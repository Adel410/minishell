/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_to_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:48:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/18 15:54:14 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lex	*ft_lstnew2(char *str)
{
	t_lex	*new_node;

	new_node = ft_calloc(sizeof(t_lex), 1);
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->str = ft_strdup(str);
	new_node->next = NULL;
	return (new_node);
}

void	ft_print_lst(t_lex *head)
{
	t_lex	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		printf("str: %s\n", ptr->str);
		ptr = ptr->next;
	}
}

void	ft_recast_to_lst(t_a *a, t_lex *lex)
{
	int		i;
	t_lex	*new;

	i = 0;
	new = lex;
	while (a->tab_cmd[i])
	{
		new->str = ft_strdup(a->tab_cmd[i][0]);
		new->type = a->tab_cmd[i][1][0];
		if (new->next == NULL)
		{
			new->next = ft_calloc(1, sizeof(t_lex));
			if (new->next == NULL)
				return ;
			new->next->next = NULL;
		}
		new = new->next;
		i++;
	}
	// ft_print_lst(lex);
}
