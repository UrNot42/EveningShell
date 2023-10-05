/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:36:39 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 12:10:26 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if there is a builtins in the arguments
 * 
 * /!\ Have to change "arguments" to a better word
 * /!\ USE PRINTF FOR NOW /!\
 * 
 * @param argc number of arguments
 * @param argv char** of the arguments
 */
void	builtins(int argc, char **argv)
{
	if (argc == 1)
		return ;
	if (detect_echo(argv + 1))
	{
		builtins_echo(argv + 1);
		return ;
	}
	if (detect_cd(argv + 1))
	{
		builtins_cd(argv + 1);
		printf("pwd : ");
		buitlins_pwd(argv + 1);
		return ;
	}
	if (detect_pwd(argv + 1))
	{
		buitlins_pwd(argv + 1);
		return ;
	}
	if (detect_exit(argv + 1))
	{
		builtins_exit();
		return ;
	}
	printf("No builtins detected\n");
}
