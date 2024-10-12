/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:04 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/12 16:32:46 by ahadj-ar         ###   ########.fr       */
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
		fd_outfile = open(current->output_file[0], flags, 0644);
		if (fd_outfile == -1)
			ft_put_error2(current->output_file[0], 1);
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
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		}
		return (2);
	}
	else if (current->limiter)
	{
		return (ft_check_limiter2(current));
	}
	return (0);
}

int	ft_check_list(t_exe *exec, t_env *built, t_b *b)
{
	t_exe	*current;

	b->hd_count = 0;
	current = exec;
	while (current)
	{
		if (ft_check_limiter(current) != 0)
			return (ft_unlink_here_doc(b->hd_count), 1);
		if (current->here_doc && current->limiter)
			ft_call_here_doc(current, built, b);
		ft_check_node(current);
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (0);
}

int	ft_check_for_options(t_lex *next, t_exe *new)
{
	int	i;

	i = 1;
	if (next->str && next->str[0] == '\0')
		return (0);
	else if (next->str && next->str[0] == ' ' && next->str[0] == '\0')
		return (0);
	while (new->cmds[i] != NULL)
		i++;
	if (next->str)
		new->cmds[i] = ft_strdup(next->str);
	return (0);
}
