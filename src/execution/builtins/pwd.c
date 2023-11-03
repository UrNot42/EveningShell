/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 17:01:33 by ulevallo         ###   ########.fr       */
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
