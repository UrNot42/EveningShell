/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:19:25 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/09 11:14:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   about naming:
 *         -Variable names can consist of letters (a-z, A-Z), digits (0-9),
 *           and underscores (_).
 *         -They must start with a letter or an underscore.
 *         -Variable names are case-sensitive.
 *
 * @param name the var to check
 * @return true if the var is fitted to be added inside the env
 * @return false if the variable is not conform to be added to the env
 */
static bool	check_env_var_naming(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[i]
		|| (!ft_isalpha(name[i]) && name[i] != '_'))
		return (false);
	while (name[i]
		&& (ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
		i++;
	if (name[i] && name[i] != '=')
		return (false);
	return (true);
}

static int	check_env_var_exist(char **env, char *var)
{
	int	env_index;
	int	varname_len;

	varname_len = 0;
	while (var[varname_len] && var[varname_len] != '=')
		++varname_len;
	env_index = 0;
	while (env[env_index])
	{
		if (!ft_strncmp(env[env_index], var, varname_len))
			return (env_index);
		++env_index;
	}
	return (-1);
}

int	print_solo_export(char **env)
{
	int	i;
	int	j;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
	{
		printf("export ");
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '\"')
				printf("\\");
			printf("%c", env[i][j]);
			if (env[i][j] == '=')
				printf("\"");
			j++;
		}
		printf("\"\n");
		i++;
	}
	return (0);
}

/**
 * @brief export command from shell
 *         using a custom environment
 *         therefore adding it to the environment
 *
 *         about naming:
 *         -Variable names can consist of letters (a-z, A-Z), digits (0-9),
 *           and underscores (_).
 *         -They must start with a letter or an underscore.
 *         -Variable names are case-sensitive.
 *
 * @return int as the error value
 */
int	ft_export(char ***env, char **args)
{
	int	i;
	int	err;
	int	env_index;

	err = 0;
	i = 0;
	if (!args || !*args)
		return (print_solo_export(*env));
	while (args && args[i])
	{
		env_index = check_env_var_exist(*env, args[i]);
		if (env_index != -1)
		{
			free((*env)[env_index]);
			(*env)[env_index] = ft_strdup(args[i]);
		}
		else if (check_env_var_naming(args[i]))
			*env = extend_env(*env, args[i]);
		else
			err++;
		i++;
	}
	return (err);
}
