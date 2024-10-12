/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/12 17:01:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_copy_index(t_lex *lex, t_parse *tmp, char index)
{
	if (lex && tmp)
	{
		lex->type = index;
		if (tmp->arg)
			lex->str = ft_strdup(tmp->arg);
	}
}

void	ft_get_index(t_parse *tmp, t_lex *lex)
{
	if (tmp->arg && ft_strcmp(tmp->arg, ">") == 0)
		ft_copy_index(lex, tmp, '5');
	else if (tmp->arg && ft_strcmp(tmp->arg, ">>") == 0)
		ft_copy_index(lex, tmp, '#');
	else if (tmp->arg && ft_strcmp(tmp->arg, "<") == 0)
		ft_copy_index(lex, tmp, '6');
	else if (tmp->arg && ft_strcmp(tmp->arg, "<<") == 0)
		ft_copy_index(lex, tmp, '*');
	else if (tmp->arg && ft_strcmp(tmp->arg, "|") == 0)
		ft_copy_index(lex, tmp, '4');
	else if (tmp->arg && (tmp->arg[0] == '"'))
		ft_copy_index(lex, tmp, '2');
	else if (tmp->arg && (tmp->arg[0] == '\''))
		ft_copy_index(lex, tmp, '3');
	else if (lex->prev && (lex->prev->type == '5' || lex->prev->type == '#'))
		ft_copy_index(lex, tmp, '@');
	else if (lex->prev && (lex->prev->type == '6'))
		ft_copy_index(lex, tmp, '%');
	else if (lex->prev && (lex->prev->type == '*'))
		ft_copy_index(lex, tmp, ':');
	else
		ft_copy_index(lex, tmp, '8');
}

void	ft_indexing(t_parse *parse, t_lex *lex)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp)
	{
		while (tmp->arg && ft_strcmp(tmp->arg, " ") == 0)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			ft_get_index(tmp, lex);
		if (tmp->next && tmp->next->arg)
		{
			lex->next = ft_calloc(sizeof(t_lex), 1);
			if (lex->next == NULL)
				return ;
			lex->next->prev = lex;
			lex = lex->next;
			tmp = tmp->next;
		}
		else
			break ;
	}
}

int	ft_check_lexer(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == '4' || tmp->type == '5' || tmp->type == '6'
			|| tmp->type == '#' || tmp->type == '*')
		{
			if (tmp->next && (tmp->next->type == '4' || tmp->next->type == '5'
					|| tmp->next->type == '6' || tmp->next->type == '#'))
			{
				ft_putstr_fd("minishell: ", 2);
				return (ft_putstr_fd("syntax error near unexpected token\n", 2),
					1);
			}
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

void	ft_lexer(t_parse *parse, t_env *built)
{
	t_lex	*lex;

	lex = ft_calloc(sizeof(t_lex), 1);
	if (!lex)
	{
		ft_free_parser(parse);
		return ;
	}
	ft_indexing(parse, lex);
	ft_free_parser(parse);
	if (ft_check_lexer(lex) == 1)
	{
		built->exit_code = 2;
		ft_free_lex(lex);
		return ;
	}
	ft_execute(lex, built);
}
