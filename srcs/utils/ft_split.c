/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/04 14:52:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freetab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static char	*ft_put_word_in_malloc(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, s, i);
	word[i] = '\0';
	return (word);
}

static char	**ft_malloc_word(char *s, char c)
{
	int		i;
	int		j;
	int		word_count;
	char	**tab;

	i = 0;
	j = 0;
	word_count = ft_strlen(s);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_put_word_in_malloc(&s[i], c);
			if (!tab[j])
			{
				freetab(tab, j - 1);
				return (NULL);
			}
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
		else
		{
			tab[j] = malloc(sizeof(char) * 2);
			tab[j][0] = c;
			tab[j][1] = '\0';
			j++;
			i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_malloc_word(s, c));
}
