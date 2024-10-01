/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:34:37 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/01 16:38:32 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	size_t index;
	size_t j;
	char *ptr;

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
