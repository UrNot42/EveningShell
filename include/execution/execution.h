/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 17:24:57 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include "environment.h"
# include "exec_struct.h"
# include "files.h"
# include "here_doc.h"

// ========================= INIT ========================

int		fill_cmds(t_token *token, t_cmd *cmd, t_file *file);
int		set_execute_struct(t_token *token, t_exec *ex, char **env);
size_t	get_token_type_size(t_token *token, bool is_cmd);

// ========================= EXECUTION ========================

int		execute(t_token *tokens, char **env);
int		wait_pids(int *pids);
void	child_process(t_exec *exec, int i);

int		close_pipe(t_pipe *pi, size_t code);

int		create_cmd(t_cmd *cmd, char **env, char **n_cmd, char ***n_args);
void	free_exec(t_exec *ex, bool env);

// ========================== SIGNAL ==========================

void	sig_handler_exec(int signum);
void	sig_handler_prompt(int signum);
void	sig_handler_heredoc(int signum);

// ========================= DEBUG ============================

void	print_exec_sruct(t_exec *exec); // TODO REMOVE

#endif
