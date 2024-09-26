/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:00:49 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 19:36:19 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_new(t_exe *new)
{
	new->next = ft_calloc(1, sizeof(t_exe));
	if (new->next == NULL)
		return ;
	new->next->next = NULL;
}

void	ft_add_slash_to_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], "/");
		i++;
	}
	paths[i] = NULL;
}

char	*ft_get_path(char *path, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	return (path);
}

void	ft_cmd_path(t_b *b, char **env)
{
	b->path = ft_get_path(b->path, env);
	b->cmd_path = ft_split4(b->path, ':');
	free(b->path);
	ft_add_slash_to_paths(b->cmd_path);
}

void	ft_print_exec(t_exe *exec)
{
	int	i;

	i = 1;
	while (exec)
	{
		if (exec->cmds)
		{
			printf("cmds: %s\n", exec->cmds[0]);
			while (exec->cmds[i])
			{
				printf("option num %d: %s\n", i, exec->cmds[i]);
				i++;
			}
		}
		printf("builtin: %d\n", exec->builtin);
		printf("input_file: %s\n", exec->input_file);
		printf("output_file: %s\n", exec->output_file);
		printf("append_output: %d\n", exec->append_output);
		printf("here_doc: %d\n", exec->here_doc);
		printf("string: %s\n", exec->string);
		printf("limiter: %s\n", exec->limiter);
		printf("NEW NODE ------>\n");
		exec = exec->next;
	}
}
