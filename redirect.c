/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:15:52 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 13:08:23 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int build_heredoc_fd(const char *delim)
{
    char path[] = "/tmp/minish_hdocXXXXXX";
    int wfd = mkstemp(path);
    char *line;
    size_t dlen;

    if (wfd < 0) return -1;

    while (1)
    {
        write(2, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line) 
            break;
        dlen = ft_strlen(delim);
        if (!ft_strncmp(line, delim, dlen) &&
            (line[dlen] == '\n' || line[dlen] == '\0')) {
            free(line);
            break;
        }
        write(wfd, line, ft_strlen(line));
        free(line);
    }
    close(wfd);

    int rfd = open(path, O_RDONLY);
    unlink(path);
    return (rfd);
}

int apply_redirs(t_redir *list)
{
    for (t_redir *p = list; p; p = p->next) {
        if (apply_one_redir(p) < 0)
            return (-1);
    }
    return 0;
}

int apply_one_redir(t_redir *node)
{
    int fd;

    if(node->kind == INPUT)
    {
        fd = open(node->filename,O_RDONLY);
        if(fd < 0)
            return(-1);
        if(dup2(fd,0) == -1)
        {
            perror("dup2 file");
            return(1);
        }
        close(fd);
    }
    else if(node->kind == OUTPUT)
    {
        fd = open(node->filename,O_WRONLY | O_CREAT |O_TRUNC,0644);
        if(fd < 0)
            return(-1);
        if(dup2(fd,1) == -1)
        {
            perror("open file");
            exit(1);
        }
        close(fd);
    }
    else if(node->kind == APPEND)
    {
        fd = open(node->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
        if(fd < 0)
            return(-1);
        if(dup2(fd,1) == -1)
        {
            perror("open");
            return(-1);
        }
        close(fd);
    }
    else if(node->kind == HEREDOC)
    {
        
        fd = build_heredoc_fd(node->delim);
        if(fd < 0)
            return(-1);
        if(dup2(fd,0) == -1)
        {
            close(fd);
            return(-1);
        }
        close(fd);
    }
    return(0);
}
