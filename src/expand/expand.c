/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 12:18:22 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief expand only one compound
 *
 * @param compound compound to expand
 * @param env char ** of the environment variables
 * @param exit_status int containing the exit status of the last command
 * @return int 1 if the expansion was successful, -1 otherwise
 */
static int	expand_one_compound(t_compound *compound,
	char **env, int exit_status)
{
	int	j;

	j = 0;
	while (compound->content[j])
	{
		if (compound->type != HERE_DOC
			&& is_expand_dollar(compound->content[j]))
		{
			if (!expand_one_content(&compound, &j, env, exit_status))
				return (-1);
		}
		else
		{
			compound->content[j]
				= remove_quotes(compound->content[j]);
			if (!compound->content[j])
			{
				return (-1);
			}
		}
		++j;
	}
	return (1);
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
	int	i;

	i = 0;
	while ((*compound)[i].type != UNSET && (*compound)[i].type != -1)
	{
		if (expand_one_compound(&(*compound)[i], env, exit_status) == -1)
		{
			free_compound(*compound);
			ft_free_dstr(env);
			error_malloc_failed(true);
		}
		++i;
	}
}
