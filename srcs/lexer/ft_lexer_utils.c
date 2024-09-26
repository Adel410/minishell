/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:03:20 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 16:55:58 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strtrim(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	ft_strrtrim(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
		{
			str[i] = '\0';
			break ;
		}
		i--;
	}
}

void	ft_print_lex(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		printf("index == %c\n", tmp->type);
		printf("element == %s\n", tmp->str);
		tmp = tmp->next;
	}
}
