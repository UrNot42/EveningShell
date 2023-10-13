/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:07:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 21:23:26 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "parsing/parsing.h"
# include "execution/execution.h"
# include "../lib/libft/libft.h"

//
// -------------------------- TEMPORARY --------------------------
// -------------------------- DEBUG --------------------------

void	debug_token(t_token *token);
void	debug_double_char(char **argv, char *debug_print);

#endif
