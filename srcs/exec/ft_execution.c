/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/09 13:59:30 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_trouble_execute(char *str, t_exe *current, t_env *built, t_b *b)
{
	char	*cmd_path;

	if ((str[0] == '.' || str[0] == '/') && chdir(str) == 0)
	{
		chdir("..");
		ft_put_error(current->cmds[0], 126);
	}
	else if (access(str, X_OK) == 0)
		execve(str, current->cmds, built->env);
	cmd_path = ft_join_path(b, current->cmds[0]);
	if (cmd_path != NULL)
	{
		if (access(cmd_path, X_OK) == 0)
			execve(cmd_path, current->cmds, built->env);
	}
	else if (access(str, X_OK) != 0 || access(str, W_OK) != 0
		|| opendir(str) == NULL)
		ft_put_error2(current->cmds[0], 1);
	else if (cmd_path == NULL)
		ft_put_error(current->cmds[0], 127);
}

void	ft_while_execve(t_b *b, t_exe *current, t_env *built)
{
	int		j;
	char	*cmd_path;

	j = 0;
	if (b->cmd_path == NULL)
		ft_put_error(current->cmds[0], 1);
	while (b->cmd_path[j])
	{
		cmd_path = ft_strjoin2(b->cmd_path[j], current->cmds[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd_path);
			ft_trouble_execute(current->cmds[0], current, built, b);
			ft_put_error(current->cmds[0], 126);
		}
		free(cmd_path);
		j++;
	}
	if (current->next == NULL)
		ft_put_error(current->cmds[0], 127);
	else
		ft_put_error2(current->cmds[0], 128);
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
			exit(0);
			current = current->next;
		}
		else if (access(current->cmds[0], F_OK) == 0)
			ft_trouble_execute(current->cmds[0], current, built, b);
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
			if (b->w == 0 && !exec->input_file)
				ft_dup2_first_last(0, b, built);
			else if (b->w == b->nb_cmds - 1 && !exec->output_file)
				ft_dup2_first_last(1, b, built);
			ft_setup_redirection(current, b);
			(close(built->save_stdin), close(built->save_stdout));
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
	b->w = 0;
	exec = ft_calloc(1, sizeof(t_exe));
	if (exec == NULL)
		return (1);
	ft_init_exec(exec);
	b->nb_cmds1 = ft_count_cmds2(lex);
	ft_cmd_path(b, built->env);
	if (ft_recast(lex, exec, built, b) == 1)
		return (1);
	b->nb_cmds = ft_count_cmds(exec);
	ft_free_lex(lex);
	if (exec->builtin && b->nb_cmds == 1)
		ft_which_builtin(exec, built, b);
	else
		ft_fork_and_pipe(exec, built, b);
	ft_unlink_here_doc(b->hd_count);
	ft_free_exec(exec);
	ft_free_b(b);
	return (0);
}
