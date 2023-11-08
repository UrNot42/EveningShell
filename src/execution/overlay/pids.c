/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:59:53 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 11:29:17 by ulevallo         ###   ########.fr       */
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
	status = 0;
	while (pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
