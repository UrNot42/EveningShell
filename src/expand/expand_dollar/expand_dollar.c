/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:24:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:32:32 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_exit_status(char ***new_content, int count, int exit_status)
{
	char	str_itoa[12];

	ft_itoa_no_malloc(exit_status, str_itoa);
	(*new_content)[count] = ft_safe_strjoin((*new_content)[count], str_itoa);
	if (!(*new_content))
		return (-1);
	return (1);
}

static int	get_index_for_expand(char *words, int *index, char **env)
{
	char	*var_name;
	int		var_name_length;
	int		j;
	int		index_env;

	var_name_length = get_var_name_length(words, *index);
	if (!retrieve_var_name(&var_name, words, *index, var_name_length))
		return (-1);
	j = 0;
	while (j++ < var_name_length)
	{
		*index += 1;
	}
	if (!ft_strcmp(var_name, "?"))
	{
		return (free(var_name), -2);
	}
	if (var_name_length == 0)
	{
		return (free(var_name), -3);
	}
	index_env = get_env_var_index(env, var_name);
	free(var_name);
	return (index_env);
}

int	expand_dollar(char ***new_content, int *count, int *index,
	t_expand_dollar expand_dollar)
{
	int		index_env;

	index_env = get_index_for_expand(expand_dollar.word, index,
			expand_dollar.env);
	if (index_env == -3)
	{
		return (expand_one_environment_variable(new_content, count,
				"=$"));
	}
	if (index_env == -2)
	{
		return (expand_exit_status(new_content, *count,
				expand_dollar.exit_status));
	}
	if (index_env != -1)
	{
		return (expand_one_environment_variable(new_content, count,
				expand_dollar.env[index_env]));
	}
	return (1);
}
