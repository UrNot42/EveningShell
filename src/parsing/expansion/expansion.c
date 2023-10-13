/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 11:24:48 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_for_dollar(char const *str, size_t *index_dollar)
{
	size_t	expand_length;

	*index_dollar = 0;
	expand_length = 0;
	while (str[*index_dollar])
	{
		if (str[*index_dollar] == '\'')
		{
			*index_dollar += 1;
			while (str[*index_dollar] && str[*index_dollar] != '\'')
				*index_dollar += 1;
			if (!str[*index_dollar])
				return (0);
		}
		if (str[*index_dollar] == '"')
		{
			*index_dollar += 1;
			while (str[*index_dollar] && str[*index_dollar] != '"')
			{
				if (str[*index_dollar] == '$')
				{
					*index_dollar += 1;
					while (str[*index_dollar]
						&& str[*index_dollar] != ' '
						&& str[*index_dollar] != '\t'
						&& str[*index_dollar] != '\''
						&& str[*index_dollar] != '"')
					{
						*index_dollar += 1;
						expand_length++;
					}
					return (expand_length);
				}
				*index_dollar += 1;
			}
			if (!str[*index_dollar])
				return (0);
		}
		if (str[*index_dollar] == '$')
		{
			*index_dollar += 1;
			while (str[*index_dollar]
				&& str[*index_dollar] != ' ' && str[*index_dollar] != '\t')
			{
				*index_dollar += 1;
				expand_length++;
			}
			return (expand_length);
		}
		*index_dollar += 1;
	}
	return (0);
}

char	*get_var(char *str, size_t index_dollar, size_t size)
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
	printf("var : %s\n", var);
	return (var);
}

// char	*get_var_content(char *var, char **env)
// {
// 	char	*var_content;
// 	size_t	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strcmp(var, env[i][0]))
// 		{
// 			var_content = ft_strdup(env[i][1]);
// 			if (!var_content)
// 				return (NULL);
// 			printf("var_content : %s\n", var_content);
// 			return (var_content);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

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
			while (var_content[n])
			{
				new_str[i] = var_content[n];
				i++;
				n++;
			}
			j += expand_length + 1;
		}
		else
		{
			new_str[i] = src[j];
			i++;
			j++;
		}
	}
	free(src);
	return (new_str);
}

char	*check_one_token(t_token token)
{
	size_t	i;
	size_t	index_dollar;
	size_t	expand_length;
	// char	*var;

	i = 0;
	while (token.content[i])
	{
		expand_length = check_for_dollar(token.content[i], &index_dollar);
		if (expand_length)
		{
			index_dollar -= expand_length;
			// get_var(token.content[i], index_dollar, expand_length);
			// if (!var)
				// return (NULL);
			// var = get_var_content(NULL, NULL);
			// if (!var)
				// return (NULL);
			token.content[i] = expand(token.content[i],
					index_dollar - 1, expand_length, "var_expanded");
			printf("new token.content : %s\n", token.content[i]);
			if (!token.content[i])
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	expansion(t_token **token, char **env)
{
	size_t	i;
	char	*var;

	(void)env;
	i = 0;
	while ((*token)[i].type != -1)
	{
		var = check_one_token(*token[i]);
		if (var != NULL)
		{
			;
		}
		i++;
	}
}
