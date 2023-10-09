/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/09 17:27:26 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command cd
 *
 * /!\ Have to change "arguments" to a better word
 *
 * @param argv char** of the arguments
 * @return int 1 if the command is well executed, 0 otherwise
 */
int	builtins_cd(char **argv)
{
	if (argv[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	if (access(argv[1], F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", argv[1]);
		return (0);
	}
	printf("cd to %s\n", argv[1]);
	chdir(argv[1]);
	return (1);
}

/**
 * @brief Detects if the command is cd
 *
 * /!\ Have to change "arguments" to a better word
 *
 * @param argv char** of the arguments to check
 * @return int 1 if the command is cd, 0 otherwise
 */
int	detect_cd(char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
	{
		printf("A builtins detected : cd\n");
		return (1);
	}
	return (0);
}
