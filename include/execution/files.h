/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:55:26 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 09:50:15 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "execution.h"

// ========================== FILES_INIT ==========================

int		fill_file(t_token *token, t_file *file, int max_file);
int		open_files(t_file *file);
void	close_files(t_file *file, int to);
int		open_fd(t_cmd *cmd, t_pipe pi);

#endif
