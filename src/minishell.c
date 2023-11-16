/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:27:32 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

/**
 * @brief Main that is bound to change as it is mainly used to redirect
 * to change funtions
 *
 */
// TODO CHECK FOR INTERACTIVE
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		start_interactive(envp);
	else
		return (run_single_cmd(argc - 1, &argv[1], envp));
	return (0);
}
