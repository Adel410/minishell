/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/18 16:19:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve(t_b *b, t_exe *exec, t_env **built, char **env)
{
	t_exe	*current;
	char	*cmd_path;
	int		j;

	current = exec;
	while (current)
	{
		if (current->builtin)
		{
			ft_which_builtin(current, built, env);
			current = current->next;
		}
		if (current->cmds && current->cmds[0])
		{
			j = 0;
			while (b->cmd_path[j])
			{
				cmd_path = ft_strjoin2(b->cmd_path[j], current->cmds[0]);
				if (access(cmd_path, X_OK) == 0)
					execve(cmd_path, current->cmds, env);
				free(cmd_path);
				j++;
			}
			printf("bash: %s: command not found\n", current->cmds[0]);
			return ;
		}
		current = current->next;
	}
}

void	ft_pipe(int *pipefd, int cmds_count)
{
	int	i;

	i = -1;
	while (++i < cmds_count - 1)
	{
		if (pipe(pipefd + i * 2) == -1)
			exit(EXIT_FAILURE);
	}
}

void	ft_fork_and_pipe(t_exe *exec, t_env **built, t_b *b, char **env)
{
	t_exe	*current;
	int		*pipefd;

	current = exec;
	pipefd = ft_calloc((b->nb_cmds - 1) * 2, sizeof(int));
	if (!pipefd)
		return ;
	ft_pipe(pipefd, b->nb_cmds);
	b->w = -1;
	while (++b->w < b->nb_cmds && current)
	{
		b->pid = fork();
		if (b->pid == -1)
			return (ft_close_pipes(pipefd, b->nb_cmds));
		else if (b->pid == 0)
		{
			ft_setup_redirection(current, b->w, pipefd, b->nb_cmds);
			ft_execve(b, current, built, env);
		}
		current = current->next;
	}
	ft_close_pipes(pipefd, b->nb_cmds);
	while (wait(NULL) > 0)
		;
	free(pipefd);
}

int	ft_execute(t_lex *lex, t_env **built, char **env)
{
	t_exe	*exec;
	t_b		*b;

	(void)built;
	b = ft_calloc(1, sizeof(t_b));
	exec = ft_calloc(1, sizeof(t_exe));
	if (exec == NULL)
		return (1);
	ft_init_exec(exec);
	b->nb_cmds = ft_count_cmds(lex);
	ft_cmd_path(b, env);
	if (b->nb_cmds == 0 && lex->next->next == NULL)
		return (ft_check_type(lex), 0);
	ft_recast(lex, exec);
	ft_print_exec(exec);
	if (exec->builtin && b->nb_cmds == 1)
		return (ft_which_builtin(exec, built, env), 0);
	// ft_print_exec(exec);
	// if (a->debug)
	// 	ft_debug_lst(exec);
	ft_fork_and_pipe(exec, built, b, env);
	return (0);
}
