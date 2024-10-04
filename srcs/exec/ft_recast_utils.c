/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:04 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 18:26:34 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_open_output(t_exe *current)
{
	int	flags;
	int	fd_outfile;

	if (current->output_file)
	{
		flags = O_WRONLY | O_CREAT;
		if (current->append_output)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_outfile = open(current->output_file, flags, 0644);
		if (fd_outfile == -1)
			ft_put_error2(current->output_file, 1);
		close(fd_outfile);
	}
}

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
		else if (!current->cmds && !current->string)
			ft_open_output(current);
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
