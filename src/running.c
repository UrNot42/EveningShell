/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:28:14 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/19 19:53:22 by ulevallo         ###   ########.fr       */
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

	if (!env || !*env)
		env_cpy = create_default_env();
	else
		env_cpy = copy_env(env);
	prompt(&env_cpy);
}

// frees the 1st var
char	*ft_safe_strjoin(char *to_free_str, char *str_2)
{
	char	*str;

	str = ft_strjoin(to_free_str, str_2);
	free(to_free_str);
	if (!str)
		return (NULL);
	return (str);
}

// frees the 2nd var
char	*ft_safe_strjoin_2(char *str_1, char *to_free_str)
{
	char	*str;

	str = ft_strjoin(str_1, to_free_str);
	free(to_free_str);
	if (!str)
		return (NULL);
	return (str);
}

/**
 * @brief sets an env for the interactive mode
			and starts the prompt
 *
 * @param env const env that has to be copied
 */
void	start_non_interactive(char **env)
{
	char	**env_cpy;

	if (!env || !*env)
		env_cpy = create_default_env();
	else
		env_cpy = copy_env(env);
	prompt_non_interactive(&env_cpy);
}
