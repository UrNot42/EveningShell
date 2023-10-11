/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:07:46 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:00 by ulevallo         ###   ########.fr       */
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
	size_t	i;

	i = 0;
	while (old_env && old_env[i])
		i++;
	if (i == 0)
		return (NULL);
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (ft_free_dstr(old_env), NULL);
	var_copy = ft_strdup(new_var);
	if (!var_copy)
		return (ft_free_dstr(old_env), free(new_env), NULL);
	i = 0;
	while (old_env && old_env[i])
	{
		new_env[i] = old_env[i];
		old_env[i] = NULL;
		i++;
	}
	ft_free_dstr(old_env);
	new_env[i] = var_copy;
	return (new_env);
}

/**
 * @brief Get the env var object
 *
 * @param env curent env that we are working with
 * @param var variable we are trying to find inside said env
 * @return the index of the found variable
 */
// TODO : FINISH
int	get_env_var(char **env, char *var)
{
	int	i;
	int	j;

	if (!env)
		return (-1);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && var[j] && env[i][j] == var[j])
			j++;
		if (env[i][j] && env[i][j] == '=')
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
char	**shorten_env(char **env, size_t index_var_to_delete)
{
	size_t	i;
	size_t	size;

	size = 0;
	while (env && env[size])
		size++;
	if (size == 0 || size <= index_var_to_delete)
		return (NULL);
	free(env[index_var_to_delete]);
	env[index_var_to_delete] = NULL;
	i = index_var_to_delete;
	while (env && env[i] && env[i + 1])
	{
		env[i] = env[i + 1];
		env[i +1] = NULL;
		i++;
	}
	return (env);
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

void	print_env(char **env)
{
	for (size_t i = 0; env && env[i]; i++)
	{
		printf("%s\n", env[i]);
	}
	printf("====================================================\n");
}

int	main(int argc, char **argv, char **envp)
{
	char **env;

	env = copy_env(envp);
	print_env(env);
	if (argc > 1)
		env = extend_env(env, argv[1]);
	print_env(env);
	if (argc > 2)
		printf("index of %s: %d\n", argv[2], get_env_var(env, argv[2]));
	// shorten_env();
	ft_free_dstr(env);
	return (0);
}
