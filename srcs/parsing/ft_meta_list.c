/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:16:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 19:16:24 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parse	*ft_rejoin_list(t_parse *tmp, int i, char **tab, int size)
{
	while (i < size)
	{
		tmp->arg = ft_strdup(tab[i]);
		// if (!tmp->arg)
		// 	ft_free_tab_and_parse(tab, tmp);
		if (i + 1 < size)
		{
			tmp->next = ft_calloc(sizeof(t_parse), 1);
			// if (!tmp->next)
			// 	ft_free_parse_and_crash(tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (tmp);
}

void	ft_split_meta(t_parse *tmp)
{
	char	**tab;
	int		i;
	int		size;
	t_parse	*tmp2;

	i = 0;
	tab = ft_split3(tmp->arg, TOKEN);
	// if (!tab)
	// 	ft_free_tab_and_parse(tab, tmp);
	if (ft_check_tab(tab) != 0)
	{
		ft_free_tab(tab);
		ft_free_parser(tmp);
		return ;
	}
	free(tmp->arg);
	tmp2 = tmp->next;
	size = ft_strstrlen(tab);
	tmp = ft_rejoin_list(tmp, i, tab, size);
	tmp->next = tmp2;
	ft_free_tab(tab);
}

void	ft_meta_arg(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp->next)
	{
		if (ft_meta_detect(tmp->arg) == 1)
			ft_split_meta(tmp);
		if (tmp->next)
			tmp = tmp->next;
	}
}
