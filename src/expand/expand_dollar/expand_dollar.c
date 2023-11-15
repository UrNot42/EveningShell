/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:24:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:02:52 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expand one the $? variable
 * 
 * @param new_content char *** of the new_content
 * @param count int * of the index of the new_content
 * @param exit_status int exit status of the last command
 * @return int -1 if malloc failed, 1 otherwise
 */
static int	expand_exit_status(char ***new_content, int count, int exit_status)
{
	char	str_itoa[12];

	ft_itoa_no_malloc(exit_status, str_itoa);
	if (!(*new_content)[count])
	{
		(*new_content)[count] = ft_calloc(1, sizeof(char));
		if (!(*new_content)[count])
			return (-1);
	}
	(*new_content)[count] = ft_safe_strjoin((*new_content)[count], str_itoa);
	if (!(*new_content))
		return (-1);
	return (1);
}

/**
 * @brief Find the index of the environment variable in the env
 * 
 * @param words char * of the content
 * @param index int * of the index of the first char of the env var in words
 * @param env char ** of the environment variables
 * @return int the index of the env var in env, or
 *  -1 if malloc failed, -2 if expand is $?, -3 if expand is not found in env
 */
static int	find_index_env(char *words, int *index, char **env)
{
	char	*var_name;
	int		var_name_length;
	int		j;
	int		index_env;

	var_name_length = get_var_name_length(words, *index);
	if (!retrieve_var_name(&var_name, words, *index, var_name_length))
		return (-42);
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

/**
 * @brief Expand one environment variable
 * 
 * @param t_enc t_expand_new_content, char ***new_content, int *count,
 *  char *flag, t_expand_dollar t_ed
 * @return int -1 if malloc failed, 1 otherwise
 */
int	expand_dollar(t_expand_new_content t_enc)
{
	int		index_env;

	index_env = find_index_env(t_enc.t_ed.word, t_enc.index,
			t_enc.t_ed.env);
	if (index_env == -42)
		return (-1);
	if (index_env == -3)
	{
		return (expand_one_environment_variable(t_enc.new_content,
				t_enc.count, t_enc.flag, "=$"));
	}
	if (index_env == -2)
	{
		return (expand_exit_status(t_enc.new_content, *t_enc.count,
				t_enc.t_ed.exit_status));
	}
	if (index_env != -1)
	{
		return (expand_one_environment_variable(t_enc.new_content,
				t_enc.count, t_enc.flag, t_enc.t_ed.env[index_env]));
	}
	return (1);
}
