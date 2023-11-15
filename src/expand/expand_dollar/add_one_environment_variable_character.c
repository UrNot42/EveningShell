/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_one_environment_variable_character.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:21 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:03:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a char ** copy of the new_content with a size of count + 1
 * 
 * @param new_content char *** of the new_content. Free the old new_content
 *  and replace it the by the new one.
 * @param count int * count of the size of the new_content
 * @return int -1 if malloc failed, 1 otherwise
 */
static int	new_word_in_content(char ***new_content, int *count)
{
	*count += 1;
	*new_content = char2d_add_one_string(*new_content);
	if (!*new_content)
		return (-1);
	return (1);
}

/**
 * @brief Add one char to the word of the new_content with single quote rules.
 * Free the old word and replace it the by the new one, malloc size + 1 and
 * the new char at the end.
 * 
 * @param new_content char *** of the new_content
 * @param count int * of the index of the new_content
 * @param flag char * of the flag of quote (equal to " or ' or \0)
 * @return int -1 if malloc failed, 1 otherwise
 */
static int	add_char_env_var_in_single_quote(char ***new_content, int *count,
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

/**
 * @brief Add one char to the word of the new_content with double quotes rules.
 * Free the old word and replace it the by the new one, malloc size + 1 and
 * the new char at the end.
 * 
 * @param new_content char *** of the new_content
 * @param count int * of the index of the new_content
 * @param flag char * of the flag of quote (equal to " or ' or \0)
 * @return int -1 if malloc failed, 1 otherwise
 */
static int	add_char_env_var_in_double_quote(char ***new_content, int *count,
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

/**
 * @brief Expand one char of the environment variable
 * 
 * @param new_content char *** of the new_content
 * @param count int * of the index of the new_content
 * @param env_var_char char of the environment variable to expand
 * @param flag char * of the flag of quote (equal to " or ' or \0)
 * @return int -1 if malloc failed, 1 otherwise
 */
int	add_one_env_var_char(char ***new_content, int *count,
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
		else if ((*flag == '\'' || *flag == '"')
			&& new_char_in_word(&(*new_content)[*count], env_var_char) == -1)
			return (-1);
	}
	else if (env_var_char == '\''
		&& add_char_env_var_in_single_quote(new_content, count, flag) == -1)
		return (-1);
	else if (env_var_char == '"'
		&& add_char_env_var_in_double_quote(new_content, count, flag) == -1)
		return (-1);
	return (1);
}
