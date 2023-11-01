/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 14:41:55 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

/**
 * @brief Main that is bound to change as it is mainly used to redirect
 * to change funtions
 *
 */
int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		start_interactive(envp);
	else
		return (run_single_cmd(argc - 1, &argv[1], envp));
	return (0);
}
/*
/SRC
	/EXECUTION (=> ?)
	/LEXER
	/PARSER
	/EXPAND
	/NONE (=> ?)
		ERROR_DISPLAY
		SIGNAL

*/
