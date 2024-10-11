/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:14:12 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:14:50 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_flags(t_exe *cmd, int *flags)
{
	*flags = O_WRONLY | O_CREAT;
	if (cmd->append_output)
		*flags |= O_APPEND;
	else
		*flags |= O_TRUNC;
}

void	ft_handle_single_output(t_exe *cmd, int i)
{
	int	flags;
	int	fd_outfile;

	ft_set_flags(cmd, &flags);
	fd_outfile = open(cmd->output_file[i], flags, 0644);
	if (fd_outfile == -1)
		ft_put_error2(cmd->output_file[i], 1);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_outfile);
}

void	ft_handle_pipe_output(t_b *b)
{
	if (b->w < b->nb_cmds - 1)
	{
		if (dup2(b->pipefd[b->w * 2 + 1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	ft_output_redirection(t_exe *cmd, t_b *b)
{
	b->i = 0;
	if (cmd->output_file)
	{
		while (cmd->output_file[b->i])
		{
			ft_handle_single_output(cmd, b->i);
			b->i++;
		}
	}
	else
		ft_handle_pipe_output(b);
}
