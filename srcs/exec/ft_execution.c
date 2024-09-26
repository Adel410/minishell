/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 19:53:43 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_while_execve(t_b *b, t_exe *current, t_env *built)
{
	int		j;
	char	*cmd_path;
	char	*str;

	j = 0;
	str = ft_strdup(current->cmds[0]);
	while (b->cmd_path[j])
	{
		cmd_path = ft_strjoin2(b->cmd_path[j], current->cmds[0]);
		if (access(cmd_path, X_OK & F_OK) == 0)
			execve(cmd_path, current->cmds, built->env);
		free(cmd_path);
		j++;
	}
	if (str)
		printf("bash: %s: command not found\n", str);
	exit(127);
}

int	ft_execve(t_b *b, t_exe *exec, t_env *built, char **env)
{
	t_exe	*current;
	char	*str;

	current = exec;
	while (current)
	{
		if (current->builtin)
		{
			ft_which_builtin(current, built, env);
			current = current->next;
		}
		else if (access(current->cmds[0], X_OK) == 0)
			execve(current->cmds[0], current->cmds, built->env);
		else
		{
			if (current->cmds && current->cmds[0])
			{
				str = ft_strdup(current->cmds[0]);
				ft_while_execve(b, current, built);
			}
		}
		current = current->next;
	}
	ft_close_pipes(b->pipefd, b->nb_cmds);
	return (0);
}

void	ft_pipe(int *pipefd, int cmds_count)
{
	int	i;

	i = 0;
	while (i < cmds_count)
	{
		if (pipe(pipefd + i * 2) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	ft_fork_and_pipe(t_exe *exec, t_env *built, t_b *b, char **env)
{
	t_exe	*current;

	current = exec;
	b->pipefd = ft_calloc((b->nb_cmds) * 2, sizeof(int));
	if (!b->pipefd)
		return ;
	ft_pipe(b->pipefd, b->nb_cmds);
	b->w = 0;
	while (b->w < b->nb_cmds && current)
	{
		b->pid = fork();
		if (b->pid == -1)
			return (ft_close_pipes(b->pipefd, b->nb_cmds));
		else if (b->pid == 0)
		{
			ft_setup_redirection(current, b->w, b->pipefd, b->nb_cmds);
			ft_execve(b, current, built, env);
		}
		current = current->next;
		b->w++;
	}
	ft_close_pipes(b->pipefd, b->nb_cmds);
	while (waitpid(b->pid, &b->status, 0) > 0)
		built->exit_code = b->status;
	free(b->pipefd);
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
		free(b->cmd_path);
	}
	free(b);
}

int	ft_execute(t_lex *lex, t_env *built, char **env)
{
	t_exe	*exec;
	t_b		*b;

	b = ft_calloc(1, sizeof(t_b));
	exec = ft_calloc(1, sizeof(t_exe));
	if (exec == NULL)
		return (1);
	ft_init_exec(exec);
	ft_cmd_path(b, built->env);
	ft_recast(lex, exec);
	ft_free_lex(lex);
	ft_print_exec(exec);
	b->nb_cmds = ft_count_cmds(exec);
	if (exec->builtin && b->nb_cmds == 1)
		ft_which_builtin(exec, built, env);
	else
		ft_fork_and_pipe(exec, built, b, env);
	ft_free_exec(exec);
	ft_free_b(b);
	return (0);
}
