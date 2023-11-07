/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:05:52 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/07 14:29:40 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_prompt(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler_heredoc(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_redisplay();
	exit_heredoc(0, NULL, NULL);
	exit(130);
}

void	sig_handler_exec(int signum)
{
	if (signum == SIGINT)
		g_signal = 130;
	if (signum == SIGQUIT)
		g_signal = 131;
}
