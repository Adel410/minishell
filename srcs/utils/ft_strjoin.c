/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:49:10 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/07 14:02:18 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_size(char const *s1, char const *s2)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	size = i + j;
	return (size);
}

char	*ft_join(char *str, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	str[i] = ' ';
	i++;
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen_stat(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

// vrai strjoin
char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	index;
	size_t	j;
	char	*ptr;

	j = 0;
	index = ft_strlen_stat(s1) + ft_strlen_stat(s2) + 1;
	ptr = (char *)malloc(index);
	index = 0;
	if (ptr == NULL)
		return (NULL);
	while (s1[index])
	{
		ptr[j] = s1[index];
		index++;
		j++;
	}
	index = 0;
	while (s2[index])
	{
		ptr[j] = s2[index];
		index++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strjoin3(char *s1, char *s2)
{
	size_t	index;
	size_t	j;
	char	*ptr;

	j = 0;
	index = ft_strlen_stat(s1) + ft_strlen_stat(s2) + 1;
	ptr = (char *)malloc(index);
	index = 0;
	while (s1[index])
	{
		ptr[j] = s1[index];
		index++;
		j++;
	}
	index = 0;
	while (s2[index])
	{
		ptr[j] = s2[index];
		index++;
		j++;
	}
	ptr[j] = '\0';
	(free(s1), free(s2));
	return (ptr);
}
