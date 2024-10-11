/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 17:05:58 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_while_execve(t_b *b, t_exe *current, t_env *built)
{
	char	*cmd_path;

	if (current->cmds[0][0] == '\0')
		exit(0);
	if ((current->cmds[0][0] == '.' || current->cmds[0][0] == '/')
		|| chdir(current->cmds[0]) == 0)
		ft_put_error(current->cmds[0], 126);
	cmd_path = ft_join_path(b, current->cmds[0]);
	if (cmd_path != NULL)
	{
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, current->cmds, built->env) == -1)
				perror("minishell: execve");
		}
	}
	else if (cmd_path == NULL || access(current->cmds[0], X_OK) != 0
		|| access(current->cmds[0], W_OK) != 0)
		ft_put_error(current->cmds[0], 127);
}

int	ft_execve(t_b *b, t_exe *exec, t_env *built)
{
	t_exe	*current;

	current = exec;
	while (current)
	{
		if (current->builtin)
		{
			ft_which_builtin(current, built, b);
			exit(built->exit_code);
			current = current->next;
		}
		else if (access(current->cmds[0], X_OK) == 0
			&& chdir(current->cmds[0]) == -1)
			execve(current->cmds[0], current->cmds, built->env);
		else
		{
			if (current->cmds && current->cmds[0])
				ft_while_execve(b, current, built);
		}
		if (current && current->next)
			current = current->next;
	}
	ft_close_pipes(b->pipefd, b->nb_cmds);
	return (0);
}

void	ft_fork_and_pipe(t_exe *exec, t_env *built, t_b *b)
{
	t_exe	*current;

	current = exec;
	if (ft_init_pipe_and_pid(b) == 1)
		return ;
	ft_pipe(b->pipefd, b->nb_cmds);
	while (b->w < b->nb_cmds && current)
	{
		b->pid[b->w] = fork();
		if (b->pid[b->w] == -1)
			return (ft_close_pipes(b->pipefd, b->nb_cmds));
		else if (b->pid[b->w] == 0)
		{
			(close(built->save_stdin), close(built->save_stdout));
			ft_setup_redirection(current, b);
			ft_execve(b, current, built);
		}
		current = current->next;
		b->w++;
	}
	ft_close_and_wait(b, built);
}

int	ft_execute(t_lex *lex, t_env *built)
{
	t_exe	*exec;
	t_b		*b;

	b = ft_calloc(1, sizeof(t_b));
	if (!b)
		return (ft_free_lex(lex), 1);
	exec = ft_calloc(1, sizeof(t_exe));
	if (!exec)
		return (ft_free_lex(lex), 1);
	ft_init_exec(exec);
	ft_count_elements(lex, b);
	ft_cmd_path(b, built->env);
	if (ft_recast(lex, exec, built, b) == 1)
		return (ft_free_lex(lex), 1);
	ft_free_lex(lex);
	b->nb_cmds = ft_count_cmds(exec);
	if (exec->builtin && b->nb_cmds == 1)
		ft_which_builtin(exec, built, b);
	else
		ft_fork_and_pipe(exec, built, b);
	ft_unlink_here_doc(b->hd_count);
	(close(built->save_stdin), close(built->save_stdout));
	ft_free_exec(exec);
	ft_free_b(b);
	return (0);
}
