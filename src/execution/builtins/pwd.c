/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/08 16:51:28 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command pwd
 *
 * /!\ Have to change "arguments" to a better word
 *
 * @return int 1 getcwd() success, 0 otherwise
 */
int	builtins_pwd(void)
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
