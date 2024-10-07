/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/07 14:00:22 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	ft_handle_non_separator(t_split_data *data)
{
	data->tab[data->j] = ft_put_word_in_malloc(&data->s[data->i], data->c);
	if (!data->tab[data->j])
	{
		freetab(data->tab, data->j - 1);
		return (0);
	}
	while (data->s[data->i] && data->s[data->i] != data->c)
		data->i++;
	data->j++;
	return (1);
}

static int	ft_handle_separator(t_split_data *data)
{
	data->tab[data->j] = malloc(sizeof(char) * 2);
	if (!data->tab[data->j])
	{
		freetab(data->tab, data->j - 1);
		return (0);
	}
	data->tab[data->j][0] = data->c;
	data->tab[data->j][1] = '\0';
	data->j++;
	data->i++;
	return (1);
}

static char	**ft_malloc_word(char *s, char c)
{
	t_split_data	data;

	data.s = s;
	data.c = c;
	data.i = 0;
	data.j = 0;
	data.word_count = ft_strlen(s);
	data.tab = malloc(sizeof(char *) * (data.word_count + 1));
	if (!data.tab)
		return (NULL);
	while (data.s[data.i])
	{
		if (data.s[data.i] != data.c)
		{
			if (!ft_handle_non_separator(&data))
				return (NULL);
		}
		else
		{
			if (!ft_handle_separator(&data))
				return (NULL);
		}
	}
	data.tab[data.j] = NULL;
	return (data.tab);
}

char	**ft_split(char *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_malloc_word(s, c));
}
