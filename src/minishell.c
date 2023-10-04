/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 18:10:08 by ulevallo         ###   ########.fr       */
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
 * @brief creates a default shell environment creating 3 default variables
 *
 * /!\ UNFINISHED
 *
 * @return returns a brand new allocated env
 */
char	**create_default_env(void)
{
	char	**env;

	env = ft_calloc(3 + 1, sizeof(char *));
	env[0] = ft_strdup("PWD=");
	env[1] = ft_strdup("SHLVL=");
	env[2] = ft_strdup("_=");
	return (new_env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	if (envp)
		env = copy_env(envp);
	else
		env = create_default_env();
	if (!env)
		return (EXIT_FAILURE);
	for (size_t i = 0; env && env[i]; i++)
	{
		printf ("The %zu str is: %s\n", i, env[i]);
	}
	return (0);
}
