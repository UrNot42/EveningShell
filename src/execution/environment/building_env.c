/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:07:46 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:47:35 by ulevallo         ###   ########.fr       */
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
	char	*var_copy;
	size_t	i[2];

	i[0] = 0;
	if (!new_var)
		return (old_env);
	while (old_env && old_env[i[0]])
		i[0]++;
	new_env = ft_calloc(i[0] + 2, sizeof(char *));
	if (!new_env)
		return (old_env);
	var_copy = ft_strdup(new_var);
	if (!var_copy)
		return (free(new_env), old_env);
	i[1] = 0;
	while (i[1] < i[0])
	{
		new_env[i[1]] = old_env[i[1]];
		old_env[i[1]] = NULL;
		i[1]++;
	}
	ft_free_dstr(old_env);
	new_env[i[1]] = var_copy;
	return (new_env);
}

/**
 * @brief Get the env var
 *
 * @param env curent env that we are working with
 * @param var variable we are trying to find inside said env
 * @return the index of the found variable
 */
int	get_env_var_index(char **env, char *var)
{
	int	i;
	int	j;

	if (!env || !var || !*env)
		return (-1);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && var[j] && var[j] != '=' && env[i][j] == var[j])
			j++;
		if (env[i][j] && env[i][j] == '=' && (!var[j] || var[j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Removes an element from the the environment
 *
 * @param old_env
 * @param new_var
 * @return env shortened
 */
char	**shorten_env(char **env, int index_var_to_delete)
{
	int	i;
	int	size;

	size = 0;
	if (index_var_to_delete < 0)
		return (env);
	while (env && env[size])
		size++;
	if (size == 0 || size <= index_var_to_delete)
		return (NULL);
	free(env[index_var_to_delete]);
	env[index_var_to_delete] = NULL;
	i = index_var_to_delete;
	while (env && env[i + 1])
	{
		env[i] = env[i + 1];
		env[i + 1] = NULL;
		i++;
	}
	return (env);
}
