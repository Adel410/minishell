/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nice_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:41:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/07 14:52:54 by ahadj-ar         ###   ########.fr       */
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

void	ft_check_double_redir(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->arg && tmp->next->arg)
		{
			if (tmp && tmp->arg && tmp->next && tmp->next->arg
				&& tmp->arg[0] == '>' && tmp->next->arg[0] == '>')
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

int	ft_unclosed_quote(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (str[0] == '\'')
	{
		if (str[len - 1] != '\'' && (len - 1) == 0)
			return (1);
	}
	else if (str[0] == '\"')
	{
		if (str[len - 1] != '\"' && (len - 1) == 0)
			return (1);
	}
	else
		ft_putstr("pas d'erreur\n");
	return (0);
}

int	ft_check_unclosed_quote(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp && tmp->arg)
			return (ft_unclosed_quote(tmp->arg));
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

void	ft_parsing(t_parse *parse, t_env *built, char **env)
{
	ft_space_arg(parse);
	ft_meta_arg(parse);
	if (ft_join_string(parse) == 1)
	{
		printf("error\n");
		return ;
	}
	ft_check_double_redir(parse);
	// ft_printf_lst(parse);
	// if (ft_check_unclosed_quote(parse) == 1)
	// {
	// 	ft_putstr("Error: unclosed quote\n");
	// 	ft_free_parser(parse);
	// 	return ;
	// }
	ft_expand_arg(parse, built);
	ft_concatenate(parse);
	ft_lexer(parse, built, env);
}
