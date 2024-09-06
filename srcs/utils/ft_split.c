/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/06 17:14:07 by nicjousl         ###   ########.fr       */
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
	return ;
}

static int	ft_word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] || s[i] == '|' || s[i] == '>' || s[i] == '<')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_put_word_in_malloc(char *s, char c, char *tab)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c))
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static char	**ft_malloc_word(char **tab, char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 32 )
		{
			tab[k] = ft_malloc_copy_char(c);
			k++;
			i++;
		}
		if (s[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			tab[k] = malloc(sizeof(char) * (j + 1));
			if (!tab[k])
				freetab(tab, k - 1);
			tab[k] = ft_put_word_in_malloc(&s[i], c, tab[k]);
			i = i + j;
			k++;
		}
	}
	tab[k] = NULL;
	return (tab);
}

//fake split
char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word_count;

	if (!s)
		return (0);
	word_count = ft_word_count((char *)s, c);
	tab = malloc(sizeof(char *) * (10000 + 1));
	if (!tab)
		return (NULL);
	//tab[word_count] = NULL;
	ft_malloc_word(tab, (char *)s, c);
	return (tab);
}
