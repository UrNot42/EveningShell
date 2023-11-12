/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_content_on_one_char.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:27:26 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:20:06 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_char_in_word(char **word, char new_char)
{
	*word = str_add_one_char(*word, new_char);
	if (!*word)
		return (-1);
	return (1);
}

static int	create_new_content_in_single_quote(char ***new_content, int *count,
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

static int	create_new_content_in_double_quote(char ***new_content, int *count,
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
		if (expand_dollar(t_enc.new_content, t_enc.count,
				t_enc.index, t_enc.t_ed) == -1)
			return (-1);
	}
	return (1);
}

int	create_new_content_on_one_char(t_expand_new_content t_enc)
{
	if (t_enc.t_ed.word[*t_enc.index] == '\'')
	{
		if (create_new_content_in_single_quote(t_enc.new_content,
				t_enc.count, t_enc.flag, t_enc.t_ed.word [*t_enc.index]) == -1)
			return (-1);
	}
	else if (t_enc.t_ed.word[*t_enc.index] == '"')
	{
		if (create_new_content_in_double_quote(t_enc.new_content,
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
