/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/07 21:05:53 by aoberon          ###   ########.fr       */
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
				if (expand_one_content(&(*compound)[i].content[j], env, exit_status) == -1)
					(free_compound(*compound), error_failed_malloc());
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
