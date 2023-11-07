/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:36:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/07 09:31:30 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if there is a builtins in the arguments
 *
 * @param argc number of arguments
 * @param argv char** of the arguments
 */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (NOT_A_BT);
	if (!ft_strcmp(cmd, "cd"))
		return (BT_CD);
	if (!ft_strcmp(cmd, "echo"))
		return (BT_ECHO);
	if (!ft_strcmp(cmd, "env"))
		return (BT_ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (BT_EXIT);
	if (!ft_strcmp(cmd, "export"))
		return (BT_EXPORT);
	if (!ft_strcmp(cmd, "pwd"))
		return (BT_PWD);
	if (!ft_strcmp(cmd, "unset"))
		return (BT_UNSET);
	return (NOT_A_BT);
}
