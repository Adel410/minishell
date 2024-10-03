/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:20:57 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 19:24:15 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_exec(t_exe *exec)
{
	exec->cmds = NULL;
	exec->next = NULL;
	exec->input_file = NULL;
	exec->output_file = NULL;
	exec->append_output = 0;
	exec->here_doc = 0;
	exec->builtin = 0;
	exec->limiter = NULL;
	exec->cmd_path = NULL;
}

void	ft_free_cmds(t_exe *exec)
{
	int	i;

	if (exec->cmds)
	{
		i = 0;
		while (exec->cmds[i])
		{
			free(exec->cmds[i]);
			i++;
		}
		free(exec->cmds);
		exec->cmds = NULL;
	}
	if (exec->input_file)
	{
		free(exec->input_file);
		exec->input_file = NULL;
	}
	if (exec->output_file)
	{
		free(exec->output_file);
		exec->output_file = NULL;
	}
}

void	ft_free_exec(t_exe *exec)
{
	t_exe	*current;
	t_exe	*next;

	current = exec;
	while (current)
	{
		next = current->next;
		ft_free_cmds(current);
		if (current->limiter)
		{
			free(current->limiter);
			current->limiter = NULL;
		}
		if (current->string)
		{
			free(current->string);
			current->string = NULL;
		}
		free(current);
		current = next;
	}
	free(current);
}

void	ft_close_pipes(int *pipefd, int cmds_count)
{
	int	i;

	i = 0;
	while (i < (cmds_count) * 2)
	{
		close(pipefd[i]);
		i++;
	}
}

int	ft_count_cmds(t_exe *exec)
{
	t_exe	*current;
	int		count;

	count = 0;
	current = exec;
	while (current)
	{
		if (current->cmds && current->cmds[0])
			count++;
		current = current->next;
	}
	return (count);
}
