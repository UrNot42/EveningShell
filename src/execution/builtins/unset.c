/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:16:12 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/19 19:55:57 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief unset command from shell
 *         using a custom environment
 *         therefore removing the found variable from the environment
 *
 * @return int as the error value 0 if all vars unset successfully
 *         and >0 if at least one failed
 */
int	unset(char **env, char **args)
{
	int	i;
	int	index;

	i = 0;
	if (args[0] && args[0][0] == '-' && args[0][1] != '\0')
		return (write(2, "unset: invalid option\n", 22), 2);
	while (args && args[i])
	{
		index = get_env_var_index(env, args[i]);
		if (index != -1)
			env = shorten_env(env, index);
		i++;
	}
	return (0);
}
