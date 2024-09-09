/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/09 17:10:39 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_open_fds(t_exe *exec)
{
	exec->infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->infile < 0)
		exit(EXIT_FAILURE);
	exec->outfile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->outfile < 0)
		exit(EXIT_FAILURE);
}

void	ft_close_fds(t_exe *exec)
{
	close(exec->infile);
	close(exec->outfile);
}

void	ft_close_pipes(int *pipefd, int cmds_count)
{
	int	i;

	i = 0;
	while (i < (cmds_count - 1) * 2)
	{
		close(pipefd[i]);
		i++;
	}
}

void	ft_free_cmds(t_exe *exec)
{
	int	i;
	int	j;

	if (!exec->cmds)
		return ;
	i = 0;
	while (exec->cmds[i])
	{
		j = 0;
		while (exec->cmds[i][j])
		{
			free(exec->cmds[i][j]);
			j++;
		}
		free(exec->cmds[i]);
		i++;
	}
	free(exec->cmds);
	exec->cmds = NULL;
}

int	ft_count_cmds(t_a *a)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (a->tab_cmd[j])
	{
		if (a->tab_cmd[j][1][0] == '7')
			count++;
		j++;
	}
	return (count);
}

void	ft_isolate_cmds(t_a *a, t_exe *exec)
{
	int	i;
	int	j;
	int	k;
	int	cmds_count;

	cmds_count = ft_count_cmds(a);
	exec->cmds = ft_calloc(cmds_count + 1, sizeof(char **));
	if (!exec->cmds)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (a->tab_cmd[i])
	{
		if (a->tab_cmd[i][1][0] == '7')
		{
			exec->cmds[j] = ft_calloc(10, sizeof(char *));
			if (!exec->cmds[j])
				exit(EXIT_FAILURE);
			k = 0;
			exec->cmds[j][k] = ft_strdup(a->tab_cmd[i][0]);
			i++;
			while (a->tab_cmd[i] && a->tab_cmd[i][0][0] == ' ')
				i++;
			if (a->tab_cmd[i] && a->tab_cmd[i][0][0] == '-')
			{
				exec->cmds[j][k + 1] = ft_strdup(a->tab_cmd[i][0]);
				i++;
			}
			j++;
		}
		else
			i++;
	}
	exec->cmds[j] = NULL;
}

void	ft_execve(t_a *a, t_exe *exec, char **env, int i)
{
	int		j;
	char	*cmd_path;

	j = 0;
	while (a->cmd_path[j])
	{
		cmd_path = ft_strjoin2(a->cmd_path[j], exec->cmds[i][0]);
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, exec->cmds[i], env);
			perror("execve");
		}
		free(cmd_path);
		j++;
	}
	printf("Command not found: %s\n", exec->cmds[i][0]);
	exit(EXIT_FAILURE);
}

void	ft_fork_and_pipe(t_a *a, t_exe *exec, char **env)
{
	t_exe	*ptr;
	int		*pipefd;
	int		i;
	int		cmds_count;
	int		pid;

	ptr = exec;
	cmds_count = ft_count_cmds(a);
	i = -1;
	pipefd = ft_calloc((cmds_count - 1) * 2, sizeof(int));
	if (!pipefd)
		exit(EXIT_FAILURE);
	while (++i < cmds_count - 1)
	{
		if (pipe(pipefd + i * 2) == -1)
			exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < cmds_count)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			// ft_setup_redirection(exec, i, pipefd, cmds_count);
			ft_execve(a, exec, env, i);
			exit(EXIT_FAILURE);
		}
	}
	ft_close_pipes(pipefd, cmds_count);
	ft_close_fds(exec);
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
	ft_open_fds(exec);
	ft_isolate_cmds(a, exec);
	ft_fork_and_pipe(a, exec, env);
	ft_free_cmds(exec);
	free(exec);
	return ;
}
