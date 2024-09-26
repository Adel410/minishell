/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:46:47 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 13:31:06 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_is_separator1(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (i);
		i++;
	}
	if (c == '\0')
		return (-1);
	return (0);
}

int	count_words1(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && char_is_separator1(str[i + 1], charset) == 1
			&& char_is_separator1(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

void	write_word1(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (char_is_separator1(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split1(char **split, char *str, char *charset)
{
	int	i;
	int	j;
	int	word;
	int	cha;

	word = 0;
	i = 0;
	cha = 0;
	while (str[i] != '\0')
	{
		cha = char_is_separator1(str[i], charset);
		if (cha > 0)
		{
			split[word] = malloc(sizeof(char) * 2);
			split[word][0] = charset[cha];
			split[word][1] = '\0';
			word++;
			i++;
		}
		else
		{
			j = 0;
			while (char_is_separator1(str[i + j], charset) == 0)
				j++;
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			write_word1(split[word], str + i, charset);
			i += j;
			word++;
		}
		split[word] = NULL;
	}
}

char	**ft_split3(char *str, char *charset)
{
	char	**split;
	int		words;

	words = count_words1(str, charset);
	split = (char **)malloc(sizeof(char *) * (words + 10));
	split[words] = 0;
	write_split1(split, str, charset);
	return (split);
}
