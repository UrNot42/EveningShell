/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 17:28:04 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command cd
 *
 *
 * @param args char** of the arguments
 * @return int 1 if the command is well executed, 0 otherwise
 */
int	builtins_cd(char **args, char **env)
{
	int	index;
	int	err;

	err = 0;
	if (args[1] == NULL)
	{
		index = get_env_var_index(env, "HOME");
		if (index == -1)
			(printf("minishell: cd: HOME not set\n"), err++);
		else if (access(&env[index][5], F_OK) != -1)
			chdir(&env[index][5]);
	}
	else if (args[2] != NULL)
		(printf("minishell: cd: too many arguments\n"), err++);
	else if (access(args[1], F_OK) == -1)
		printf("minishell: cd: %s: No such file or directory\n", args[++err]);
	else if (args[2] == NULL)
		(printf("cd to %s\n", args[1]), chdir(args[1]));
	return (err);
}
