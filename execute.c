/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:26:14 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 13:54:25 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splits(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}

void	execute(int argc, char **argv, char **envp, t_pipex *ps)
{
	char	*line;
	char	**cmd_args;
	int		st;
	t_token_list *token_list_head;
	t_ast		 *node_list;

	(void)argc;
	(void)argv;
	//setup_signal();
	ps->path_array = get_path_array(envp, ps);
	// rl_catch_signals = 0;
	
	while (1)
	{
		setup_signal_parents();
		//(void)setup_signal_parents;
		line = readline("minishell$");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if(g_sigflags == SIGINT)
			ps->last_status = 130;
		else if(g_sigflags == SIGQUIT)
			ps->last_status = 131;
		if (g_sigflags == SIGINT || g_sigflags == SIGQUIT)
		{
			if (line[0] == '\0')
			{
				if (g_sigflags == SIGINT)
					ps->last_status = 130;
				else if (g_sigflags == SIGQUIT)
					ps->last_status = 131;
				g_sigflags = 0;
				free(line);
				continue ;
			}
			g_sigflags = 0;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		token_list_head = create_token_list(line);
		if(!token_list_head)
			return;
		node_list = parse_pipeline(&token_list_head);
		if(!node_list)
			return;
		if (ft_strnstr(line, "echo $?", ft_strlen(line)))
		{
			printf("%d\n", ps->last_status);
			ps->last_status = 0;
			free(line);
			continue ;
		}
		cmd_args = ft_split(line, ' ');
		if (!cmd_args || !cmd_args[0] || !*cmd_args[0])
		{
			free_splits(cmd_args);
			free(line);
			continue ;
		}
		st = execute_ast(node_list,envp,ps,line);
		ps->last_status = st;
		ast_free_a(node_list);
		continue;
	}
}
