/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:04 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 15:36:41 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_node(t_exe *current)
{
	if (!current->cmds)
	{
		if (current->string)
		{
			current->cmds = ft_calloc(2, sizeof(char *));
			current->cmds[0] = ft_strdup(current->string);
			current->cmds[1] = NULL;
			free(current->string);
			current->string = NULL;
		}
	}
}

int	ft_check_limiter(t_exe *current)
{
	if (current->here_doc == 1 && !current->limiter)
	{
		if (current->next != NULL)
			ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		else
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
				2);
		return (2);
	}
	return (0);
}

void	ft_check_list(t_exe *exec)
{
	t_exe	*current;

	current = exec;
	while (current)
	{
		ft_check_node(current);
		ft_check_limiter(current);
		current = current->next;
	}
}

int	ft_check_if_already(t_exe *current, char *str)
{
	if (current->input_file && ft_strcmp(current->input_file, str) == 0)
		return (1);
	else if (current->output_file && ft_strcmp(current->output_file, str) == 0)
		return (2);
	else if (current->cmds && current->cmds[0] && ft_strcmp(current->cmds[0],
			str) == 0)
		return (3);
	else if (current->cmds && current->cmds[1] && ft_strcmp(current->cmds[1],
			str) == 0)
		return (4);
	else if (current->limiter && ft_strcmp(current->limiter, str) == 0)
		return (5);
	else
		return (0);
}
