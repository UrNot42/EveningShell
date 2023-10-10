/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:07:46 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/10 17:49:17 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies the inherited env object
 * 			so that the shell can manage it's own environement
 *
 * @param old_env
 * @return the copied environment
 */
char	**copy_env(char **old_env)
{
	char	**new_env;
	size_t	size;
	size_t	i;

	size = 0;
	while (old_env && old_env[size])
		size++;
	if (size == 0)
		return (NULL);
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
			return (ft_free_dstr(new_env), NULL);
		i++;
	}
	return (new_env);
}

/**
 * @brief Creates a new environment of size + 1
 *        so that it can create a new space for the new_var
 *
 * @param old_env the env that ought to be removed
 * @param new_var var set at the bottom of the new array
 * @return the copied environment
 */
char	**extend_env(char **old_env, char *new_var)
{
	char	**new_env;
	char	**var_copy;
	size_t	i;

	i = 0;
	while (old_env && old_env[i])
		i++;
	if (i == 0)
		return (NULL);
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (ft_free_dstr(old_env), NULL);
	var_copy = ft_strdup(new_env);
	if (!var_copy)
		return (ft_free_dstr(old_env), free(new_env), NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		old_env[i++] = NULL;
	}
	ft_free_dstr(old_env);
	new_env[i] = var_copy;
	return (new_env);
}

/**
 * @brief Removes an element from the the environment
 *
 * @param old_env
 * @param new_var
 * @return char**
 */
char	**shorten_env(char **env, size_t index_var_to_delete) // TODO : finish code of function
{
	char	**new_env;
	char	**var_copy;
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	if (i == 0)
		return (NULL);
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (ft_free_dstr(env), NULL);
	var_copy = ft_strdup(new_env);
	if (!var_copy)
		return (ft_free_dstr(env), free(new_env), NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		env[i++] = NULL;
	}
	ft_free_dstr(env);
	new_env[i] = var_copy;
	return (new_env);
}

/**
 * @brief creates a default shell environment creating 3 default variables
 *
 * /!\ UNFINISHED
 *
 * @return returns a brand new allocated env
 */
char	**create_default_env(void)
{
	char		**env;
	const char	*def_vars[3] = {"PWD=", "SHLVL=", "_="};
	int			i;

	env = ft_calloc(3 + 1, sizeof(char *));
	i = 0;
	while (i < 3)
	{
		env[i] = ft_strdup(def_vars[i]);
		if (!env[i])
			return (ft_free_dstr(env), NULL);
		i++;
	}
	return (env);
}
