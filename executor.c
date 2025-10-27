/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:22:32 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 13:56:56 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_exit_status(int stR)
{

	if (WIFEXITED(stR))
		return(WEXITSTATUS(stR));
	else if (WIFSIGNALED(stR))
		return(128 + WTERMSIG(stR));
	else
		return(1);
}

static void free_arg_list_a(t_arg *a)
{
    while (a) 
    {
         t_arg *n = a->next; 
        free(a->value); 
        free(a); 
        a = n; 
    }
}

int exec_cmd_node(t_ast *node_list, char **envp, t_pipex *ps)//実行関数に渡したり渡すための下準備を行う関数。
{
    pid_t pid;
    char *full_path;
    int execute;
    int code;
    int st;

    if(!node_list)
        return(0);
    pid = fork();
    if(pid < 0)
    {
        free_arg_list_a(node_list->arg_list);
        return(0);
    }
    if(pid == 0)
    {
        if(apply_redirs(node_list->redirs) < 0)
            _exit(1);
        
        full_path = resolve_command_path(node_list->argv[0],ps);
        execute = execute_command(full_path,node_list->argv,envp,ps);
        if (full_path)
		    free(full_path);
	    //free(line);free(node_list)とかであればいいのだけど
	    _exit(execute);   
    }
    waitpid(pid,&st,0);
    code = get_exit_status(st);
    if(ps)
        ps->last_status = code;
    return(code);
}

int exec_cmd_pipe_node(t_ast *node_list, char **envp, t_pipex *ps,char *line)
{
    int fds[2];
    int st;
    int st_right;
    int st_left;
    int status_code;
    pid_t   left;
    pid_t   right;

    if(pipe(fds) < 0)
        return(1);
    left = fork();
    if(left < 0)
    {
        close(fds[0]);
        close(fds[1]);
        return(1);
    }
    if(left == 0)
    {
        signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
        close(fds[0]);
        if(dup2(fds[1],1) == -1)
            _exit(1);
        close(fds[1]);
        st = execute_ast(node_list->left,envp,ps,line);
        _exit(st);
    }
    right = fork();
    if(right < 0)
    {
        close(fds[0]);
        close(fds[1]);
        waitpid(left, &st_left,0);
        return(1);
    }
    if(right == 0)
    {
        signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
        close(fds[1]);
        if(dup2(fds[0],0) < 0)
            _exit(1);
        close(fds[0]);
        st = execute_ast(node_list->right,envp,ps,line);
        _exit(st);
    }
    close(fds[0]);
    close(fds[1]);
    waitpid(left,&st_left,0);
    waitpid(right,&st_right,0);
    status_code = get_exit_status(st_right);
    return(status_code);
}

int execute_ast(t_ast *node_list,char **envp,t_pipex *ps,char *line)//parseしたものを型分岐していって実行に回していくための関数。
{
    if(!node_list)
        return(1);
    if(node_list->type == NODE_CMD)
        return(exec_cmd_node(node_list,envp,ps));
    if(node_list->type == NODE_PIPE)
        return(exec_cmd_pipe_node(node_list,envp,ps,line));
    return(1);
}
