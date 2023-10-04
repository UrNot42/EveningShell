/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 09:59:40 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_cd(char **argv)
{
	if (access(argv[2], F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", argv[2]);
		return (0);
	}
	printf("cd to %s\n", argv[2]);
	chdir(argv[2]);
	return (1);
}

int	detect_cd(char **argv)
{
	if (!ft_strcmp(argv[1], "cd"))
	{
		printf("A builtins detectd : cd\n");
		return (builtins_cd(argv));
	}
	return (0);
}
