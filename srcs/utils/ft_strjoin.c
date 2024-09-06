/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:49:10 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/06 17:14:22 by nicjousl         ###   ########.fr       */
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

//fake strjoin
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		size;

	size = ft_size(s1, s2);
	str = ft_calloc (sizeof (char *), size + 2);
	if (!str)
		return (NULL);
	str = ft_join(str, s1, s2);
	return (str);
}
