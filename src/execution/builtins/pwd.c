/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 12:08:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command pwd
 * 
 * /!\ Have to change "arguments" to a better word
 * 
 * @param argv char** of the arguments
 * @return int 1 getcwd() success, 0 otherwise
 */
int	buitlins_pwd(char **argv)
{
	char	*pwd;

	if (argv[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
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

/**
 * @brief Detects if the command is pwd
 * 
 * /!\ Have to change "arguments" to a better word
 * 
 * @param argv char** of the arguments to check
 * @return int 1 if the command is pwd, 0 otherwise
 */
int	detect_pwd(char **argv)
{
	if (!ft_strcmp(argv[0], "pwd"))
	{
		printf("A builtins detected : pwd\n");
		return (1);
	}
	return (0);
}
