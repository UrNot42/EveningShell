/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:28:14 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 14:27:39 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief sets an env for the interactive mode
			and starts the prompt
 *
 * @param env const env that has to be copied
 */
void	start_interactive(char **env)
{
	char	**env_cpy;

	if (!env)
		env_cpy = create_default_env();
	else
		env_cpy = copy_env(env);
	prompt(env_cpy);
}

char	*ft_safe_strjoin(char *to_free_str, char *str_2)
{
	char	*str;

	str = ft_strjoin(to_free_str, str_2);
	free(to_free_str);
	if (!str)
		return (NULL);
	return (str);
}

char	*create_line_from_args(char **argv, int argc)
{
	char	*line;
	size_t	total_length;
	size_t	i;

	total_length = 0;
	i = 0;
	while (argv[i])
		total_length += ft_strlen(argv[i++]);
	line = ft_calloc(total_length + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		line = ft_safe_strjoin(line, argv[i]);
		if (!line)
			return (NULL);
		i++;
	}
	(void)argc;
	return (line);
}

int	run_single_cmd(int arg_count, char **args, char **env)
{
	t_token	*tokens;
	char	*line;

	if (!args)
		return (0);
	line = create_line_from_args(args, arg_count);
	tokens = parse_line(line, env);
	expand(&tokens, env);
	if (tokens)
		return (execute(tokens, env));
	return (0);
}
