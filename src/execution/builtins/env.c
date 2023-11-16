/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:25:28 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:38:12 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
