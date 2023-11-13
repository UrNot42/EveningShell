/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:59:53 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:31 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief uses a malloc'ed pid array and waits for every program
 *
 * @param pids
 * @return last error code
 */
int	wait_pids(int *pids)
{
	int		i;
	int		status;
	bool	quit;

	i = 0;
	status = 0;
	quit = false;
	signal(SIGQUIT, sig_handler_exec);
	signal(SIGINT, sig_handler_exec);
	while (pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && g_signal == 131 && !quit)
		{
			quit = true;
			write(2, "Quit (core dumped)\n", 19);
		}
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
