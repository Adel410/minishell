/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:34:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/10 22:05:42 by ahadj-ar         ###   ########.fr       */
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

	tmp = ft_calloc(sizeof(char), 20);
	ft_strcpy(tmp, "here_doc_");
	count_str = ft_itoa(here_doc_count);
	ft_strcat(tmp, count_str);
	ft_strcat(tmp, ".tmp");
	free(count_str);
	return (tmp);
}

void	ft_dup_here_doc(t_exe *exec, char *file_name, int nb_count1)
{
	int	i;

	if (exec->input_file == NULL)
	{
		exec->input_file = ft_calloc(sizeof(char *), nb_count1 + 1);
		if (exec->input_file == NULL)
			return ;
	}
	i = 0;
	while (i < nb_count1 && exec->input_file[i] != NULL)
		i++;
	if (i < nb_count1)
	{
		exec->input_file[i] = ft_strdup(file_name);
		if (exec->input_file[i] == NULL)
			return ;
		exec->input_file[i + 1] = NULL;
	}
}

char	*ft_here_doc_bis(char *str)
{
	char	*tmp;

	tmp = ft_strjoin2(str, "_bis");
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

int	ft_here_doc(t_exe *exec, t_env *built, t_b *b)
{
	char	*line;
	int		fd;
	int		i;
	char	*file_name;

	i = 0;
	file_name = ft_create_filename(b->hd_count);
	if (access(file_name, F_OK) == 0)
		file_name = ft_here_doc_bis(file_name);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = NULL;
	ft_here_doc_prompt(line, exec->limiter[b->hd_count], built, fd);
	close(fd);
	ft_dup_here_doc(exec, file_name, b->nb_cmds1);
	free(file_name);
	return (0);
}
