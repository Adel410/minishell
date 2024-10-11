/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:18:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:20:48 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_files(t_exe *exec)
{
	if (exec->output_file)
		ft_free_tab(exec->output_file);
	if (exec->input_file)
	{
		ft_free_tab(exec->input_file);
		if (access("here_doc", F_OK) == 0)
			unlink("here_doc");
	}
}

void	ft_free_cmds(t_exe *exec)
{
	if (exec->cmds)
		ft_free_tab(exec->cmds);
	ft_free_files(exec);
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
			ft_free_tab(current->limiter);
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
