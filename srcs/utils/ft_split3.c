/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:46:47 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_separator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '"' || c == '\''
		|| c == ' ');
}

int	ft_count_words1(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (ft_is_separator(str[i]))
		{
			if (in_word)
				count++;
			count++;
			in_word = 0;
		}
		else if (!in_word)
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

void	ft_write_word(char **split, char *str, int len, int *index)
{
	split[*index] = malloc(len + 1);
	ft_strncpy(split[*index], str, len);
	split[*index][len] = '\0';
	(*index)++;
}

void	ft_write_split1(char **split, char *str, int max_words)
{
	int	i;
	int	word_start;
	int	word_index;

	i = 0;
	word_start = 0;
	word_index = 0;
	while (str[i] && word_index < max_words - 1)
	{
		if (ft_is_separator(str[i]))
		{
			if (i > word_start)
				ft_write_word(split, str + word_start, i - word_start,
					&word_index);
			ft_write_word(split, str + i, 1, &word_index);
			word_start = i + 1;
		}
		i++;
	}
	if (i > word_start && word_index < max_words - 1)
		ft_write_word(split, str + word_start, i - word_start, &word_index);
	split[word_index] = NULL;
}

char	**ft_split3(char *str)
{
	char	**split;
	int		words;

	words = ft_count_words1(str);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	ft_write_split1(split, str, words + 1);
	return (split);
}
