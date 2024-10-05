/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:56:08 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/05 13:05:34 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_process_separator(t_split_data3 *data)
{
	int	cha;

	cha = ft_char_is_separator1(data->str[data->i], data->charset);
	if (cha > 0)
	{
		data->split[data->word] = malloc(sizeof(char) * 2);
		data->split[data->word][0] = data->charset[cha];
		data->split[data->word][1] = '\0';
		data->word++;
		data->i++;
	}
}

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
