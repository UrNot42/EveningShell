/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_one_compound.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:53:09 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/10 22:47:18 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_dollar_copy_length(char **new_word, char *content, char **env, int exit_status, int *index_src, int *index_dst, int *index_env, int *index_expand, char **var_name)
{
	int	var_name_length;

	if (*var_name == NULL)
	{
		var_name_length = get_varname_length(content, *index_src);
		if (!retrieve_var_name(var_name, content, *index_src, var_name_length))
		{
			return (-1);
		}
		int	j;
		j = 0;
		while (j++ < var_name_length)
		{
			*index_src += 1;
		}
		if (!strcmp(*var_name, "?"))
		{
			char	exit_status_str[12];
			*index_env = -2;
			*index_expand = 0;
			free(*var_name);
			*var_name = NULL;
			ft_itoa_no_malloc(exit_status, exit_status_str);
			*index_dst += ft_nbrlen(exit_status);
			*new_word = ft_safe_strjoin(*new_word, exit_status_str);
			if (!*new_word)
				return (-1);
			return (0);
		}
		*index_env = get_env_var_index(env, *var_name);
		if (*index_env == -1)
		{
			*index_env = -2;
			*index_expand = 0;
			free(*var_name);
			*var_name = NULL;
			return (0);
		}
		while (env[*index_env][*index_expand] != '=')
			*index_expand += 1;
	*index_expand += 1;
	}

	char	flag;
	flag = '\0';
	while (env[*index_env][*index_expand])
	{
		if (env[*index_env][*index_expand] != ' ' && env[*index_env][*index_expand] != '\t')
		{
			(*new_word)[*index_dst] = env[*index_env][*index_expand];
			*index_dst += 1;
		}
		else if (env[*index_env][*index_expand] == ' ' || env[*index_env][*index_expand] == '\t')
		{
			*index_expand += 1;
			return (1);
		}
		else if (env[*index_env][*index_expand] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
			else if (flag == '\'')
				return (1);
		}
		else if (env[*index_env][*index_expand] == '"')
		{
			if (flag == '\0')
				flag = '"';
			else if (flag == '"')
				return (1);
		}
		*index_expand += 1;
	}
	*index_env = -2;
	*index_expand = 0;
	free(*var_name);
	*var_name = NULL;
	return (0);
}

char	*copy_word(char *content, char **env, int exit_status, int length_word,
	int *index_src)
{
	char		*new_word;
	int			index_dst;
	int			expand_flag;

	static char	flag = '\0';
	static int	index_expand = 0;
	static int	index_env = -2;
	static char	*var_name = NULL;

	index_dst = 0;
	new_word = ft_calloc(length_word + 1, sizeof(char));
	if (!new_word)
		return (NULL);

	if (var_name)
	{
		expand_flag = expand_dollar_copy_length(&new_word, content, env, exit_status, index_src, &index_dst, &index_env, &index_expand, &var_name);
		*index_src += 1;
		if (expand_flag == -1)
		{
			free(new_word);
			flag = '\0';
			return (NULL);
		}
		if (expand_flag == 1)
		{
			flag = '\0';
			return (new_word);
		}
	}
	while (content[*index_src])
	{
		if (content[*index_src] == '\'')
		{
			if (flag == '\0')
				flag = '\'';
			else if (flag == '\'')
				flag = '\0';
			else if (flag == '"')
			{
				printf("index_dst : [%d]/[%d]\n", index_dst, length_word);
				new_word[index_dst] = content[*index_src];
				++index_dst;
			}
		}
		else if (content[*index_src] == '"')
		{
			if (flag == '\0')
				flag = '"';
			else if (flag == '\'')
			{
				new_word[index_dst] = content[*index_src];
				++index_dst;
			}
			else if (flag == '"')
				flag = '\0';
		}
		else if (content[*index_src] == '$')
		{
			if (flag == '\'')
			{
				new_word[index_dst] = content[*index_src];
				++index_dst;
			}
			else if (flag == '\0' || flag == '"')
			{
				expand_flag = expand_dollar_copy_length(&new_word, content, env, exit_status, index_src, &index_dst, &index_env, &index_expand, &var_name);
				if (expand_flag == -1)
				{
					free(new_word);
					flag = '\0';
					return (NULL);
				}
				if (expand_flag == 1)
				{
					// flag = '\0';
					return (new_word);
				}
			}
		}
		else
		{
			new_word[index_dst] = content[*index_src];
			++index_dst;
		}
		*index_src += 1;
	}
	flag = '\0';
	return (new_word);
}

char	**create_new_array(char *content, char **env, int exit_status, int count)
{
	int		index_count;
	int		world_length;
	int		index_content_length;
	int		index_content_copy;
	char	**new_array;

	new_array = ft_calloc(count + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	index_count = 0;
	index_content_length = 0;
	index_content_copy = 0;
	while (index_count < count)
	{
		world_length = word_length_expand(content, env, exit_status, &index_content_length);
		new_array[index_count] = copy_word(content, env,
				exit_status, world_length, &index_content_copy);
		if (!new_array[index_count])
			return (ft_rewind_free(new_array, index_count));
		++index_count;
	}
	return (new_array);
}

int	word_count(char *content, char **env, int exit_status, int content_length)
{
	int	index;
	int	count;
	int	word_length;

	index = 0;
	count = 0;
	if (content_length == -1)
		return (-1);
	// printf("content_length : [%d]\n", content_length);
	while (index < content_length)
	{
		// printf("\033[0;32m[\033[0;37m");
		word_length = word_length_expand(content, env, exit_status, &index);
		// printf("\033[0;32m]\033[0;37m	word_length : [%d]\n", word_length);
		if (word_length == -1)
			return (-1);
		if (word_length == 0)
			break ;
		++count;
	}
	return (count);
}

char	**expand_one_content(char *content, char **env, int exit_status)
{
	int	count;
	int	content_length;

	content_length = total_length(content, env, exit_status);
	count = word_count(content, env, exit_status, content_length);
	if (count == -1)
		return (NULL);
	// printf("count : [%d]\n", count);
	return (create_new_array(content, env, exit_status, count));
}

// echo $HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'
// /mnt/nfs/homes/aoberonaoberon$PATH'0'"$PATH"

// echo "toto$HOME"'$USER toto'"'toto'"


// bash-5.1$ '$HOME'$USER
// bash: $HOMEaoberon: command not found

// minishell-0.1$ '$HOME'$USER
// $HOME
// aoberon
// count : [1]
// ------------------------------
// Command ''$HOME'$USER' not found


/*
$HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'
*/
// /mnt/nfs/homes/aoberonaoberon$PATH'0'before after"$PATH
