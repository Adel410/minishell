/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:17:54 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/07 14:55:28 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_old_string(char *old_string, char *arg)
{
	if (old_string != arg)
		free(old_string);
}

void	ft_get_join2(t_parse *tmp)
{
	char	*string;
	char	*old_string;
	t_parse	*to_delete;

	string = tmp->arg;
	to_delete = tmp->next;
	while (to_delete && to_delete->arg && to_delete->arg[0] != tmp->arg[0])
	{
		old_string = string;
		string = ft_strjoin2(string, to_delete->arg);
		ft_check_old_string(old_string, tmp->arg);
		tmp->next = to_delete->next;
		ft_free_node(to_delete);
		to_delete = tmp->next;
	}
	if (to_delete && to_delete->arg && to_delete->arg[0] == tmp->arg[0])
	{
		old_string = string;
		string = ft_strjoin2(string, to_delete->arg);
		ft_check_old_string(old_string, tmp->arg);
		tmp->next = to_delete->next;
		ft_free_node(to_delete);
	}
	free(tmp->arg);
	tmp->arg = string;
}

void	ft_get_join(t_parse *tmp)
{
	char	*string;
	t_parse	*to_delete;

	string = tmp->arg;
	to_delete = tmp->next;
	if (to_delete && to_delete->arg && to_delete->arg[0] == tmp->arg[0])
	{
		string = ft_strjoin2(string, to_delete->arg);
		tmp->next = to_delete->next;
		ft_free_node(to_delete);
		free(tmp->arg);
		tmp->arg = string;
	}
	else
		ft_get_join2(tmp);
}

int	ft_check_if_quote(t_parse *tmp, char c)
{
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->arg[0] == c)
			return (1);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

int	ft_check_if_joinable(t_parse *tmp)
{
	int	flag;

	flag = 0;
	while (tmp)
	{
		if (tmp->arg && tmp->arg[0] == '"')
		{
			flag = 1;
			if (tmp->next)
			{
				flag += ft_check_if_quote(tmp->next, tmp->arg[0]);
				printf("flag === %d\n", flag);
				if (flag != 2)
					return (1);
				else
					return (0);
			}
			else
				return (1);
		}
		if (tmp->arg && tmp->arg[0] == '\'')
		{
			flag = 1;
			flag += ft_check_if_quote(tmp, tmp->arg[0]);
			printf("flag === %d\n", flag);
			if (flag != 2)
				return (1);
			else
				return (0);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

int	ft_join_string(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	if (ft_check_if_joinable(tmp) == 0)
	{
		while (tmp)
		{
			if (tmp->arg && (tmp->arg[0] == 34 || tmp->arg[0] == 39))
				ft_get_join(tmp);
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (1);
}
