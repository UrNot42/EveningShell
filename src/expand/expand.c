/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/10 22:17:30 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dollar_expand(char *word)
{
	size_t	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			++i;
			while (word[i] && word[i] != '\'')
				++i;
			if (!word[i])
				return (false);
		}
		if (word[i] == '"')
		{
			++i;
			while (word[i] && word[i] != '"')
			{
				if (word[i] == '$')
					return (true);
				++i;
			}
			if (!word[i])
				return (0);
		}
		if (word[i] == '$')
		{
			return (true);
		}
		++i;
	}
	return (false);
}

char	**expand_new_content(t_compound *compound, char **env, int exit_status, int i, int j)
{
	int		current_content_size;
	int		new_one_content_size;
	int		new_size;
	char	**new_one_content;
	char	**new_content;

	new_one_content = expand_one_content(compound[i].content[j], env, exit_status);
	if (!new_one_content)
		return (NULL);
	new_one_content_size = 0;
	while (new_one_content[new_one_content_size])
		++new_one_content_size;
	current_content_size = 0;
	while (compound[i].content[current_content_size])
		++current_content_size;
	new_size = (current_content_size -1) + new_one_content_size + 1;
	new_content = malloc(sizeof(char *) * new_size);
	if (!new_content)
		return (NULL);
	int		k;
	k = 0;
	while (k < j)
	{
		new_content[k] = compound[i].content[k];
		++k;
	}
	int		l;
	l = 0;
	while (l < new_one_content_size)
	{
		new_content[k] = new_one_content[l];
		++k;
		++l;
	}
	++j;
	while (k < new_size)
	{
		new_content[k] = compound[i].content[j];
		++k;
		++j;
	}
	ft_free_dstr(compound[i].content);
	return (new_content);
}

/**
 * @brief Expands one by one each content's compound, compound by compound
 * Expand means to replace the environment variables (starting with $) by their
 * content (contained in the char ** env) And remove the quotes
 *
 * @param compound compound containing the content to expand
 * @param env char ** of the environment variables
 * @param exit_status int containing the exit status of the last command
 */
void	expand(t_compound **compound, char **env, int exit_status)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*compound)[i].type != UNSET && (*compound)[i].type != -1)
	{
		j = 0;
		while ((*compound)[i].content[j])
		{
			if ((*compound)[i].type != HERE_DOC && is_dollar_expand((*compound)[i].content[j]))
			{
				(*compound)[i].content = expand_new_content(*compound, env, exit_status, i, j);
				if (!(*compound)[i].content)
					(free_compound(*compound), error_failed_malloc());
				// expand_one_content((*compound)[i].content[j], env, exit_status);
				// if (!expand_one_content(&(*compound)[i].content[j], env, exit_status))
					// (free_compound(*compound), error_failed_malloc());
			}
			else
			{
				(*compound)[i].content[j] = remove_quotes((*compound)[i].content[j]);
				if (!(*compound)[i].content[j])
				{
					(free_compound(*compound), error_failed_malloc());
				}
			}
			++j;
		}
		++i;
		// if ((*compound)[i].type != HERE_DOC)
		// {
		// 	if (expand_one_compound((*compound)[i], env, exit_status) == -1)
		// 	{
		// 		(free_compound(*compound), error_failed_malloc());
		// 	}
		// }
		// j = 0;
		// while ((*compound)[i].content[j])
		// {
		// 	printf("content[%zu][%zu] = %s\n", i, j, (*compound)[i].content[j]);
		// 	(*compound)[i].content[j]
		// 		= remove_quotes((*compound)[i].content[j]);
		// 	if (!(*compound)[i].content[j++])
		// 	{
		// 		(free_compound(*compound), error_failed_malloc());
		// 	}
		// }
		// i++;
	}
}
