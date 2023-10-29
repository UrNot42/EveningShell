/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:25:20 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/29 13:30:25 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief creates a default shell environment creating 3 default variables
 *
 * /!\ UNFINISHED TODO
 *
 * @return returns a brand new allocated env
 */
char	**create_default_env(void)
{
	char		**env;
	const char	*def_vars[3] = {"PWD=", "SHLVL=1", "_="};
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

/*

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
	char	**env;

	env = copy_env(envp);
	print_env(env);
	if (argc > 1)
		env = extend_env(env, argv[1]);
	print_env(env);
	if (argc > 2)
	{
		printf("index of %s: %d\n", argv[2], get_env_var_index(env, argv[2]));
		shorten_env(env, get_env_var_index(env, argv[2]));
		print_env(env);
		env = extend_env(env, "KOALA=NON");
		env = extend_env(env, "NQOQOFHOSD=OPO");
		print_env(env);
	}
	ft_free_dstr(env);
	return (0);
}
*/