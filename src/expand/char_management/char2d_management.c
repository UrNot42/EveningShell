/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2d_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:45:40 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 11:12:37 by aoberon          ###   ########.fr       */
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
 * @brief Copy the array_to_copy, from start_copy, into the new_array at index.
 * If a malloc failed, free the new_array array_to_copy, and return -1.
 * Otherwise return the index of the last element copied.
 * 
 * @param new_array char *** to copy the array_to_copy into
 * @param index int * index of the new_array where to copy
 * @param array_to_copy char ** array to copy
 * @param start_copy int index of the array_to_copy where to start the copy
 * @return int -1 if a malloc failed, start_copy otherwise
 */
int	copy_char2d(char **new_array, int *index,
	char **array_to_copy, int start_copy)
{
	while (array_to_copy[start_copy])
	{
		new_array[*index] = ft_strdup(array_to_copy[start_copy]);
		if (!new_array[*index])
			return (ft_free_dstr(array_to_copy),
				ft_rewind_free(new_array, *index), -1);
		++start_copy;
		*index += 1;
	}
	return (start_copy);
}

/**
 * @brief Copy the array_to_copy into the new_array at index,
 * and stop the copy at n.
 * If a malloc failed, free the new_array, array_to_copy and return -1.
 * Otherwise return 1.
 * 
 * @param new_array char *** to copy the array_to_copy into
 * @param index int * index of the new_array where to copy
 * @param array_to_copy char ** array to copy
 * @param n int index of the array_to_copy where to stop the copy
 * @return int -1 if a malloc failed, 1 otherwise
 */
int	copy_nchar2d(char **new_array, int *index,
	char **array_to_copy, int n)
{
	while (array_to_copy[*index] && *index < n)
	{
		new_array[*index] = ft_strdup(array_to_copy[*index]);
		if (!new_array[*index])
			return (ft_free_dstr(array_to_copy),
				ft_rewind_free(new_array, *index), -1);
		*index += 1;
	}
	return (1);
}

/**
 * @brief Create a new array (char **) with the content of
 * array2 inserted in array1 at index. And free array1 and array2.
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
	char	**new_array;

	new_array = ft_calloc(ft_char2d_length(array1) + ft_char2d_length(array2)
			+ 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	if (copy_nchar2d(new_array, &i, array1, *index) == -1)
	{
		return (ft_free_dstr(array2), NULL);
	}
	j = copy_char2d(new_array, &i, array2, 0);
	if (j == -1)
	{
		return (ft_free_dstr(array1), NULL);
	}
	if (copy_char2d(new_array, &i, array1, *index + 1) == -1)
	{
		return (ft_free_dstr(array2), NULL);
	}
	(ft_free_dstr(array1), ft_free_dstr(array2));
	*index += j - 1;
	return (new_array);
}
