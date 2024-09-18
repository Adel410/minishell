/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:13:18 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/11 15:43:14 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define BUFFER_SIZE 1

char	*ft_remove(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = stash[i];
	return (line);
}

char	*ft_add(char *stash)
{
	char	*newstash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (stash[i] == '\0')
		return (ft_free_stash(stash));
	newstash = malloc(sizeof(char) * (strlen(stash) - i + 1));
	if (!newstash)
		return (ft_free_stash(stash));
	while (stash[i])
		newstash[j++] = stash[i++];
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

char	*ft_joined(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = strlen(s1);
	if (s2)
		len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = -1;
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

char	*read_line(int fd, char *save)
{
	char	*buffer;
	int		red;
	char	*temp;

	red = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_stash(save));
	while (red > 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == -1)
			return (ft_free_stash(buffer), ft_free_stash(save));
		buffer[red] = '\0';
		temp = ft_joined(save, buffer);
		free(save);
		save = temp;
		if (!save)
			ft_free_stash(save);
		if (strchr(save, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_remove(stash);
	stash = ft_add(stash);
	return (line);
}
