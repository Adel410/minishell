/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:52:25 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/09 19:18:40 by ahadj-ar         ###   ########.fr       */
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

void	ft_dup2_first_last(int value, t_b *b, t_env *built)
{
	if (value == 0)
	{
		if (dup2(b->infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(b->infile);
	}
	else if (value == 1)
	{
		if (dup2(b->pipefd[b->w * 2], built->save_stdout) == -1)
			exit(EXIT_FAILURE);
	}
}

void	ft_unlink_here_doc(int here_doc_count)
{
	int		i;
	char	*file_name;

	i = 0;
	while (i < here_doc_count)
	{
		file_name = ft_create_filename(i);
		unlink(file_name);
		free(file_name);
		i++;
	}
}
