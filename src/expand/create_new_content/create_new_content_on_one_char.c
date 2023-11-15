/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_content_on_one_char.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:27:26 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:03:47 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add one char to the word. Free the old word and
 * replace it the by the new one, malloc size + 1 and the new char at the end.
 * 
 * @param word char ** word to add the char
 * @param new_char char to add
 * @return int 1 if success, -1 if error of malloc
 */
int	new_char_in_word(char **word, char new_char)
{
	*word = str_add_one_char(*word, new_char);
	if (!*word)
		return (-1);
	return (1);
}

/**
 * @brief Add char that is in single quote
 * 
 * @param new_content char *** new_content to add the char
 * @param count int * count of the new_content
 * @param flag char * flag to know if the char is in single quote or not
 * @param character char to add
 * @return int 1 if success, -1 if error of malloc
 */
static int	add_char_in_single_quote(char ***new_content, int *count,
	char *flag, char character)
{
	if (*flag == '\0')
	{
		*flag = '\'';
	}
	else if (*flag == '\'')
	{
		*flag = '\0';
	}
	else if (*flag == '"')
	{
		if (new_char_in_word(new_content[*count], character) == -1)
			return (-1);
	}
	return (1);
}

/**
 * @brief Add char that is in double quote
 * 
 * @param new_content char *** new_content to add the char
 * @param count int * count of the new_content
 * @param flag char * of the flag of quote (equal to " or ' or \0)
 * @param character char to add
 * @return int 1 if success, -1 if error of malloc
 */
static int	add_char_in_double_quote(char ***new_content, int *count,
	char *flag, char character)
{
	if (*flag == 0)
	{
		*flag = '"';
	}
	else if (*flag == '\'')
	{
		if (new_char_in_word(new_content[*count], character) == -1)
			return (-1);
	}
	else if (*flag == '"')
	{
		*flag = '\0';
	}
	return (1);
}

/**
 * @brief Create a new content and expand the dollar if it is not in single quote
 * 
 * @param t_enc t_expand_new_content struct with the new_content, the count,
 * the index, the flag and the t_expand_dollar struct
 * @return int 1 if success, -1 if error of malloc
 */
static int	create_new_content_dollar(t_expand_new_content t_enc)
{
	if (*t_enc.flag == '\'')
	{
		if (new_char_in_word(t_enc.new_content[*t_enc.count],
				t_enc.t_ed.word[*t_enc.index]) == -1)
			return (-1);
	}
	else if (*t_enc.flag == 0 || *t_enc.flag == '"')
	{
		if (expand_dollar(t_enc) == -1)
			return (-1);
	}
	return (1);
}

/**
 * @brief Add one char to the new content.
 * Add the char to the new_content[count] string. Or create a new string in
 * new_content[count + 1] if the char is a separator between no quoted.
 * 
 * @param t_enc t_expand_new_content struct with the new_content, the count,
 * the index, the flag and the t_expand_dollar struct
 * @return int 1 if success, -1 if error of malloc
 */
int	create_new_content_on_one_char(t_expand_new_content t_enc)
{
	if (t_enc.t_ed.word[*t_enc.index] == '\'')
	{
		if (add_char_in_single_quote(t_enc.new_content,
				t_enc.count, t_enc.flag, t_enc.t_ed.word [*t_enc.index]) == -1)
			return (-1);
	}
	else if (t_enc.t_ed.word[*t_enc.index] == '"')
	{
		if (add_char_in_double_quote(t_enc.new_content,
				t_enc.count, t_enc.flag, t_enc.t_ed.word[*t_enc.index]) == -1)
			return (-1);
	}
	else if (t_enc.t_ed.word[*t_enc.index] == '$')
	{
		if (create_new_content_dollar(t_enc) == -1)
			return (-1);
	}
	else
	{
		if (new_char_in_word((t_enc).new_content[*t_enc.count],
				t_enc.t_ed.word [*t_enc.index]) == -1)
			return (-1);
	}
	return (1);
}
