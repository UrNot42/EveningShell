/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   total_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:20:15 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/10 20:38:12 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_manage(char *content, char **env, int exit_status, int *index, int *total_length, int *index_env, int *index_expand)
{
	char	*var_name;
	int		var_name_length;
	int		j;

	var_name_length = get_varname_length(content, *index);
	if (!retrieve_var_name(&var_name, content, *index, var_name_length))
		return (-1);
	j = 0;
	while (j++ < var_name_length)
		*index += 1;
	if (!strcmp(var_name, "?"))
	{
		free(var_name);
		*total_length += ft_nbrlen(exit_status);
		return (2);
	}
	*index_env = get_env_var_index(env, var_name);
	free(var_name);
	if (*index_env == -1)
		return (1);
	while (env[*index_env][*index_expand] != '=')
		*index_expand += 1;
	*index_expand += 1;
	return (1);
}

static int	expand_dollar_total_length(char *content, char **env, int exit_status, int *index, int *total_length)
{
	int		index_env;
	int		index_expand;
	int		env_var_flag;
	char	flag;

	flag = '\0';
	index_expand = 0;
	env_var_flag = env_var_manage(content, env, exit_status, index, total_length, &index_env, &index_expand);
	if (env_var_flag == -1 || env_var_flag == 2)
		return (env_var_flag);
	if (index_env == -1)
		return (0);
	while (env[index_env][index_expand])
	{
		if (env[index_env][index_expand] != ' ' && env[index_env][index_expand] != '\t')
		{
			*total_length += 1;
		}
		else if (env[index_env][index_expand] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
		}
		else if (env[index_env][index_expand] == '"')
		{
			if (flag == '\0')
				flag = '"';
		}
		++index_expand;
	}
	return (0);
}

int	total_length(char *content, char **env, int exit_status)
{
	int		index;
	int		total_length;
	int		expand_flag;
	char	flag;

	index = 0;
	total_length = 0;
	flag = '\0';
	while (content[index])
	{
		if (content[index] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
			else if (flag == '\'')
				flag = '\0';
			else if (flag == '"')
			{
				++total_length;
			}
		}
		else if (content[index] == '"')
		{
			if (flag == '\0')
				flag = '"';
			else if (flag == '\'')
			{
				++total_length;
			}
			else if (flag == '"')
				flag = '\0';
		}
		else if (content[index] == '$')
		{
			if (flag == '\'')
			{
				++total_length;
			}
			else if (flag == '\0' || flag == '"')
			{
				expand_flag = expand_dollar_total_length(content, env, exit_status, &index, &total_length);
				if (expand_flag == -1)
				{
					flag = '\0';
					return (-1);
				}
			}
		}
		else
		{
			++total_length;
		}
		++index;
	}
	flag = '\0';
	return (total_length);
}
