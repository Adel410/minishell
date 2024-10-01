/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:04:18 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/01 15:05:33 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	overflow;

	overflow = nmemb * size;
	if (overflow == 0)
	{
		tab = malloc(1);
		if (!tab)
			return (NULL);
		return (tab);
	}
	if (size && overflow / size != nmemb)
		return (NULL);
	tab = malloc(nmemb * size);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
