/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:33:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/06 19:49:08 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_pipe(t_a *a, int *pipefd, int count_cmds)
{
	int	i;

	(void)a;
	i = 0;
	while (i < (count_cmds - 1) * 2)
	{
		close(pipefd[i]);
		i++;
	}
	free(pipefd);
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

void	ft_free_exec_cmds(t_exe *exec)
{
	int	i;
	int	j;

	i = 0;
	if (exec == NULL || exec->cmds == NULL)
		return ;
	while (i < exec->cmd_count)
	{
		if (exec->cmds[i] != NULL)
		{
			j = 0;
			while (exec->cmds[i][j] != NULL)
			{
				free(exec->cmds[i][j]);
				j++;
			}
			free(exec->cmds[i]);
		}
		i++;
	}
	free(exec->cmds);
	exec->cmds = NULL;
	exec->cmd_count = 0;
}

void	ft_isolate_commands(t_a *a, t_exe *exec)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (a->tab_cmd[i] != NULL)
	{
		if (strcmp(a->tab_cmd[i][1], "7") == 0)
			j++;
		i++;
	}
	exec->cmds = malloc((j + 1) * sizeof(char **));
	if (exec->cmds == NULL)
		return ;
	j = 0;
	i = -1;
	while (a->tab_cmd[++i] != NULL)
	{
		if (strcmp(a->tab_cmd[i][1], "7") == 0)
		{
			exec->cmds[j] = malloc(2 * sizeof(char *));
			if (exec->cmds[j] == NULL)
				return ;
			exec->cmds[j][0] = strdup(a->tab_cmd[i][0]);
			exec->cmds[j][1] = NULL;
			j++;
		}
	}
	exec->cmds[j] = NULL;
}

void	ft_execute_redirections(t_exe *exec)
{
	int	i;

	i = 0;
	while (i < exec->redir_count)
	{
		if (ft_strncmp(exec->redir_types[i], "5", 1) == 0)
		{
			exec->infile = open(exec->redir_files[i], O_RDONLY);
			if (exec->infile < 0)
			{
				perror("open infile");
				exit(EXIT_FAILURE);
			}
			dup2(exec->infile, STDIN_FILENO);
			close(exec->infile);
		}
		else if (ft_strncmp(exec->redir_types[i], "6", 1) == 0)
		{
			exec->outfile = open(exec->redir_files[i],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec->outfile < 0)
			{
				perror("open outfile");
				exit(EXIT_FAILURE);
			}
			dup2(exec->outfile, STDOUT_FILENO);
			close(exec->outfile);
		}
		i++;
	}
}

void	ft_execute(t_a *a, char **env)
{
	t_exe	*exec;
	int		cmds_count;
	char	*cmd_path;
	int		i;
	pid_t	pid;
	int		j;

	exec = ft_calloc(1, sizeof(t_exe));
	if (exec == NULL)
		return ;
	cmds_count = ft_count_cmds(a);
	exec->cmd_count = cmds_count;
	if (exec->cmds != NULL)
		ft_free_exec_cmds(exec);
	ft_isolate_commands(a, exec);
	ft_isolate_redirections(a, exec);
	i = -1;
	while (++i < cmds_count)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_execute_redirections(exec);
			j = 0;
			while (a->cmd_path[j])
			{
				cmd_path = ft_strjoin2(a->cmd_path[j], exec->cmds[i][0]);
				if (access(cmd_path, X_OK) == 0)
				{
					execve(cmd_path, exec->cmds[i], env);
					exit(EXIT_FAILURE);
				}
				free(cmd_path);
				j++;
			}
			printf("Command not found: %s\n", exec->cmds[i][0]);
			exit(EXIT_FAILURE);
		}
		else
			wait(&pid);
	}
	ft_free_redirections(exec->redir_files);
	ft_free_redirections(exec->redir_types);
	ft_free_exec_cmds(exec);
	free(exec);
	return ;
}
