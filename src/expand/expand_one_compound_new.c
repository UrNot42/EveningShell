/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_compound_new.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:23:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/09 14:05:13 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	copy_var_content(char **new_content, char *var_content, size_t *i)
// {
// 	size_t	n;

// 	n = 0;
// 	while (var_content && var_content[n])
// 	{
// 		(*new_content)[*i] = var_content[n++];
// 		*i += 1;
// 	}
// }

// static	char	*merge_var_content(char *src, t_expand_params params)
// {
// 	char	*new_content;
// 	size_t	i;
// 	size_t	j;
// 	size_t	size;

// 	size = (ft_strlen(src) - params.var_name_length) + ft_strlen(params.var);
// 	new_content = ft_calloc(size + 1, sizeof(char));
// 	if (!new_content)
// 		return (free(src), free(params.var), NULL);
// 	i = 0;
// 	j = 0;
// 	while (i < size)
// 	{
// 		if (i == params.index_dollar)
// 		{
// 			j += params.var_name_length + 1;
// 			if (params.var)
// 				copy_var_content(&new_content, params.var, &i);
// 			else
// 				new_content[i++] = src[j++];
// 		}
// 		else
// 			new_content[i++] = src[j++];
// 		// printf("new_content: %s\n", new_content);
// 	}
// 	return (free(src), free(params.var), new_content);
// }

// // ====================================================================

// static void	debug_expand(char *content, int index)
// {
// 	int	i;

// 	i = 0;
// 	printf("content: ");
// 	while (content[i])
// 	{
// 		if (i == index)
// 		{
// 			if (content[i] == '"' || content[i] == '\'')
// 				printf("\033[0;31m%c\033[0;37m", content[i]);
// 			else if (content[i] == '$')
// 				printf("\033[0;32m%c\033[0;37m", content[i]);
// 			else
// 				printf("\033[0;36m%c\033[0;37m", content[i]);
// 		}
// 		else
// 			printf("%c", content[i]);
// 		++i;
// 	}
// 	printf("\n");
// }

// // ====================================================================

static int	is_special_character(int c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '"'
		|| c == '$' || c == '{' || c == '}' || c == '~' || c == '`'
		|| c == '&' || c == '?' || c == ';' || c == '(' || c == ')'
		|| c == '[' || c == ']' || c == '*' || c == '+' || c == '-'
		|| c == '@' || c == ':' || c == '.' || c == ',' || c == '/')
		return (1);
	return (0);
}

static size_t	get_varname_length(char const *str, int index)
{
	size_t	length;

	length = 0;
	++index;
	if (!ft_isalpha(str[index]) && str[index] != '_'
		&& ft_isdigit(str[index]))
	{
		return (1);
	}
	else if (!ft_isalpha(str[index]) && str[index] != '_'
		&& str[index] != '?' && !ft_isdigit(str[index]))
	{
		return (0);
	}
	else if (str[index] == '?')
	{
		return (1);
	}
	while (str[index] && !is_special_character(str[index]))
	{
		++index;
		++length;
	}
	return (length);
}

// // ====================================================================

// char	*remove_one_couple_single_quotes(char *content, int *index)
// {
// 	char	*new_content;
// 	int		i;
// 	int		j;
// 	int		count_quotes;

// 	new_content = ft_calloc(ft_strlen(content) - 2, sizeof(char));
// 	if (!new_content)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	count_quotes = 0;
// 	while (content[i])
// 	{
// 		if (i == *index && content[i] == '\'')
// 			++count_quotes;
// 		else if (i > *index && count_quotes == 1 && content[i] == '\'')
// 		{
// 			*index = i + 1;
// 			++count_quotes;
// 		}
// 		else
// 			new_content[j++] = content[i];
// 		++i;
// 	}
// 	return (new_content);
// }

// ====================================================================

static	int	retrieve_var_name(char **var, char *str,
	size_t index_dollar, size_t size)
{
	size_t	i;

	i = 0;
	*var = ft_calloc(size + 1, sizeof(char));
	if (!*var)
		return (0);
	++index_dollar;
	while (i < size)
	{
		(*var)[i] = str[index_dollar];
		++index_dollar;
		++i;
	}
	return (1);
}

int	expand_dollar(char **env, char *content, int *index, int exit_status, int *count)
{
	char	*var_name;
	size_t	var_name_length;
	size_t	i;
	size_t	j;
	int		index_env;
	char	flag;

	var_name_length = get_varname_length(content, *index);
	if (!retrieve_var_name(&var_name, content, *index, var_name_length))
		return (-1);
	j = 0;
	while (j++ < var_name_length)
	{
		*index += 1;
	}
	if (!ft_strcmp(var_name, "?"))
	{
		printf("%d", exit_status);
		return (1);
	}
	index_env = get_env_var_index(env, var_name);
	i = 0;
	if (index_env != -1)
	{
		while (env[index_env][i] != '=')
			++i;
		++i;
		flag = '\0';
		while (env[index_env][i])
		{
			printf("%c", env[index_env][i]);
			if ((env[index_env][i] == ' ' || env[index_env][i] == '\t'))
			{
				*count += 1;
				printf("\n");
			}
			if (env[index_env][i] == '\'')
			{
				if (flag == '\0')
				{
					flag = '\'';
				}
				else if (flag == '\'')
				{
					flag = '\0';
					*count += 1;
					printf("\n");
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
					*count += 1;
					printf("\n");
				}
			}
			++i;
		}
	}
	return (1);
}

// ====================================================================

int	expand_one_content(char **content, char **env, int exit_status)
{
	int				index;
	int				count;
	char			flag;
	// t_expand_params	params;

	index = 0;
	count = 0;
	flag = '\0';
	while ((*content)[index])
	{
		// debug_expand(*content, index);
		if (((*content)[index] == ' ' || (*content)[index] == '\t'))
		{
			++count;
			printf("\n");
		}
		else if ((*content)[index] == '\'')
		{
			if (flag == '\0')
			{
				flag = '\'';
			}
			else if (flag == '\'')
			{
				flag = '\0';
				++count;
				printf("\n");
			}
			else if (flag == '"')
			{
				printf("%c", (*content)[index]);
			}
		}
		else if ((*content)[index] == '"')
		{
			if (flag == 0)
			{
				flag = '"';
			}
			else if (flag == '\'')
			{
				printf("%c", (*content)[index]);
			}
			else if (flag == '"')
			{
				flag = '\0';
				++count;
				printf("\n");
			}
		}
		else if ((*content)[index] == '$')
		{
			if (flag == '\'')
			{
				printf("%c", (*content)[index]);
			}
			else if (flag == 0 || flag == '"')
			{
				if (expand_dollar(env, *content, &index, exit_status, &count) == -1)
					return (-1);
			}
		}
		else
			printf("%c", (*content)[index]);
		++index;
	}
	printf("\ncount : [%d]\n", count);
	printf("------------------------------\n");
	return (1);
}

int	expand_one_compound(t_compound compound, char **env, int exit_status)
{
	int	i;

	i = -1;
	while (compound.content[++i])
	{
		if (expand_one_content(&compound.content[i], env, exit_status) == -1)
			return (-1);
	}
	return (1);
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
