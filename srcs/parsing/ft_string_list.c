/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:17:54 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 19:19:31 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_detect_single_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	ft_detect_double_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}

void	ft_get_join(t_parse *tmp)
{
	char	*string;
	t_parse	*to_delete;

	string = ft_strdup(tmp->arg);
	to_delete = tmp->next;
	if (to_delete && to_delete->arg && to_delete->arg[0] == tmp->arg[0])
	{
		string = ft_strjoin2(string, to_delete->arg);
		tmp->next = to_delete->next;
		ft_free_node(to_delete);
	}
	else
	{
		while (to_delete && to_delete->arg && to_delete->arg[0] != tmp->arg[0])
		{
			string = ft_strjoin2(string, to_delete->arg);
			tmp->next = to_delete->next;
			ft_free_node(to_delete);
			to_delete = tmp->next;
		}
		if (to_delete && to_delete->arg && to_delete->arg[0] == tmp->arg[0])
		{
			string = ft_strjoin2(string, to_delete->arg);
			tmp->next = to_delete->next;
			ft_free_node(to_delete);
		}
	}
	free(tmp->arg);
	tmp->arg = string;
}

void	ft_join_string(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp->arg && (tmp->arg[0] == 34 || tmp->arg[0] == 39))
			ft_get_join(tmp);
		tmp = tmp->next;
	}
}
