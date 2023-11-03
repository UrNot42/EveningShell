/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 16:26:18 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	write(1, "exit\n", 5);
	exit(code);
}
