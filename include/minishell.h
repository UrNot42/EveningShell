/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:07:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 15:29:46 by ulevallo         ###   ########.fr       */
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
# include <signal.h>

# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "get_next_line.h"
# include "execution/execution.h"
# include "../lib/libft/libft.h"

extern int	g_signal;

// ========================== PROMPT ==========================

void		prompt(char ***env);
void		prompt_non_interactive(char ***env);
t_compound	*parse_line(char *line, char **envp, int exit_status);

// ------------------------- ERROR_DISPLAY -----------------------

void		error_dup_failed(char *s); // TODO
void		error_malloc_failed(bool _exit);
void		command_not_found(char *cmd, bool spe);

// ------------------------- RUNNING_SHELL -----------------------

void		start_interactive(char **env);
void		start_non_interactive(char **env);
int			run_single_cmd(int argc, char **argv, char **envp);

// ---------------------------- DEBUG ----------------------------

void		debug_heredoc(int fd);
void		debug_expand(char *content, int index);
void		debug_compound(t_compound *compound, char *debug_print);
void		debug_double_char(char **argv, char *debug_print, int print_name);

#endif
