/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:28:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/09 18:22:01 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_pipes_redir(t_b *b)
{
	int	i;

	i = 0;
	while (i < (b->nb_cmds) * 2)
	{
		close(b->pipefd[i]);
		i++;
	}
}

void	ft_input_redirection(t_exe *cmd, t_b *b)
{
	int	fd_infile;

	if (cmd->input_file)
	{
		fd_infile = open(cmd->input_file, O_RDONLY);
		if (fd_infile == -1)
			ft_put_error2(cmd->input_file, 1);
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_infile);
		if (access("here_doc", F_OK) == 1)
			unlink("here_doc");
	}
	else if (b->w > 0)
	{
		if (dup2(b->pipefd[(b->w - 1) * 2], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	ft_output_redirection(t_exe *cmd, t_b *b)
{
	int	flags;
	int	fd_outfile;

	if (cmd->output_file)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append_output)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_outfile = open(cmd->output_file, flags, 0644);
		if (fd_outfile == -1)
			ft_put_error2(cmd->output_file, 1);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_outfile);
	}
	else if (b->w < b->nb_cmds - 1)
	{
		if (dup2(b->pipefd[b->w * 2 + 1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	ft_setup_redirection(t_exe *cmd, t_b *b)
{
	ft_input_redirection(cmd, b);
	ft_output_redirection(cmd, b);
	ft_close_pipes_redir(b);
}
