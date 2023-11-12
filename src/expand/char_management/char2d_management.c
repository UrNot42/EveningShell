/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2d_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:45:40 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 17:29:18 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_char2d_length(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	**char2d_add_one_string(char **array)
{
	int		i;
	char	**new_array;

	new_array = ft_calloc(ft_char2d_length(array) + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		++i;
	}
	ft_free_dstr(array);
	return (new_array);
}

char	**insert_char2d_into_char2d(char **array1, char **array2, int *index)
{
	int		i;
	int		j;
	int		k;
	char	**new_array;

	new_array = ft_calloc(ft_char2d_length(array1) + ft_char2d_length(array2)
			+ 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < *index)
	{
		new_array[i] = ft_strdup(array1[i]);
		++i;
	}
	j = 0;
	while (array2[j])
		new_array[i++] = ft_strdup(array2[j++]);
	k = 1;
	while (array1[*index + k])
		new_array[i++] = ft_strdup(array1[*index + k++]);
	ft_free_dstr(array1);
	ft_free_dstr(array2);
	*index += j;
	return (new_array);
}
