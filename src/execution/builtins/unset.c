/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:16:12 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/02 16:46:47 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		if (index != -1)
			shorten_env(env, index);
		else
			err++;
		i++;
	}
	return (err);
}
