/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expand_one_content.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:59:50 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 17:22:57 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_dollar(char ***new_content, int *count, char *words, int *index, char **env, int exit_status)
{
	char	*var_name;
	int		var_name_length;
	int		i;
	int		j;
	int		index_env;
	char	flag;

	var_name_length = get_var_name_length(words, *index);
	if (!retrieve_var_name(&var_name, words, *index, var_name_length))
		return (-1);
	j = 0;
	while (j++ < var_name_length)
	{
		*index += 1;
	}
	if (!ft_strcmp(var_name, "?"))
	{
		char	str_itoa[12];
		free(var_name);
		// *size_word += 1;
		// printf("%d", exit_status);
		ft_itoa_no_malloc(exit_status, str_itoa);
		(*new_content)[*count] = ft_safe_strjoin((*new_content)[*count], str_itoa);
		if (!(*new_content))
			return (-1);
		return (1);
	}
	index_env = get_env_var_index(env, var_name);
	free(var_name);
	i = 0;
	if (index_env != -1)
	{
		while (env[index_env][i] != '=')
			++i;
		++i;
		flag = '\0';
		while (env[index_env][i])
		{
			if (((env[index_env][i] != ' ' && env[index_env][i] != '\t')))
			{
				// *size_word += 1;
				// printf("%c", env[index_env][i]);
				// printf("\n| count = [%d] | content = %s | env[%d][%d] = %c |\n", *count, (*new_content)[*count], index_env, i, env[index_env][i]);
				(*new_content)[*count] = str_add_one_char((*new_content)[*count], env[index_env][i]);
				if (!(*new_content)[*count])
					return (-1);
			}
			else if ((env[index_env][i] == ' ' || env[index_env][i] == '\t'))
			{
				// printf("	|	size_word : [%d]\n", *size_word);
				// *size_word = 0;
				*count += 1;
				// printf("\n");
				*new_content = char2d_add_one_string(*new_content);
				if (!*new_content)
					return (-1);
			}
			else if (env[index_env][i] == '\'')
			{
				if (flag == '\0')
				{
					flag = '\'';
				}
				else if (flag == '\'')
				{
					flag = '\0';
					// printf("	|	size_word : [%d]\n", *size_word);
					// *size_word = 0;
					*count += 1;
					// printf("\n");
					*new_content = char2d_add_one_string(*new_content);
					if (!*new_content)
						return (-1);
				}
			}
			else if (env[index_env][i] == '"')
			{
				if (flag == 0)
				{
					flag = '"';
				}
				else if (flag == '"')
				{
					flag = '\0';
					// printf("	|	size_word : [%d]\n", *size_word);
					// *size_word = 0;
					*count += 1;
					// printf("\n");
					*new_content = char2d_add_one_string(*new_content);
					if (!*new_content)
						return (-1);
				}
			}
			++i;
		}
	}
	return (1);
}

// ====================================================================

char	**create_new_content(char *words, char **env, int exit_status)
{
	int				index;
	int				count;
	// int				size_word;
	char			flag;
	char			**new_content;
	// t_expand_params	params;

	index = 0;
	count = 0;
	// size_word = 0;
	flag = '\0';
	new_content = ft_calloc(2, sizeof(char *));
	if (!new_content)
		return (NULL);
	while (words[index])
	{
		// debug_expand(content, index);
		if (words[index] == '\'')
		{
			if (flag == '\0')
			{
				flag = '\'';
			}
			else if (flag == '\'')
			{
				flag = '\0';
			}
			else if (flag == '"')
			{
				// ++size_word;
				// printf("%c", words[index]);
				new_content[count] = str_add_one_char(new_content[count], words[index]);
				if (!new_content[count])
				{
					ft_free_dstr(new_content);
					return (NULL);
				}
			}
		}
		else if (words[index] == '"')
		{
			if (flag == 0)
			{
				flag = '"';
			}
			else if (flag == '\'')
			{
				// ++size_word;
				// printf("%c", words[index]);
				new_content[count] = str_add_one_char(new_content[count], words[index]);
				if (!new_content[count])
				{
					ft_free_dstr(new_content);
					return (NULL);
				}
			}
			else if (flag == '"')
			{
				flag = '\0';
			}
		}
		else if (words[index] == '$')
		{
			if (flag == '\'')
			{
				// ++size_word;
				// printf("%c", words[index]);
				new_content[count] = str_add_one_char(new_content[count], words[index]);
				if (!new_content[count])
				{
					ft_free_dstr(new_content);
					return (NULL);
				}
			}
			else if (flag == 0 || flag == '"')
			{
				if (expand_dollar(&new_content, &count, words, &index, env, exit_status) == -1)
					return (NULL);
			}
		}
		else
		{
			// ++size_word;
			// printf("%c", words[index]);
			new_content[count] = str_add_one_char(new_content[count], words[index]);
			if (!new_content[count])
			{
				ft_free_dstr(new_content);
				return (NULL);
			}
		}
		++index;
	}
	++count;
	// printf("	|	size_word : [%d]\n", size_word);
	// printf("\ncount : [%d]\n", count);
	// printf("------------------------------\n");
	return (new_content);
}
