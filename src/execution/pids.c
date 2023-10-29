/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:59:53 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/28 23:01:57 by ulevallo         ###   ########.fr       */
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
	int	i;
	int	status;

	i = 0;
	while (pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (free(pids), WEXITSTATUS(status));
	free(pids);
	return (0);
}
