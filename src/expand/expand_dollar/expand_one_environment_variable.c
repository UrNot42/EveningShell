/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_environment_variable.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:26:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:02:39 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expand one environment variable in a content
 * 
 * @param new_content char *** of the new_content
 * @param count int * of the index of the new_content
 * @param flag char * of the flag of quote (equal to " or ' or \0)
 * @param env_var char * of the environment variable
 * @return int -1 if malloc failed, 1 otherwise
 */
int	expand_one_environment_variable(char ***new_content, int *count, char *flag,
	char *env_var)
{
	int		i;

	i = 0;
	while (env_var[i] != '=')
		++i;
	++i;
	while (env_var[i])
	{
		if (add_one_env_var_char(new_content, count,
				env_var[i], flag) == -1)
			return (-1);
		++i;
	}
	return (1);
}
