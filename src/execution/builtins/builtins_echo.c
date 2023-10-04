/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 12:04:25 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_echo(int argc, char **argv)
{
	int	new_line;

	new_line = 0;
	if (!ft_strcmp(argv[1], "-n"))
		new_line = 1;
	if ((argc == 2 && !new_line) || (argc == 3 && new_line))
	{
		printf("Missing arguments.\n");
		return (0);
	}
	printf("%s", argv[2 + new_line]);
	if (!new_line)
		printf("\n");
	return (1);
}

int	detect_echo(int argc, char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
	{
		printf("A builtins detected : echo\n");
		return (builtins_echo(argc, argv));
	}
	return (0);
}
