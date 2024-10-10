/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:20:57 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/10 22:12:57 by ahadj-ar         ###   ########.fr       */
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

void	ft_free_files(t_exe *exec, int nb_cmds1)
{
	int	i;

	i = 0;
	(void)nb_cmds1;
	if (exec->output_file)
	{
		while (exec->output_file[i])
		{
			free(exec->output_file[i]);
			i++;
		}
		free(exec->output_file);
	}
	i = 0;
	if (exec->input_file)
	{
		while (exec->input_file[i])
		{
			free(exec->input_file[i]);
			i++;
		}
		free(exec->input_file);
		if (access("here_doc", F_OK) == 0)
			unlink("here_doc");
	}
	exec->input_file = NULL;
	exec->output_file = NULL;
}

void	ft_free_cmds(t_exe *exec, int nb_cmds1)
{
	int	i;

	i = 0;
	if (exec->cmds)
	{
		while (exec->cmds[i])
		{
			free(exec->cmds[i]);
			i++;
		}
		free(exec->cmds);
		exec->cmds = NULL;
	}
	ft_free_files(exec, nb_cmds1);
}

void	ft_free_exec(t_exe *exec, int nb_cmds1)
{
	t_exe	*current;
	t_exe	*next;
	int		i;

	current = exec;
	while (current)
	{
		next = current->next;
		ft_free_cmds(current, nb_cmds1);
		i = 0;
		if (current->limiter)
		{
			while (i <= nb_cmds1)
			{
				free(current->limiter[i]);
				i++;
			}
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
	while (i < (cmds_count)*2)
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
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (count);
}
