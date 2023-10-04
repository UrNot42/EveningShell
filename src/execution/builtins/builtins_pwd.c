/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 12:50:21 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	buitlins_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error of malloc.\n");
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int	detect_pwd(char **argv)
{
	if (!ft_strcmp(argv[0], "pwd"))
	{
		printf("A builtins detected : pwd\n");
		return (buitlins_pwd());
	}
	return (0);
}
