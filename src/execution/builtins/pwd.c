/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 12:16:03 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command pwd
 *
 * @return int 1 getcwd() success, 0 otherwise
 */
int	builtins_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_malloc_failed(false);
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
