/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:19:25 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/20 18:16:26 by ulevallo         ###   ########.fr       */
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
static bool	check_env_var_naming(char *name, bool print)
{
	int	i;

	i = 0;
	if (!name || !name[i]
		|| (!ft_isalpha(name[i]) && name[i] != '_'))
	{
		if (print)
		{
			write(2, "export: `", 9);
			write(2, name, ft_strlen(name));
			write(2, "': not a valid identifier\n", 26);
		}
		return (false);
	}
	while (name[i]
		&& (ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
		i++;
	if (name[i] && name[i] != '=')
		return (false);
	return (true);
}

char	**get_sorted_env(char **env)
{
	char	**sort_env;
	char	*tmp;
	int		i;

	if (!env)
		return (NULL);
	sort_env = ft_dstrdup((const char **)env);
	if (!sort_env)
		return (error_malloc_failed(false), NULL);
	while (!ft_dstr_is_sorted(sort_env))
	{
		i = 0;
		while (sort_env[i] && sort_env[i + 1])
		{
			if (ft_strcmp(sort_env[i], sort_env[i + 1]) > 0)
			{
				tmp = sort_env[i];
				sort_env[i] = sort_env[i + 1];
				sort_env[i + 1] = tmp;
			}
			i++;
		}
	}
	return (sort_env);
}

void	print_export_var(char *var)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	printf("export ");
	while (var[i])
	{
		if (var[i] == '\"')
			printf("\\");
		printf("%c", var[i]);
		if (var[i] == '=' && !check++)
			printf("\"");
		i++;
	}
	if (check)
		printf("\"");
	printf("\n");
	i++;
}

/**
 * @brief handles the printing of the entire env when typing export on its own
 *
 * @param env
 * @return 0
 */
int	print_solo_export(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
	{
		print_export_var(env[i++]);
	}
	return (ft_free_dstr(env), 0);
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
int	ft_export(char ***env, char **args, bool print)
{
	int	i;
	int	err;
	int	env_index;

	err = 0;
	i = 0;
	if (!args || !*args)
		return ((print && print_solo_export(get_sorted_env(*env))), 0);
	if (args[0] && args[0][0] == '-' && args[0][1] != '\0')
		return ((print && write(2, "export: invalid option\n", 23)), 2);
	while (args && args[i])
	{
		env_index = get_env_var_index(*env, args[i]);
		if (env_index != -1)
		{
			free((*env)[env_index]);
			(*env)[env_index] = ft_strdup(args[i]);
		}
		else if (check_env_var_naming(args[i], print))
			*env = extend_env(*env, args[i]);
		else
			err++;
		i++;
	}
	return (err);
}
