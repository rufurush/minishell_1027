/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:14:35 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/23 18:56:32 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_erro(char *err, char *msg)
{
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

char	*resolve_command_path(char *cmd, t_pipex *ps)
{
	char	*full_path;

	ps->err = ERR_NONE;
	if (!cmd || !*cmd)
		return (ps->err = ERR_NOT_FOUND, NULL);
	if ((cmd[0] == '.' && cmd[1] == '\0') || (cmd[0] == '.' && cmd[1] == '.'
			&& cmd[2] == '\0'))
		return (ps->err = ERR_NOT_FOUND, NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!ps->path_array)
		return (ps->err = ERR_NOT_FOUND, NULL);
	full_path = find_command_path(ps->path_array, cmd);
	if (full_path)
		return (full_path);
	return (ps->err = ERR_NOT_FOUND, NULL);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (-1);
	return (S_ISDIR(st.st_mode));
}

int	execute_command(char *cmd_path, char **cmd_args, char **envp, t_pipex *ps)
{
	int	directory;

	if(!cmd_args || !cmd_args[0] || !*cmd_args[0])
		return(ps->last_status = 127);
	if (!cmd_path)
	{
		if (ps->err == ERR_NOT_FOUND)
			dprintf(2, "%s: command not found\n", cmd_args[0]);
		else
			dprintf(2, "%s: No such file or directory\n", cmd_args[0]);
		return (ps->last_status = 127);
	}
	directory = is_directory(cmd_path);
	if (directory > 0)
	{
		dprintf(2, "%s: Is a directory\n", cmd_args[0]);
		return (ps->last_status = 126);
	}
	if (directory == -1)
	{
		dprintf(2, "%s: No such file or directory\n", cmd_args[0]);
		return (ps->last_status = 127);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		dprintf(2, "%s: Permission denied\n", cmd_args[0]);
		return (ps->last_status = 126);
	}
	execve(cmd_path, cmd_args, envp);
	if (errno == ENOEXEC)
	{
		dprintf(2, "%s: Exec format error\n", cmd_args[0]);
		return (ps->last_status = 126);
	}
	dprintf(2, "%s: %s\n", cmd_args[0], strerror(errno));
	return (ps->last_status = 126);
}
