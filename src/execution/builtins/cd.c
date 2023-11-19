/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:36:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/19 19:59:50 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief moves to the var specified by var and at the index size
 *
 * @param env
 * @param var
 * @param size
 * @return int
 */
int	try_cd(char **env, char *var, int size)
{
	int	index;

	index = get_env_var_index(env, var);
	if (index == -1)
	{
		write(2, "MarmiShell: cd: ", 16);
		write(2, var, ft_strlen(var));
		write(2, " not set\n", 9);
		return (1);
	}
	else if (chdir(&env[index][size]) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	do_export_cd(char ***env, char *content, bool new)
{
	char	*tmp;
	char	**args;

	if (new)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (error_malloc_failed(false), 1);
		tmp = ft_safe_strjoin_2("PWD=", tmp);
		if (!tmp)
			return (error_malloc_failed(false), 1);
	}
	else
	{
		tmp = ft_safe_strjoin_2("OLDPWD=", content);
		if (!tmp)
			return (error_malloc_failed(false), 1);
	}
	args = ft_calloc(sizeof(char *), 2);
	if (!args)
		return (error_malloc_failed(false), 1);
	args[0] = tmp;
	ft_export(env, (char **)args, false);
	return (ft_free_dstr(args), 0);
}

/**
 * @brief Builtins of the command cd
 *        moves to a given directory according to an absolute or relative path
 *        for more detail please reffer to man cd
 *
 * @param args char** of the arguments
 * @return int 1 if the command is well executed, 0 otherwise
 */
int	builtins_cd(char **args, char ***env)
{
	char	*opwd;

	opwd = getcwd(NULL, 0);
	if (!opwd)
		return (error_malloc_failed(false), 1);
	if (args[1] == NULL)
	{
		if (try_cd(*env, "HOME", 5))
			return (free(opwd), 1);
	}
	else if (args[2] != NULL)
	{
		return (write(2, "MarmiShell: cd: too many arguments\n", 35),
			free(opwd), 1);
	}
	else if (args[2] == NULL && args[1][0] == '-' && args[1][1] == '\0')
	{
		if (try_cd(*env, "OLDPWD", 7))
			return (free(opwd), 1);
		builtins_pwd();
	}
	else if (args[2] == NULL && chdir(args[1]) == -1)
		return (perror("cd"), free(opwd), 1);
	(do_export_cd(env, opwd, false), do_export_cd(env, NULL, true));
	return (0);
}
