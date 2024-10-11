/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:20:57 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:21:40 by ahadj-ar         ###   ########.fr       */
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

void	ft_count_elements(t_lex *lex, t_b *b)
{
	t_lex	*current;

	b->nb_cmds1 = 0;
	b->input_count = 0;
	b->output_count = 0;
	b->limiter_count = 0;
	current = lex;
	while (current)
	{
		if (current->type == '8' || current->type == '2'
			|| current->type == '3')
			b->nb_cmds1++;
		else if (current->type == '%')
			b->input_count++;
		else if (current->type == '@')
			b->output_count++;
		else if (current->type == ':')
			b->limiter_count++;
		current = current->next;
	}
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
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (count);
}
