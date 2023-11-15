/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_environment_variable.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:26:57 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 10:28:30 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (expand_on_one_env_var_char(new_content, count,
				env_var[i], flag) == -1)
			return (-1);
		++i;
	}
	return (1);
}
