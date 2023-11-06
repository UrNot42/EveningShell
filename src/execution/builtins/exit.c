/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/06 19:23:43 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO
bool	check_exit_args(char args)
{
	(void)(args);
	return (false);
}

/**
 * @brief Exits the shell process currently running
 *
 * @return exit [n]
 * 			Exit the shell, returning a status of n to the shell’s parent.
 * 			If n is omitted, the exit status is that of the last command executed.
 * 			Any trap on EXIT is executed before the shell terminates.
 */
int	builtins_exit(int code)
{
	if (isatty(STDIN_FILENO) && isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit(code);
}
