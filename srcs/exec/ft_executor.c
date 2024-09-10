/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/10 17:01:52 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_isolate_cmds(t_a *a, t_exe *exec)
{
	int		i;
	t_exe	*current;

	current = exec;
	i = 0;
	while (a->tab_cmd[i] != NULL)
	{
		if (a->tab_cmd[i][1][0] == '7')
		{
			current->cmds = ft_calloc(3, sizeof(char *));
			if (!current->cmds)
				return ;
			current->cmds[0] = ft_strdup(a->tab_cmd[i][0]);
			while (a->tab_cmd[i + 1] && a->tab_cmd[i + 1][1][0] != '7'
				&& a->tab_cmd[i + 1][1][0] != '4')
			{
				i++;
				if (ft_strncmp(a->tab_cmd[i][0], "<", 1) == 0)
					current->input_file = ft_strdup(a->tab_cmd[++i][0]);
				else if (ft_strncmp(a->tab_cmd[i][0], ">", 1) == 0)
				{
					current->output_file = ft_strdup(a->tab_cmd[++i][0]);
					current->append_output = 0;
				}
				else if (ft_strncmp(a->tab_cmd[i][0], ">>", 2) == 0)
				{
					current->output_file = ft_strdup(a->tab_cmd[++i][0]);
					current->append_output = 1;
				}
				else
					current->cmds[1] = ft_strdup(a->tab_cmd[i][0]);
			}
			current->cmds[2] = NULL;
			if (current->next == NULL && a->tab_cmd[i + 1] != NULL)
			{
				current->next = ft_calloc(1, sizeof(t_exe));
				if (!current->next)
					return ;
			}
			current = current->next;
		}
		i++;
	}
}

void	ft_execve(t_a *a, t_exe *exec, char **env)
{
	t_exe	*current;
	char	*cmd_path;
	int		j;

	current = exec;
	while (current)
	{
		if (current->cmds && current->cmds[0])
		{
			j = 0;
			while (a->cmd_path[j])
			{
				cmd_path = ft_strjoin2(a->cmd_path[j], current->cmds[0]);
				if (access(cmd_path, X_OK) == 0)
				{
					execve(cmd_path, current->cmds, env);
				}
				free(cmd_path);
				j++;
			}
			printf("Command not found: %s\n", current->cmds[0]);
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

void	ft_fork_and_pipe(t_a *a, t_exe *exec, char **env)
{
	t_exe	*current;
	int		*pipefd;
	(void)env;

	current = exec;
	pipefd = ft_calloc((a->b->nb_cmds - 1) * 2, sizeof(int));
	if (!pipefd)
		return ;
	ft_pipe(pipefd, a->b->nb_cmds);
	a->b->i = -1;
	while (++a->b->i < a->b->nb_cmds && current)
	{
		a->b->pid = fork();
		if (a->b->pid == -1)
			return (ft_close_pipes(pipefd, a->b->nb_cmds));
		else if (a->b->pid == 0)
		{
			ft_setup_redirection(current, a->b->i, pipefd, a->b->nb_cmds);
			ft_execve(a, current, env);
		}
		current = current->next;
	}
	ft_close_pipes(pipefd, a->b->nb_cmds);
	while (wait(NULL) > 0)
		;
	free(pipefd);
}

void	ft_execute(t_a *a, char **env)
{
	t_exe	*exec;

	exec = ft_calloc(1, sizeof(t_exe));
	if (exec == NULL)
		return ;
	a->b->nb_cmds = ft_count_cmds(a);
	ft_init_exec(exec);
	ft_isolate_cmds(a, exec);
	ft_fork_and_pipe(a, exec, env);
	ft_free_cmds(exec);
	ft_free_exec(exec);
	return ;
}
