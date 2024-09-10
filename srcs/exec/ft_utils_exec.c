/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:20:57 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/10 14:22:44 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_exec(t_exe *exec)
{
	exec->cmds = NULL;
	exec->next = NULL;
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
		free(current);
		current = next;
	}
}

void	ft_close_pipes(int *pipefd, int cmds_count)
{
	int	i;

	i = 0;
	while (i < (cmds_count - 1) * 2)
	{
		close(pipefd[i]);
		i++;
	}
}

int	ft_count_cmds(t_a *a)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (a->tab_cmd[j])
	{
		if (a->tab_cmd[j][1][0] == '7')
			count++;
		j++;
	}
	return (count);
}