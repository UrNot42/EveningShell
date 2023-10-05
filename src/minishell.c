/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 19:23:51 by aoberon          ###   ########.fr       */
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

void	prompt(void)
{
	char	*buffer;
	bool	error;

	buffer = NULL;
	error = false;
	while (!error)
	{
		if (buffer)
			free(buffer);
		buffer = readline("minishell$:");
		if (buffer[0] == 'q')
			error = true;
		add_history(buffer);
		builtins(0, split_minishell(buffer));
	}
}

int	main(int argc, char **argv) //, char **envp)
{
	// char	**env;

	(void)argc;
	(void)argv;
	// if (envp)
	// 	env = copy_env(envp);
	// else
	// 	env = create_default_env();
	// if (!env)
	// 	return (EXIT_FAILURE);
	// for (size_t i = 0; env && env[i]; i++)
	// {
	// 	printf ("The %zu str is: %s\n", i, env[i]);
	// }
	prompt();
	// builtins(argc, argv);
	return (0);
}
