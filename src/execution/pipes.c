/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:01:48 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 09:18:13 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief closes wanted pipes using the pipe structure
 *
 * @param pi the pipe structure
 * @param code Binary code
 *     using the last three bytes to read which pipes to close:
 *      001 -> pipe[0]
 *      010 -> pipe[1]
 *      100 -> pipe_previous
 *     And any combination of those
 * @return val the amount of pipes closed
 */
int	close_pipe(t_pipe *pi, size_t code)
{
	int	val;

	val = 0;
	code = code % 8;
	if ((code == 1 || code == 3 || code == 4 || code == 7) && pi->pe[0] != -1)
	{
		val++;
		close(pi->pe[0]);
	}
	if ((code == 2 || code == 3 || code == 6 || code == 7) && pi->pe[1] != -1)
	{
		val++;
		close(pi->pe[1]);
	}
	if ((code == 4 || code == 6 || code == 7) && pi->pe_prev != -1)
	{
		val++;
		close(pi->pe_prev);
	}
	return (val);
}
