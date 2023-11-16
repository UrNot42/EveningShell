/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2d_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:45:40 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 09:14:35 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the length of a char ** array
 * 
 * @param str char ** array to get the length
 * @return int the length of the array
 */
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

/**
 * @brief Create a char ** copy of the array with a size + 1
 * And free the old array.
 * 
 * @param array char ** array to copy
 * @return char** the new array
 */
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

/**
 * @brief Create a new array (char **) with the content of
 * array2 inserted in array1 at the index. And free array1 and array2.
 * 
 * @param array1 Original array char **
 * @param array2 New array char ** to insert in array1
 * @param index int * of the index of array1 where to insert array2
 * @return char** the new array
 */
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
	*index += j - 1;
	return (new_array);
}
