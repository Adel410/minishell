/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:03:02 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:03:41 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_join_double_redir(t_parse *tmp, int redir_type)
{
	char	*new_arg;
	t_parse	*to_free;

	to_free = NULL;
	if (!tmp || !tmp->arg || !tmp->next || !tmp->next->arg)
		return ;
	if (redir_type == 1)
		new_arg = ft_strdup(">>");
	else
		new_arg = ft_strdup("<<");
	free(tmp->arg);
	tmp->arg = new_arg;
	to_free = tmp->next;
	tmp->next = tmp->next->next;
	free(to_free->arg);
	free(to_free);
}

void	ft_check_redir_type(t_parse **tmp, char redir_char)
{
	if ((*tmp)->next->next && (*tmp)->next->next->arg
		&& (*tmp)->next->next->arg[0] != redir_char)
	{
		if (redir_char == '>')
			ft_join_double_redir(*tmp, 1);
		else if (redir_char == '<')
			ft_join_double_redir(*tmp, 2);
		*tmp = (*tmp)->next;
	}
	else
		*tmp = (*tmp)->next->next;
}

void	ft_check_double_redir(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp && tmp->next)
	{
		if (tmp->arg && tmp->next->arg)
		{
			if (tmp->arg[0] == '>' && tmp->next->arg[0] == '>')
				ft_check_redir_type(&tmp, '>');
			else if (tmp->arg[0] == '<' && tmp->next->arg[0] == '<')
				ft_check_redir_type(&tmp, '<');
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
