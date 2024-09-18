/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:11:33 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/18 14:38:13 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PWD
void	ft_pwd(char **env)
{
	pid_t	pid;
	char	*argv[2];

	argv[0] = "/usr/bin/pwd";
	argv[1] = NULL;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		execve("/usr/bin/pwd", argv, env);
		_exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

// ENV
void	ft_env(t_env **built)
{
	t_env	*ptr;

	ptr = *built;
	while (ptr->next)
	{
		printf("%s\n", ptr->env_str);
		ptr = ptr->next;
	}
}

void	ft_unset(t_env **built, char *str)
{
	t_env	*current;
	t_env	*to_remove;
	char	*goal;
	int		i;

	i = 5;
	while (str[i] == ' ')
		i++;
	goal = ft_master_strndup(str, i, ft_strlen(str) - 6);
	if (*built == NULL || goal == NULL)
		return ;
	if (ft_strncmp((*built)->env_str, goal, ft_strlen(goal)) == 0)
	{
		to_remove = *built;
		*built = (*built)->next;
		free(to_remove->env_str);
		free(to_remove);
	}
	else
	{
		current = *built;
		while (current->next != NULL)
		{
			if (ft_strncmp(current->next->env_str, goal, ft_strlen(goal)) == 0)
			{
				to_remove = current->next;
				current->next = to_remove->next;
				(free(to_remove->env_str), free(to_remove));
				break ;
			}
			current = current->next;
		}
	}
	free(goal);
}

void	ft_export(t_env **built, char *str)
{
	t_env	*to_add;
	char	*new;
	int		i;
	int		j;

	to_add = *built;
	i = 6;
	while (str[i] == ' ')
		i++;
	j = i;
	while (str[j] != ' ' && str[j])
		j++;
	new = ft_master_strndup(str, i, j);
	if (!new)
		return ;
	to_add = ft_lstnew(new);
	if (!to_add)
		return ;
	printf("%s\n", to_add->env_str);
	ft_lstadd_back(built, to_add);
	return ;
}

// CD
void	ft_cd(t_exe *current)
{
	char	*path;

	if (current->cmds[1] == NULL)
		path = ft_strdup("/home");
	else
		path = ft_strdup(current->cmds[1]);
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
}

void	ft_which_builtin(t_exe *current, t_env **built, char **env)
{
	(void) built;
	printf("builtin\n");
	if (ft_strcmp(current->cmds[0], "cd") == 0)
		ft_cd(current);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		ft_pwd(env);
	else if (ft_strcmp(current->cmds[0], "echo") == 0)
		ft_echo(current);
	else if (ft_strcmp(current->cmds[0], "exit") == 0)
		exit(0);
	return ;
}
