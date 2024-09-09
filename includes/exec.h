/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:34:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/09 16:47:49 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"

typedef struct s_exe
{
	int				infile;
	int				outfile;
	char			***cmds;
	char			**paths;
	struct s_exe	*next;
}					t_exe;

void				ft_setup_redirection(t_exe *exec, int cmd_index,
						int *pipefd, int count_cmds);
#endif