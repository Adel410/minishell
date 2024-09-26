/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:49:33 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/25 17:57:40 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	i = ft_strlen(s);
	dest = ft_calloc(sizeof(char), i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup2(const char *s, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (10240));
	if (!dest)
		return (NULL);
	while (s[n])
	{
		dest[i] = s[n];
		i++;
		n++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_master_strndup(char *s, int start, int size)
{
	char	*dest;
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start < 0 || start >= s_len)
		return (NULL);
	if (size > s_len - start)
		size = s_len - start;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size && s[start])
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_malloc_copy_char(char c)
{
	char	*dest;

	dest = malloc(2);
	if (!dest)
		return (NULL);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}
