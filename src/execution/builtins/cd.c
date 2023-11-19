/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/19 16:53:54 by aoberon          ###   ########.fr       */
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
		else if (chdir(&env[index][5]) == -1)
			return (perror("cd"), err);
	}
	else if (args[2] != NULL)
		(write(2, "MarmiShell: cd: too many arguments\n", 35), ++err);
	else if (args[2] == NULL && args[1][0] == '-' && args[1][1] == '\0')
	{
		index = get_env_var_index(env, "OLDPWD");
		if (index == -1)
			(write(2, "MarmiShell: cd: OLDPWD not set\n", 31), ++err);
		else if (chdir(&env[index][7]) == -1)
			return (perror("cd"), err);
		builtins_pwd();
	}
	else if (args[2] == NULL && chdir(args[1]) == -1)
		return (perror("cd"), ++err);
	return (err);
}
