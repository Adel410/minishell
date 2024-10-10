/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:00:49 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/10 22:11:37 by ahadj-ar         ###   ########.fr       */
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
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin2(tmp, "/");
		free(tmp);
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
	b->path = NULL;
	b->path = ft_get_path(b->path, env);
	if (b->path == NULL)
	{
		b->cmd_path = NULL;
		return ;
	}
	b->cmd_path = ft_split4(b->path, ':');
	ft_add_slash_to_paths(b->cmd_path);
}

void	ft_print_exec(t_exe *exec, int nb_cmds1)
{
	int	i;

	i = 1;
	while (exec)
	{
		if (exec->cmds)
		{
			printf("cmds: %s\n", exec->cmds[0]);
			while (i <= nb_cmds1)
			{
				printf("option num %d: %s\n", i, exec->cmds[i]);
				i++;
			}
		}
		printf("builtin: %d\n", exec->builtin);
		i = 0;
		if (exec->input_file)
		{
			while (i <= nb_cmds1)
			{
				printf("inputfile numero %d --> %s\n", i, exec->input_file[i]);
				i++;
			}
		}
		i = 0;
		if (exec->output_file)
		{
			while (i <= nb_cmds1)
			{
				printf("outputfile numero %d --> %s\n", i,
					exec->output_file[i]);
				i++;
			}
		}
		printf("append_output: %d\n", exec->append_output);
		printf("here_doc: %d\n", exec->here_doc);
		printf("NEW NODE ------>\n");
		exec = exec->next;
	}
}
