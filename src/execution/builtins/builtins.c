/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:36:39 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 19:24:52 by aoberon          ###   ########.fr       */
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
	int	debug = 0;

	if (argc == 1)
		return ;
	if (detect_echo(argv + debug))
	{
		builtins_echo(argv + debug);
		return ;
	}
	if (detect_cd(argv + debug))
	{
		builtins_cd(argv + debug);
		printf("pwd : ");
		buitlins_pwd(argv + debug);
		return ;
	}
	if (detect_pwd(argv + debug))
	{
		buitlins_pwd(argv + debug);
		return ;
	}
	if (detect_exit(argv + debug))
	{
		builtins_exit();
		return ;
	}
	printf("No builtins detected\n");
}
