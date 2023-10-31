/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:05:17 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 22:30:18 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_var_content(char **new_content, char *var_content, size_t *i)
{
	size_t	n;

	n = 0;
	while (var_content && var_content[n])
	{
		(*new_content)[*i] = var_content[n++];
		*i += 1;
	}
}

static	char	*merge_var_content(char *src, t_expand_params params)
{
	char	*new_content;
	size_t	i;
	size_t	j;
	size_t	size;

	size = (ft_strlen(src) - params.expand_length) + ft_strlen(params.var);
	new_content = ft_calloc(size + 1, sizeof(char));
	if (!new_content)
		return (free(src), free(params.var), NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i == params.index_dollar - 1)
		{
			j += params.expand_length + 1;
			if (params.var)
				copy_var_content(&new_content, params.var, &i);
			else
				new_content[i++] = src[j++];
		}
		else
			new_content[i++] = src[j++];
	}
	return (free(src), free(params.var), new_content);
}

static int	expand_one_content(char **content, char **env, int exit_status)
{
	t_expand_params	params;

	params.expand_length = check_for_dollar(*content, &params.index_dollar);
	while (params.expand_length)
	{
		params.index_dollar -= params.expand_length;
		if (set_var(&params, *content, env, exit_status) == -1)
			return (-1);
		*content = merge_var_content(*content, params);
		if (!content)
			return (-1);
		params.expand_length = check_for_dollar(*content, &params.index_dollar);
	}
	return (1);
}

int	expand_one_token(t_token token, char **env, int exit_status)
{
	int	i;

	i = -1;
	while (token.content[++i])
	{
		if (expand_one_content(&token.content[i], env, exit_status) == -1)
			return (-1);
	}
	return (1);
}

// echo $HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'
