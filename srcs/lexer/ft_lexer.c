/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/04 18:28:00 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_copy_index(t_lex *lex, t_parse *tmp, char index, char **env)
{
	if (lex->flag_echo == 1)
	{
		if (ft_manage_string(lex, tmp, index) == 1)
			return ;
	}
	else if (index == '2')
	{
		(ft_strtrim(tmp->arg, '"'), ft_strrtrim(tmp->arg, '"'));
		if (ft_test_if_execute(tmp->arg, env) == 1)
			index = '8';
	}
	else if (index == '3')
	{
		(ft_strtrim(tmp->arg, '\''), ft_strrtrim(tmp->arg, '\''));
		if (ft_test_if_execute(tmp->arg, env) == 1)
			index = '8';
	}
	lex->type = index;
	if (tmp->arg)
		lex->str = ft_strdup(tmp->arg);
	if (index == '4')
		lex->flag_echo = 0;
	if ((lex->str && ft_strcmp(lex->str, "echo") == 0) || (lex->str
			&& ft_strcmp(lex->str, "export") == 0))
		lex->flag_echo = 1;
}

void	ft_get_index(t_parse *tmp, t_lex *lex, char **env)
{
	if (tmp->arg && ft_strcmp(tmp->arg, ">") == 0)
		ft_copy_index(lex, tmp, '5', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, ">>") == 0)
		ft_copy_index(lex, tmp, '#', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "<") == 0)
		ft_copy_index(lex, tmp, '6', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "<<") == 0)
		ft_copy_index(lex, tmp, '*', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "|") == 0)
		ft_copy_index(lex, tmp, '4', env);
	else if (tmp->arg && (tmp->arg[0] == '"'))
		ft_copy_index(lex, tmp, '2', env);
	else if (tmp->arg && (tmp->arg[0] == '\''))
		ft_copy_index(lex, tmp, '3', env);
	else if (lex->prev && (lex->prev->type == '5' || lex->prev->type == '#'))
		ft_copy_index(lex, tmp, '@', env);
	else if (lex->prev && (lex->prev->type == '6'))
		ft_copy_index(lex, tmp, '%', env);
	else if (lex->prev && (lex->prev->type == '*'))
		ft_copy_index(lex, tmp, ':', env);
	else
		ft_copy_index(lex, tmp, '8', env);
}

void	ft_indexing(t_parse *parse, t_lex *lex, char **env)
{
	t_parse	*tmp;
	t_lex	*tmp_lex;
	int		flag;

	tmp = parse;
	tmp_lex = lex;
	while (tmp)
	{
		if (tmp->arg && tmp->arg[0] == ' ' && tmp->arg[1] == '\0')
			tmp = tmp->next;
		ft_get_index(tmp, tmp_lex, env);
		flag = tmp_lex->flag_echo;
		if (tmp->next && tmp->next->next != NULL)
		{
			tmp_lex->next = ft_calloc(sizeof(t_lex), 1);
			if (tmp_lex->next == NULL)
				return ;
			tmp_lex->next->prev = tmp_lex;
			tmp_lex = tmp_lex->next;
			tmp_lex->flag_echo = flag;
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
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp->str == NULL && tmp->type == '8')
	{
		tmp = tmp->prev;
		free(tmp->next);
		tmp->next = NULL;
	}
	else if (tmp->type == '4' || tmp->type == '5' || tmp->type == '6'
		|| tmp->type == '#' || tmp->type == '*')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->str, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

void	ft_lexer(t_parse *parse, t_env *built, char **env)
{
	t_lex	*lex;

	lex = ft_calloc(sizeof(t_lex), 1);
	lex->flag_echo = 0;
	if (lex == NULL)
		return ;
	ft_indexing(parse, lex, env);
	ft_free_parser(parse);
	if (ft_check_lexer(lex) == 1)
		return ;
	ft_execute(lex, built);
}
