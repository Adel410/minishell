/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:52:25 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/12 17:47:32 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (b->cmd_path)
	{
		while (b->cmd_path[j])
		{
			cmd_path = ft_strjoin2(b->cmd_path[j], cmd);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			j++;
		}
	}
	return (NULL);
}

// void	ft_dup2_first_last(int value, t_b *b, t_env *built)
// {
// 	if (value == 0)
// 	{
// 		if (dup2(built->save_stdin, STDIN_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 		close(b->infile);
// 	}
// 	else if (value == 1)
// 	{
// 		if (dup2(b->pipefd[b->w * 2], built->save_stdout) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// }

int	ft_check_limiter2(t_exe *current)
{
	int	i;

	i = 0;
	while (current->limiter[i])
	{
		if (current->limiter[i] == NULL)
			return (ft_putstr_fd("minishell: empty limiter\n", 2), 1);
		if (current->limiter[i] && current->limiter[i][0] == ' '
			&& current->limiter[i][1] == '\0')
			return (ft_putstr_fd("minishell: empty limiter\n", 2), 1);
		i++;
	}
	return (0);
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

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		ft_putstr("\n");
		i++;
	}
}
