/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:28:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/06 19:57:33 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_redirections(char **redir)
{
	int	j;

	j = 0;
	if (redir == NULL)
		return ;
	while (redir[j] != NULL)
	{
		free(redir[j]);
		j++;
	}
	free(redir);
}

int	ft_count_redirections(t_a *a)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (a->tab_cmd[i] != NULL)
	{
		if (ft_strncmp(a->tab_cmd[i][1], "5", 1) == 0
			|| ft_strncmp(a->tab_cmd[i][1], "6", 1) == 0)
			count++;
		i++;
	}
	return (count);
}

void	ft_isolate_redirections(t_a *a, t_exe *exec)
{
	int	i;
	int	j;

	exec->redir_count = ft_count_redirections(a);
	exec->redir_types = malloc((exec->redir_count + 1) * sizeof(char *));
	exec->redir_files = malloc((exec->redir_count + 1) * sizeof(char *));
	if (exec->redir_types == NULL || exec->redir_files == NULL)
	{
		free(exec->redir_types);
		free(exec->redir_files);
		return ;
	}
	j = 0;
	i = -1;
	while (a->tab_cmd[++i] != NULL)
	{
		if (ft_strncmp(a->tab_cmd[i][1], "5", 1) == 0 || ft_strncmp(a->tab_cmd[i][1],
				"6", 1) == 0)
		{
			exec->redir_types[j] = ft_strdup(a->tab_cmd[i][1]);
			exec->redir_files[j] = ft_strdup(a->tab_cmd[i+1][0]);
			if (exec->redir_types[j] == NULL || exec->redir_files[j] == NULL)
			{
				ft_free_redirections(exec->redir_files);
				ft_free_redirections(exec->redir_types);
				exec->redir_types = NULL;
				exec->redir_files = NULL;
				return ;
			}
			j++;
		}
	}
	exec->redir_types[j] = NULL;
	exec->redir_files[j] = NULL;
}
