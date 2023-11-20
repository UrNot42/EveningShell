/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:25:28 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/20 17:04:18 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_env_var_valid(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[i]
		|| (!ft_isalpha(name[i]) && name[i] != '_'))
	{
		return (false);
	}
	while (name[i]
		&& (ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
		i++;
	if (name[i] != '=')
		return (false);
	return (true);
}

/**
 * @brief prints out a double string ending every line with a \n
 *
 * @param env
 * @return 0 to express no errors were found
 */
int	env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (check_env_var_valid(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
