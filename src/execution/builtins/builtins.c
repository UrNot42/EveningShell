/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:36:39 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 10:27:54 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "env")
		|| ft_strcmp(cmd, "exit") || ft_strcmp(cmd, "export")
		|| ft_strcmp(cmd, "pwd") || ft_strcmp(cmd, "unset"))
		return (true);
	return (false);
}

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
