/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:06:01 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 15:45:26 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigflags = 0;

void	on_signal_parents(int s_num)
{
	if (s_num == SIGINT)
	{
		g_sigflags = SIGINT;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_catch_signals = 0;
	}
	if (s_num == SIGQUIT)
		g_sigflags = SIGQUIT;
}

void	on_signal_child(int s_num)
{
	if(s_num == SIGINT)
	{
		g_sigflags = SIGINT;
		write(2,"\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_catch_signals = 0;
	}
	if(s_num == SIGQUIT)
		g_sigflags = SIGQUIT;
}

void	setup_signal_parents(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	//sa.sa_flags = SA_RESTART;
	sa.sa_flags = 0;
	sa.sa_handler = on_signal_parents;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	//sa.sa_flags = SA_RESTART;
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	// sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
