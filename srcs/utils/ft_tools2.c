/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:25:44 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 19:55:17 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmpchar(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != c)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_free_stash(char *str)
{
	if (str)
		free(str);
	return (NULL);
}