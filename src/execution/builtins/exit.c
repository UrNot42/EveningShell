/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 12:05:45 by aoberon          ###   ########.fr       */
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
void	builtins_exit(void)
{
	printf("free all\n");
	printf("Not right exit value ! (for now it's EXIT_SUCCESS)\n");
	printf("Dunno what to do if exit had arguments ¯\\_(-_-)_/¯ !\n");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Detects if the command is exit
 * 
 * /!\ Have to change "arguments" to a better word
 * 
 * @param argv char** of the arguments to check
 * @return int 1 if the command is exit, 0 otherwise
 */
int	detect_exit(char **argv)
{
	if (!ft_strcmp(argv[0], "exit"))
	{
		printf("A builtins detected : exit\n");
		return (1);
	}
	return (0);
}
