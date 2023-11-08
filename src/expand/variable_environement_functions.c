/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_environement_functions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:21:44 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/08 15:56:52 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	retrieve_var_name(char **var, char *str,
	size_t index_dollar, size_t size)
{
	size_t	i;

	i = 0;
	*var = ft_calloc(size + 1, sizeof(char));
	if (!*var)
		return (0);
	++index_dollar;
	while (i < size)
	{
		(*var)[i] = str[index_dollar];
		++index_dollar;
		++i;
	}
	return (1);
}

static int	copy_env_var_content(char **var_content, char **env, int index,
size_t *var_content_length)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env[index][i] != '=')
		++i;
	++i;
	*var_content_length = ft_strlen(env[index]) - i;
	*var_content = ft_calloc(sizeof(char), *var_content_length + 1);
	if (!*var_content)
		return (0);
	j = 0;
	while (j < *var_content_length)
	{
		(*var_content)[j] = env[index][i];
		++i;
		++j;
	}
	return (1);
}

int	set_var(t_expand_params *params, char *content, char **env, int exit_status)
{
	if (!retrieve_var_name(&(params)->var, content, params->index_dollar,
			params->var_name_length))
		return (-1);
	if (ft_strcmp(params->var, "?"))
	{
		params->index_env = get_env_var_index(env, params->var);
		(free(params->var), params->var = NULL);
		if (params->index_env != -1 && !copy_env_var_content(&params->var,
				env, params->index_env, &params->var_content_length))
			return (-1);
	}
	else
		(free(params->var), params->var = ft_itoa(exit_status));
	return (1);
}
