/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 17:55:54 by ulevallo         ###   ########.fr       */
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

# define

// ========================== PROMPT ==========================

void	prompt(char **envp);
t_token	*parse_line(char *line, char **envp);

// ========================= INIT ========================

int		fill_cmds(t_token *token, t_cmd *cmd, t_file *file);
int		set_execute_struct(t_token *token, t_exec *ex, char **env);
size_t	get_token_type_size(t_token *token, bool is_cmd);

// ========================= EXECUTION ========================

int		execute(t_token *tokens, char **env);
int		wait_pids(int *pids);
void	child_process(t_exec *exec, int i);

int		close_pipe(t_pipe *pi, size_t code);

int		create_cmd(t_cmd *cmd, char **env);

// ========================= DEBUG ============================

void	print_exec_sruct(t_exec *exec); // TODO REMOVE

#endif
