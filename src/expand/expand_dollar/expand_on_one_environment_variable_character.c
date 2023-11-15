/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_on_one_environment_variable_characte        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:21 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 15:07:15 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_word_in_content(char ***new_content, int *count)
{
	*count += 1;
	*new_content = char2d_add_one_string(*new_content);
	if (!*new_content)
		return (-1);
	return (1);
}

static int	expand_env_var_single_quote(char ***new_content, int *count,
	char *flag)
{
	if (*flag == '\0')
		*flag = '\'';
	else if (*flag == '\'')
	{
		*flag = '\0';
		if (new_word_in_content(new_content, count) == -1)
			return (-1);
	}
	return (1);
}

static int	expand_env_var_double_quote(char ***new_content, int *count,
	char *flag)
{
	if (*flag == 0)
		*flag = '"';
	else if (*flag == '"')
	{
		*flag = '\0';
		if (new_word_in_content(new_content, count) == -1)
			return (-1);
	}
	return (1);
}

int	expand_on_one_env_var_char(char ***new_content, int *count,
	char env_var_char, char *flag)
{
	if (((env_var_char != ' ' && env_var_char != '\t')))
	{
		if (new_char_in_word(&(*new_content)[*count], env_var_char) == -1)
			return (-1);
	}
	else if ((env_var_char == ' ' || env_var_char == '\t'))
	{
		if (*flag == '\0')
		{
			if ((*new_content)[*count] && (*new_content)[*count][0] != '\0')
				if (new_word_in_content(new_content, count) == -1)
					return (-1);
		}
		else if (*flag == '\'' || *flag == '"')
		{
			if (new_char_in_word(&(*new_content)[*count], env_var_char) == -1)
				return (-1);
		}
	}
	else if (env_var_char == '\'')
	{
		if (expand_env_var_single_quote(new_content, count, flag) == -1)
			return (-1);
	}
	else if (env_var_char == '"')
	{
		if (expand_env_var_double_quote(new_content, count, flag) == -1)
			return (-1);
	}
	return (1);
}
