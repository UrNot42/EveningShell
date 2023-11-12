/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:44:56 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:17:14 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_new_content(t_expand_dollar expand_dollar_t)
{
	int				index;
	int				count;
	char			flag;
	char			**new_content;

	index = 0;
	count = 0;
	flag = '\0';
	new_content = ft_calloc(2, sizeof(char *));
	if (!new_content)
		return (NULL);
	while (expand_dollar_t.word[index])
	{
		if (create_new_content_on_one_char((t_expand_new_content){&new_content, 
				&count, &index, &flag, expand_dollar_t}) == -1)
		{
			ft_free_dstr(new_content);
			return (NULL);
		}
		++index;
	}
	++count;
	return (new_content);
}
