/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:05:52 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 13:23:04 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief default behaviour for ctrl-c inside the prompt
 *
 * @param signum
 */
void	sig_handler_prompt(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief behaviour function for SIGINT iside heredoc
 *
 * @param signum
 */
void	sig_handler_heredoc(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_redisplay();
	exit_heredoc(false, NULL, NULL);
	exit(130);
}

/**
 * @brief while waiting for commands to execute ALLOWS SIGINT AND SIGKILL
 * to modify the g_signal variable to catch errors
 *
 * @param signum
 */
void	sig_handler_exec(int signum)
{
	if (signum == SIGINT)
		g_signal = 130;
	if (signum == SIGQUIT)
		g_signal = 131;
}
