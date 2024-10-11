/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:34:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 17:22:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_here_doc_prompt(char *line, char *limiter, t_env *built, int fd)
{
	char	*tmp;

	while (1)
	{
		ft_putstr("heredoc > ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		while (ft_dollar_in_string(line) == 1)
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

int	ft_here_doc(t_exe *exec, t_env *built, t_b *b)
{
	char	*line;
	int		fd;
	char	*file_name;

	file_name = ft_create_filename(b->hd_count);
	if (access(file_name, F_OK) == 0)
		file_name = ft_here_doc_bis(file_name);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = NULL;
	ft_here_doc_prompt(line, exec->limiter[b->hd_count], built, fd);
	close(fd);
	ft_dup_here_doc(exec, file_name, b);
	free(file_name);
	return (0);
}
