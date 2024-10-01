/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:52:25 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 17:51:30 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_cmds2(t_lex *lex)
{
	t_lex	*current;
	int		count;

	count = 0;
	current = lex;
	while (current)
	{
		if (current->type == '8' || current->type == '2'
			|| current->type == '3')
			count++;
		current = current->next;
	}
	return (count);
}

void	ft_pipe(int *pipefd, int cmds_count)
{
	int	i;

	i = 0;
	while (i < cmds_count)
	{
		if (pipe(pipefd + i * 2) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

char	*ft_join_path(t_b *b, char *cmd)
{
	char	*cmd_path;
	int		j;

	j = 0;
	if (cmd[0] == '\0')
		return (NULL);
	while (b->cmd_path[j])
	{
		cmd_path = ft_strjoin2(b->cmd_path[j], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		j++;
	}
	return (NULL);
}
