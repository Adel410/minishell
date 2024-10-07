/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:34:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/07 13:47:13 by ahadj-ar         ###   ########.fr       */
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

void	ft_int_to_str(int num, char *buffer)
{
	int	i;
	int	temp;

	i = 0;
	temp = num;
	if (num == 0)
	{
		buffer[i++] = '0';
	}
	else
	{
		while (temp > 0)
		{
			temp /= 10;
			i++;
		}
		buffer[i] = '\0';
		while (num > 0)
		{
			buffer[--i] = (num % 10) + '0';
			num /= 10;
		}
	}
}

char	*ft_create_filename(int here_doc_count)
{
	char	*tmp;
	char	*count_str;

	printf("%d ======= HERE_DOC_COUNT\n", here_doc_count);
	tmp = ft_calloc(sizeof(char), 20);
	ft_strcpy(tmp, "here_doc_");
	count_str = ft_itoa(here_doc_count);
	ft_strcat(tmp, count_str);
	ft_strcat(tmp, ".tmp");
	free(count_str);
	return (tmp);
}

int	ft_here_doc(t_exe *exec, t_env *built, int here_doc_count)
{
	char	*line;
	char	*limiter;
	int		fd;
	char	*file_name;

	file_name = ft_create_filename(here_doc_count);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = NULL;
	limiter = NULL;
	if (exec->limiter)
		limiter = ft_strdup(exec->limiter);
	else
		return (1);
	ft_here_doc_prompt(line, limiter, built, fd);
	free(limiter);
	close(fd);
	exec->input_file = ft_strdup(file_name);
	free(file_name);
	return (0);
}
