/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:28:29 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/10 22:36:03 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_dollar_word_length(char *content, char **env, int exit_status, int *index, int *word_length, int *index_env, int *index_expand, char **var_name)
{
	int	var_name_length;

	if (*var_name == NULL)
	{
		var_name_length = get_varname_length(content, *index);
		if (!retrieve_var_name(var_name, content, *index, var_name_length))
			return (-1);

		int	j;
		j = 0;
		while (j++ < var_name_length)
		{
			*index += 1;
		}
		if (!strcmp(*var_name, "?"))
		{
			*index_env = -2;
			*index_expand = 0;
			free(*var_name);
			*var_name = NULL;
			*word_length += ft_nbrlen(exit_status);
			printf("%d", exit_status);
			return (0);
		}
		*index_env = get_env_var_index(env, *var_name);
		if (*index_env == -1)
		{
			*index_env = -2;
			*index_expand = 0;
			free(*var_name);
			*var_name = NULL;
			return (0);
		}
		while (env[*index_env][*index_expand] != '=')
			*index_expand += 1;
	*index_expand += 1;
	}

	char	flag;
	flag = '\0';
	while (env[*index_env][*index_expand])
	{
		if (env[*index_env][*index_expand] != ' ' && env[*index_env][*index_expand] != '\t')
		{
			*word_length += 1;
		}
		else if (env[*index_env][*index_expand] == ' ' || env[*index_env][*index_expand] == '\t')
		{
			*index_expand += 1;
			return (1);
		}
		else if (env[*index_env][*index_expand] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
			else if (flag == '\'')
				return (1);
		}
		else if (env[*index_env][*index_expand] == '"')
		{
			if (flag == '\0')
				flag = '"';
			else if (flag == '"')
				return (1);
		}
		*index_expand += 1;
	}
	*index_env = -2;
	*index_expand = 0;
	free(*var_name);
	*var_name = NULL;
	return (0);
}

int	word_length_expand(char *content, char **env, int exit_status, int *index)
{
	int	word_length;
	int	expand_flag;

	static char	flag = '\0';
	static int	index_expand = 0;
	static int	index_env = -2;
	static char	*var_name = NULL;

	word_length = 0;
	if (var_name)
	{
		expand_flag = expand_dollar_word_length(content, env, exit_status, index, &word_length, &index_env, &index_expand, &var_name);
		*index += 1;
		if (expand_flag == -1)
		{
			flag = '\0';
			return (-1);
		}
		if (expand_flag == 1)
		{
			flag = '\0';
			return (word_length);
		}
	}
	while (content[*index])
	{
		if (content[*index] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
			else if (flag == '\'')
				flag = '\0';
			else if (flag == '"')
			{
				++word_length;
			}
		}
		else if (content[*index] == '"')
		{
			if (flag == '\0')
				flag = '"';
			else if (flag == '\'')
			{
				++word_length;
			}
			else if (flag == '"')
				flag = '\0';
		}
		else if (content[*index] == '$')
		{
			if (flag == '\'')
			{
				++word_length;
			}
			else if (flag == '\0' || flag == '"')
			{
				expand_flag = expand_dollar_word_length(content, env, exit_status, index, &word_length, &index_env, &index_expand, &var_name);
				if (expand_flag == -1)
				{
					flag = '\0';
					return (-1);
				}
				if (expand_flag == 1)
				{
					// flag = '\0';
					// printf("index : [%d]\n", *index);
					return (word_length);
				}
			}
		}
		else
		{
			++word_length;
		}
		*index += 1;
	}
	flag = '\0';
	index_env = -2;
	index_expand = 0;
	free(var_name);
	var_name = NULL;
	return (word_length);
}
