/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 18:58:15 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtins of the command cd
 *        moves to a given directory according to an absolute or relative path
 *        for more detail please reffer to man cd
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
			(write(2, "MarmiShell: cd: HOME not set\n", 29), ++err);
		if (chdir(&env[index][5]) == -1)
			return (perror("cd"), err);
	}
	else if (args[2] != NULL)
		(write(2, "MarmiShell: cd: too many arguments\n", 35), ++err);
	else if (args[2] == NULL && chdir(args[1]) == -1)
		return (perror("cd"), ++err);
	return (err);
}
