/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:39:00 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/21 15:49:42 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_access(char **envp)
{
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char **path_array, char *cmd)
{
	size_t	i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	**get_path_array(char **envp, t_pipex *px)
{
	char	*path_env;

	path_env = ft_search_access(envp);
	if (!path_env || !*path_env)
	{
		px->no_path_flag = 1;
		return (NULL);
	}
	px->no_path_flag = 0;
	px->path_array = ft_split(path_env, ':');
	if (!px->path_array)
	{
		write(2, "malloc error\n", 13);
		exit(1);
	}
	return (px->path_array);
}
