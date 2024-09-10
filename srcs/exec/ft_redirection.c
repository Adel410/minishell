/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:28:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/10 14:18:29 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setup_redirection(t_exe *cmd, int cmd_index, int *pipefd,
		int cmds_count)
{
	int	fd_infile;
	int	flags;
	int	fd_outfile;
	
	if (cmd->input_file)
	{
		fd_infile = open(cmd->input_file, O_RDONLY);
		if (fd_infile == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_infile);
	}
	else if (cmd_index > 0)
	{
		if (dup2(pipefd[(cmd_index - 1) * 2], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->output_file)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append_output)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_outfile = open(cmd->output_file, flags, 0644);
		if (fd_outfile == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_outfile);
	}
	else if (cmd_index < cmds_count - 1)
	{
		if (dup2(pipefd[cmd_index * 2 + 1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	ft_close_pipes(pipefd, cmds_count);
}
