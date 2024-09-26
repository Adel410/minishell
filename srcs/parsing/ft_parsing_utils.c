/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:19:08 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 18:02:02 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_parser(t_parse *parse)
{
	t_parse	*tmp;
	t_parse	*tmp2;

	tmp = parse;
	if (tmp == NULL)
	{
		return ;
	}
	else if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->next)
				tmp2 = tmp->next;
			free(tmp->arg);
			tmp = tmp2;
		}
	}
}

void	ft_printf_lst(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp->next)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}

void	ft_free_node(t_parse *node)
{
	free(node->arg);
	free(node);
}

int	ft_string_is_closed(char *str)
{
	int	i;
	int	size;

	size = ft_strlen(str);
	i = 0;
	if (str[size - 1] == str[i])
		return (1);
	return (0);
}
