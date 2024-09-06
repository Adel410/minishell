/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:11:33 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/06 16:44:23 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PWD
void	ft_pwd(char *str, char **env)
{
	pid_t	pid;
	char	*argv[] = {"/usr/bin/pwd", NULL};

	(void)str;
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
				free(to_remove->env_str);
				free(to_remove);
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
	int	i;
	int	j;

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

// ECHO
void	ft_echo(char *str)
{
	int	i;

	i = 4;
	if (ft_strncmp(str, "echo -n", 7) == 0)
	{
		i = 8;
		while (str[i])
		{
			printf("%c", str[i]);
			i++;
		}
		return ;
	}
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
	return ;
}

// CD
void	ft_cd(char *str)
{
	int		i;
	int		j;
	char	*path;

	i = 2;
	j = 0;
	while (str[i] == ' ' && str[i])
		i++;
	j = i;
	while (str[j])
		j++;
	path = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while (str[i] != ' ' && str[i])
	{
		path[j] = str[i];
		i++;
		j++;
	}
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s", path);
}

// Chercher si str est un built-in executer sinon on return
void	ft_which_builtin(t_env **built, t_a *a, char *str, char **env)
{
	if (ft_strncmp(str, "pwd", 3) == 0 && *(str + 3) == '\0')
		ft_pwd(str, env);
	else if (ft_strncmp(str, "env", 3) == 0 && *(str + 3) == '\0')
		ft_env(built);
	else if (ft_strncmp(str, "unset", 5) == 0)
		ft_unset(built, str);
	else if (ft_strncmp(str, "export", 6) == 0)
		ft_export(built, str);
	else if (ft_strncmp(str, "echo", 4) == 0)
		ft_echo(str);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str);
	else if (ft_strncmp(str, "..", 2) == 0 && *(str + 2) == '\0')
		chdir("..");
	else if (ft_strncmp(str, "exit", 4) == 0 && *(str + 4) == '\0')
		ft_cleanup(a);
	else
		return ;
}
