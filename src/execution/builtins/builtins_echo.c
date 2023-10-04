/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 09:49:08 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_echo(int argc, char **argv, int backslash)
{
	if ((argc == 2 && !backslash) || (argc == 3 && backslash))
	{
		printf("Missing arguments.\n");
		return (0);
	}
	printf("%s", argv[2 + backslash]);
	if (!backslash)
		printf("\n");
	return (1);
}

int	detect_echo(int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "echo"))
	{
		printf("A builtins detectd : echo\n");
		if (!ft_strcmp(argv[2], "-n"))
			return (builtins_echo(argc, argv, 1));
		return (builtins_echo(argc, argv, 0));
	}
	return (0);
}
