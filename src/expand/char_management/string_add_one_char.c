/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_add_one_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:44:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 17:27:33 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_add_one_char(char *str_to_free, char c)
{
	int		i;
	int		length;
	char	*new_str;

	i = 0;
	if (!str_to_free)
	{
		new_str = ft_calloc(2, sizeof(char));
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		return (new_str);
	}
	length = ft_strlen(str_to_free) + 1;
	new_str = ft_calloc(length + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str_to_free[i])
	{
		new_str[i] = str_to_free[i];
		++i;
	}
	new_str[i] = c;
	free(str_to_free);
	return (new_str);
}
