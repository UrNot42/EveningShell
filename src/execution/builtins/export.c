/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:19:25 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/13 20:54:33 by ulevallo         ###   ########.fr       */
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
		|| (!ft_isapha(name[i]) && name[i != '_']))
		return (false);
	while (name[i]
		&& (ft_isapha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
		i++;
	if (name[i] && name[i] != '=')
		return (false);
	return (true);
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
int	ft_export(char **env, char **args)
{
	int	i;
	int	err;

	err = 0;
	i = 0;
	while (args && args[i])
	{
		if (check_env_var_naming(args[i]))
			extend_env(env, args[i]);
		else
			err++;
		i++;
	}
	return (err);
}
