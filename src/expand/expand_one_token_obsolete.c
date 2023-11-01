/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:53:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 22:18:44 by aoberon          ###   ########.fr       */
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
	printf("var_content: %s\n", var_content);
	return (var_content);
}

char	*copy_var(char *new_str, char *var_content, size_t *i)
{
	size_t	n;

	n = 0;
	while (var_content && var_content[n])
	{
		new_str[*i] = var_content[n++];
		*i += 1;
	}
	return (new_str);
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
char	*expand_var_env(char *src, size_t index_dollar,
	size_t expand_length, char *var_content)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	size;

	size = (ft_strlen(src) - expand_length) + ft_strlen(var_content);
	new_str = ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (free(src), free(var_content), NULL);
	i = 0;
	j = 0;
	printf("INDEX_DOLLAR: %zu\n", index_dollar);
	while (i < size)
	{
		if (i == index_dollar)
		{
			j += expand_length + 1;
			if (var_content)
				new_str = copy_var(new_str, var_content, &i);
			else
				new_str[i++] = src[j++];
		}
		else
			new_str[i++] = src[j++];
	}
	return (free(src), free(var_content), new_str);
}

// int	expand_one_content(char *content, char **env, int exit_status)
// {
// 	size_t	index_dollar;
// 	size_t	expand_length;
// 	int		index_env;
// 	char	*var;

// 	expand_length = check_for_dollar(content, &index_dollar);
// 	while (expand_length)
// 	{
// 		index_dollar -= expand_length;
// 		var = get_var_name(content, index_dollar, expand_length);
// 		if (!var)
// 			return (-1);
// 		if (!ft_strcmp(var, "?"))
// 		{
// 			free(var);
// 			var = ft_itoa(exit_status);
// 		}
// 		else
// 		{
// 			index_env = get_env_var_index(env, var);
// 			free(var);
// 			var = NULL;
// 			if (index_env != -1)
// 			{
// 				var = get_env_var_content(env, index_env);
// 				if (!var)
// 					return (-1);
// 			}
// 		}
// 		content = expand_var_env(content,
// 				index_dollar - 1, expand_length, var);
// 		if (!content)
// 			return (-1);
// 		expand_length = check_for_dollar(content, &index_dollar);
// 	}
// }

/**
 * @brief Expands all content of one token
 * 
 * @param token token containing the content to expand
 * @param env char ** of the environment variables
 * @param exit_status int contains the exit status of the last command
 * @return int 1 if success, -1 if there was an error of malloc
 */
int	expand_one_token(t_token token, char **env, int exit_status)
{
	size_t	i;
	size_t	index_dollar;
	size_t	expand_length;
	int		index_env;
	char	*var;

	i = -1;
	while (token.content[++i])
	{
		printf("content: %s\n", token.content[i]);
		expand_length = check_for_dollar(token.content[i], &index_dollar);
		printf("expand_length: %zu\n", expand_length);
		printf("index_dollar: %zu\n", index_dollar);
		while (expand_length)
		{
			index_dollar -= expand_length;
			printf("index_dollar: %zu\n", index_dollar);
			var = get_var_name(token.content[i], index_dollar, expand_length);
			if (!var)
				return (-1);
			if (!ft_strcmp(var, "?"))
			{
				free(var);
				var = ft_itoa(exit_status);
			}
			else
			{
				index_env = get_env_var_index(env, var);
				free(var);
				var = NULL;
				if (index_env != -1)
				{
					var = get_env_var_content(env, index_env);
					if (!var)
						return (-1);
				}
			}
			printf("content: %s\n", token.content[i]);
			token.content[i] = expand_var_env(token.content[i],
					index_dollar - 1, expand_length, var);
			printf("content: %s\n", token.content[i]);
			if (!token.content[i])
				return (-1);
			expand_length = check_for_dollar(token.content[i], &index_dollar);
		}
	}
	return (1);
}

// echo $HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'

// typedef struct s_expand
// {
// 	;
// }	t_expand;

// int	expand_one_token(t_token token, char **env, int exit_status)
// {
// 	size_t	i;
// 	size_t	index_dollar;
// 	size_t	expand_length;
// 	int		index_env;
// 	char	*var;
// 	t_expand	expand;
	

// 	i = -1;
// 	expand.env = env;
// 	expand.exit_status = exit_status;
// 	while (token.content[++i])
// 	{
// 		expand.content = &token.content[i];
// 		if (expand_one_content(expand))
// 			(void)env;
// 	}
// 	return (1);
// }

// int	expand_one_content(t_expand expand)
// {
// 	var;

// 	expand_length = check_for_dollar(expand->content, &index_dollar);
// 	while (expand_length)
// 	{
// 		index_dollar -= expand_length;
// 		var = get_var_name(expand->content, index_dollar, expand_length);
// 		if (!var)
// 			return (-1);
// 		if (!ft_strcmp(var, "?"))
// 		{
// 			(free(var),
// 			var = ft_itoa(expand.exit_status);
// 		}
// 		else
// 		{
// 			index_env = get_env_var_index(expand.env, var);
// 			free(var);
// 			var = NULL;
// 			if (index_env != -1)
// 			{
// 				var = get_env_var_content(expand.env, index_env);
// 				if (!var)
// 					return (-1);
// 			}
// 		}
// 		expand->content = expand_var_env(expand->content,
// 				index_dollar - 1, expand_length, var);
// 		if (!expand->content)
// 			return (-1);
// 		expand_length = check_for_dollar(expand->content, &index_dollar);
// 	}
// 	return (1);
// }
