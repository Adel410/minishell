/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:28:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/09 16:48:04 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setup_redirection(t_exe *exec, int cmd_index, int *pipefd,
		int count_cmds)
{
	int	i;

	i = -1;
	if (cmd_index == 0)
	{
		dup2(exec->infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(exec->outfile);
	}
	else if (cmd_index == count_cmds - 1)
	{
		dup2(pipefd[(cmd_index - 1) * 2], STDIN_FILENO);
		dup2(exec->outfile, STDOUT_FILENO);
		close(exec->infile);
	}
	else
	{
		dup2(pipefd[(cmd_index - 1) * 2], STDIN_FILENO);
		dup2(pipefd[cmd_index * 2 + 1], STDOUT_FILENO);
		close(exec->infile);
		close(exec->outfile);
	}
	while (++i < (count_cmds - 1) * 2)
	{
		if (i != (cmd_index - 1) * 2 && i != cmd_index * 2 + 1)
			close(pipefd[i]);
	}
}
