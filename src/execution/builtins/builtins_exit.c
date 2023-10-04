/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 18:20:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exits the shell process currently running
 *
 * @return exit [n]
 * 			Exit the shell, returning a status of n to the shell’s parent. If n is omitted, the
 * 			exit status is that of the last command executed. Any trap on EXIT is executed
 * 			before the shell terminates.
 */
static int	builtins_exit(void)
{
	printf("free all\n");
	printf("exit at value ? (for now it's EXIT_SUCCESS)\n");
	exit(EXIT_SUCCESS);
}

int	detect_exit(char **argv)
{
	if (!ft_strcmp(argv[0], "exit"))
	{
		printf("A builtins detected : exit\n");
		builtins_exit();
	}
	return (0);
}
