/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:12:37 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 19:24:35 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

void	ft_free_lex(t_lex *lex)
{
	t_lex	*tmp;

	while (lex)
	{
		tmp = lex->next;
		free(lex->str);
		free(lex);
		lex = tmp;
	}
}

int	ft_init_pipe_and_pid(t_b *b)
{
	b->pipefd = ft_calloc((b->nb_cmds) * 2, sizeof(int));
	if (!b->pipefd)
		return (1);
	b->pid = ft_calloc(b->nb_cmds, sizeof(pid_t));
	if (!b->pid)
	{
		free(b->pipefd);
		return (1);
	}
	return (0);
}

void	ft_close_and_wait(t_b *b, t_env *built)
{
	ft_close_pipes(b->pipefd, b->nb_cmds);
	b->x = 0;
	while (waitpid(-1, &b->status, 0) > 0)
		;
	if (WIFEXITED(b->status))
		built->exit_code = WEXITSTATUS(b->status);
	free(b->pipefd);
	free(b->pid);
}

void	ft_free_b(t_b *b)
{
	int	i;

	i = 0;
	if (b->cmd_path)
	{
		while (b->cmd_path[i])
		{
			free(b->cmd_path[i]);
			i++;
		}
	}
	if (b->cmd_path)
		free(b->cmd_path);
	if (b->path)
		free(b->path);
	if (b)
		free(b);
}
