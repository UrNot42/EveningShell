/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/03 17:47:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_cd(int argc, char **argv)
{
	(void)argc;
	if (access(argv[2], F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", argv[2]);
		return (0);
	}
	printf("cd to %s\n", argv[2]);
	chdir(argv[2]);
	return (1);
}

int	detecte_cd(int argc, char **argv)
{
	(void)argc;
	if (!ft_strcmp(argv[1], "cd"))
	{
		printf("A builtins detected : cd\n");
		return (builtins_cd(argc, argv));
	}
	return (0);
}
