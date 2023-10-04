/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 12:50:41 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
