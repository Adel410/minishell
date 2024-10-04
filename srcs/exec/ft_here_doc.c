/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:34:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 19:52:50 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_here_doc(t_exe *exec, t_env *built)
{
	t_exe	*current;

	current = exec;
	while (current)
	{
		if (current->here_doc == 1)
		{
			if (ft_here_doc(current, built) == 0)
			{
				free(current->input_file);
				current->input_file = ft_strdup("here_doc");
			}
		}
		current = current->next;
	}
}

void	ft_here_doc_prompt(char *line, char *limiter, t_env *built, int fd)
{
	char	*tmp;

	while (1)
	{
		ft_putstr("heredoc > ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (ft_dollar_in_string(line) == 1)
		{
			tmp = ft_strdup(line);
			free(line);
			line = ft_expand_dollar(tmp, built);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	ft_here_doc(t_exe *exec, t_env *built)
{
	char	*line;
	char	*limiter;
	int		fd;
	t_exe	*current;

	current = exec;
	fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = NULL;
	if (current->limiter)
		limiter = ft_strdup(current->limiter);
	else
		return (1);
	ft_here_doc_prompt(line, limiter, built, fd);
	free(limiter);
	close(fd);
	return (0);
}
