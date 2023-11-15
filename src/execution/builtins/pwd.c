/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:45:59 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:06:04 by aoberon          ###   ########.fr       */
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
		// fix error failed malloc not freeing
		error_failed_malloc();
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
