/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:53:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 21:45:38 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the var name contains in a string
 * 
 * @param str string containing the environment variable name
 * @param index_dollar index of the first char of the environment variable name
 * in the string str
 * @param size size of the environment variable name
 * @return char* environment variable name
 */
static char	*get_var_name(char *str, size_t index_dollar, size_t size)
{
	size_t	i;
	char	*var;

	i = 0;
	var = ft_calloc(size + 1, sizeof(char));
	if (!var)
		return (NULL);
	while (i < size)
	{
		var[i] = str[index_dollar];
		index_dollar++;
		i++;
	}
	return (var);
}

/**
 * @brief Get the content of a environment variable
 * 
 * @param env char ** of the environment variables
 * @param index index of the environment variable in the char ** env
 * @return char* content of the environment variable
 */
static char	*get_env_var_content(char **env, int index)
{
	size_t	i;
	size_t	j;
	size_t	content_length;
	char	*var_content;

	i = 0;
	if (index == -1)
		return (NULL);
	while (env[index][i] != '=')
		i++;
	i++;
	content_length = ft_strlen(env[index]) - i;
	var_content = ft_calloc(sizeof(char), content_length + 1);
	if (!var_content)
		return (NULL);
	j = 0;
	while (j < content_length)
	{
		var_content[j] = env[index][i];
		i++;
		j++;
	}
	return (var_content);
}

/**
 * @brief Creates a copy of the string with the environment variable name
 * replaced by its content
 * 
 * @param src string to copy
 * @param index_dollar index of the first char of the environment variable name
 * in the string src
 * @param expand_length length of the environment variable name
 * @param var_content content of the environment variable
 * @return char* new copy string with the environment variable name replaced by
 * its content
 */
char	*expand(char *src, size_t index_dollar,
	size_t expand_length, char *var_content)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	n;
	size_t	size;

	size = (ft_strlen(src) - expand_length) + ft_strlen(var_content);
	new_str = ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	n = 0;
	while (i < size)
	{
		if (i == index_dollar)
		{
			while (var_content && var_content[n])
				new_str[i++] = var_content[n++];
			j += expand_length + 1;
		}
		else
			new_str[i++] = src[j++];
	}
	return (free(src), free(var_content), new_str);
}

/**
 * @brief Expands all content of one token
 * 
 * @param token token containing the content to expand
 * @param env char ** of the environment variables
 * @return int 1 if success, -1 if there was an error of malloc
 */
int	expand_one_token(t_token token, char **env)
{
	size_t	i;
	size_t	index_dollar;
	size_t	expand_length;
	int		index_env;
	char	*var;

	i = 0;
	while (token.content[i])
	{
		expand_length = check_for_dollar(token.content[i], &index_dollar);
		if (expand_length)
		{
			index_dollar -= expand_length;
			var = get_var_name(token.content[i], index_dollar, expand_length);
			index_env = get_env_var_index(env, var);
			free(var);
			var = get_env_var_content(env, index_env);
			token.content[i] = expand(token.content[i],
					index_dollar - 1, expand_length, var);
			printf("new token.content : %s\n", token.content[i]);
			if (!token.content[i])
				return (-1);
		}
		i++;
	}
	return (1);
}
