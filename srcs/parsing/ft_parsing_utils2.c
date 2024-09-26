/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:50:50 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 16:16:36 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_meta_char(char c)
{
	int	i;

	i = 0;
	if (c == 34)
		return (1);
	if (c == 39)
		return (1);
	while (TOKEN[i])
	{
		if (c == TOKEN[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_meta_detect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_meta_char(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_find_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_meta_char(str[i]) == 1)
			return (i);
		i++;
	}
	return (i);
}

int	ft_check_parse_error(char **tab, int i, char token)
{
	if (tab[i + 1] && tab[i + 1][0] == token)
	{
		if (tab[i + 2] && tab[i + 2][0] == token)
			return (1);
	}
	return (0);
}

int	ft_check_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == '>')
		{
			if (ft_check_parse_error(tab, i, '>') == 1)
				return (printf("minishell : parse error near '%c'\n",
						tab[i][0]), 1);
		}
		else if (tab[i][0] == '<')
		{
			if (ft_check_parse_error(tab, i, '<') == 1)
				return (printf("minishell : parse error near '%c'\n",
						tab[i][0]), 1);
		}
		else if (tab[i][0] == '|')
		{
			if (ft_check_parse_error(tab, i, '|') == 1)
				return (printf("minishell : parse error near '%c'\n",
						tab[i][0]), 1);
		}
	}
	return (0);
}
