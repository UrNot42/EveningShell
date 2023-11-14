/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/09 19:17:46 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

/**
 * @brief Main that is bound to change as it is mainly used to redirect
 * to change funtions
 *
 */
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		start_interactive(envp);
	else
		return (run_single_cmd(argc - 1, &argv[1], envp)); // TODO
	return (0);
}

// int	main(void)
// {
// 	char	**char2d;

// 	char2d = ft_calloc(4 + 1, sizeof(char *));
// 	if (!char2d)
// 		return (1);
// 	char2d[0] = ft_strdup("1");
// 	char2d[1] = ft_strdup("2");
// 	char2d[2] = ft_strdup("3");
// 	char2d[3] = ft_strdup("4");
// 	ft_free_dstr(char2d);
// 	return (0);
// }
