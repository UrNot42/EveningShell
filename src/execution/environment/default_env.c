/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:25:20 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:49:12 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief creates a default shell environment creating 3 default variables
 *
 *
 * @return returns a brand new allocated env
 */
char	**create_default_env(void)
{
	char		**env;
	const char	*def_vars[3] = {"PWD=", "SHLVL=1", "_=/usr/bin/env"};
	char		*tmp;
	int			i;

	env = ft_calloc(3 + 1, sizeof(char *));
	if (!env)
		return (error_malloc_failed(true), NULL);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(ft_free_dstr(env), error_malloc_failed(true));
	env[0] = ft_strjoin(def_vars[0], tmp);
	free(tmp);
	if (!env[0])
		(ft_free_dstr(env), error_malloc_failed(true));
	i = 1;
	while (i < 3)
	{
		env[i] = ft_strdup(def_vars[i]);
		if (!env[i])
			return (ft_free_dstr(env), NULL);
		i++;
	}
	return (env);
}
