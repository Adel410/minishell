/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:46:47 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/05 13:02:10 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_char_is_separator1(char c, char *charset)
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

int	ft_count_words1(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && ft_char_is_separator1(str[i + 1], charset) == 1
			&& ft_char_is_separator1(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

void	ft_write_word1(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (ft_char_is_separator1(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_write_split1(char **split, char *str, char *charset)
{
	t_split_data3	data;
	int				j;

	data.split = split;
	data.str = str;
	data.charset = charset;
	data.i = 0;
	data.word = 0;
	while (data.str[data.i] != '\0')
	{
		ft_process_separator(&data);
		if (ft_char_is_separator1(data.str[data.i], data.charset) == 0)
		{
			j = 0;
			while (ft_char_is_separator1(data.str[data.i + j],
					data.charset) == 0)
				j++;
			data.split[data.word] = (char *)malloc(sizeof(char) * (j + 1));
			ft_write_word1(data.split[data.word], data.str + data.i,
				data.charset);
			data.i += j;
			data.word++;
		}
	}
	data.split[data.word] = NULL;
}

char	**ft_split3(char *str, char *charset)
{
	char	**split;
	int		words;

	words = ft_count_words1(str, charset);
	split = (char **)malloc(sizeof(char *) * (words + 10));
	split[words] = 0;
	ft_write_split1(split, str, charset);
	return (split);
}
