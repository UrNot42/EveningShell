/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:16:12 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 19:39:30 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief simple boolean check to see if the var is correct
 *
 * @param s
 * @return true
 * @return false
 */
bool	check_env_var_naming(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[i]
		|| (!ft_isalpha(name[i]) && name[i] != '_'))
		return (false);
	while (name[i]
		&& (ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
		i++;
	if (name[i] && name[i] != '=')
		return (false);
	return (true);
}

/**
 * @brief unset command from shell
 *         using a custom environment
 *         therefore removing the found variable from the environment
 *
 * @return int as the error value 0 if all vars unset successfully
 * 			and >0 if at least one failed
 */
int	unset(char **env, char **args)
{
	int	i;
	int	err;
	int	index;

	err = 0;
	i = 0;
	while (args && args[i])
	{
		index = get_env_var_index(env, args[i]);
		if (!check_env_var_naming(args[i]))
			err++;
		else if (index != -1)
			env = shorten_env(env, index);
		i++;
	}
	return (err);
}
