/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:15:24 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 12:15:51 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_space_arg(t_parse *parse)
{
	t_parse	*tmp;
	int		i;
	char	**tab;

	tmp = parse;
	tab = ft_split(tmp->arg, ' ');
	i = 0;
	free(tmp->arg);
	while (tab[i])
	{
		tmp->arg = ft_strdup(tab[i]);
		tmp->next = ft_calloc(sizeof(t_parse), 1);
		tmp = tmp->next;
		i++;
	}
	ft_free_tab(tab);
}
