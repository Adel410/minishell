/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nice_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:41:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/26 19:54:40 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_join_double_redir(t_parse *tmp, int redir_type)
{
	char	*new_arg;
	t_parse	*to_free;

	if (!tmp || !tmp->arg || !tmp->next || !tmp->next->arg)
		return ;
	if (redir_type == 1)
		new_arg = ft_strdup(">>");
	else
		new_arg = ft_strdup("<<");
	if (!new_arg)
		return ;
	free(tmp->arg);
	tmp->arg = new_arg;
	to_free = tmp->next;
	tmp->next = tmp->next->next;
	free(to_free->arg);
	free(to_free);
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
				ft_join_double_redir(tmp, 1);
			else if (tmp->arg[0] == '<' && tmp->next->arg[0] == '<')
				ft_join_double_redir(tmp, 2);
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_parsing(t_parse *parse, t_env *built, char **env)
{
	ft_space_arg(parse);
	ft_meta_arg(parse);
	ft_join_string(parse);
	ft_check_double_redir(parse);
	ft_expand_arg(parse, built);
	ft_lexer(parse, built, env);
}
