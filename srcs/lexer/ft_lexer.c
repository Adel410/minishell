/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/25 15:27:12 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_test_if_execute(char *arg, char **env)
{
	char	*path;
	char	**cmd_path;

	path = NULL;
	path = ft_get_path(path, env);
	cmd_path = ft_split4(path, ':');
	free(path);
	ft_add_slash_to_paths(cmd_path);
	if (ft_check_access(arg, cmd_path) == 1)
		return (1);
	else
		return (0);
}

void	ft_copy_index(t_lex *lex, char *arg, char index, char **env)
{
	if (index == '2')
	{
		ft_strtrim(arg, '"');
		ft_strrtrim(arg, '"');
		if (ft_test_if_execute(arg, env) == 1)
			index = '8';
	}
	else if (index == '3')
	{
		ft_strtrim(arg, '\'');
		ft_strrtrim(arg, '\'');
		if (ft_test_if_execute(arg, env) == 1)
			index = '8';
	}
	lex->type = index;
	lex->str = ft_strdup(arg);
}

void	ft_get_index(t_parse *tmp, t_lex *tmp_lex, char **env)
{
	if (tmp->arg && ft_strcmp(tmp->arg, ">") == 0)
		ft_copy_index(tmp_lex, tmp->arg, '5', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, ">>") == 0)
		ft_copy_index(tmp_lex, tmp->arg, '#', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "<") == 0)
		ft_copy_index(tmp_lex, tmp->arg, '6', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "<<") == 0)
		ft_copy_index(tmp_lex, tmp->arg, '*', env);
	else if (tmp->arg && ft_strcmp(tmp->arg, "|") == 0)
		ft_copy_index(tmp_lex, tmp->arg, '4', env);
	else if (tmp->arg && (tmp->arg[0] == '"'))
		ft_copy_index(tmp_lex, tmp->arg, '2', env);
	else if (tmp->arg && (tmp->arg[0] == '\''))
		ft_copy_index(tmp_lex, tmp->arg, '3', env);
	else if (tmp_lex->prev && (tmp_lex->prev->type == '5'
			|| tmp_lex->prev->type == '#'))
		ft_copy_index(tmp_lex, tmp->arg, '@', env);
	else if (tmp_lex->prev && (tmp_lex->prev->type == '6'))
		ft_copy_index(tmp_lex, tmp->arg, '%', env);
	else if (tmp_lex->prev && (tmp_lex->prev->type == '*'))
		ft_copy_index(tmp_lex, tmp->arg, ':', env);
	else
		ft_copy_index(tmp_lex, tmp->arg, '8', env);
}

void	ft_indexing(t_parse *parse, t_lex *lex, char **env)
{
	t_parse	*tmp;
	t_lex	*tmp_lex;

	tmp = parse;
	tmp_lex = lex;
	while (tmp->next)
	{
		if (tmp->arg && ft_strcmp(tmp->arg, " ") == 0)
			tmp = tmp->next;
		else
		{
			ft_get_index(tmp, tmp_lex, env);
			if (tmp->next->next != NULL)
			{
				tmp_lex->next = ft_calloc(sizeof(t_lex), 1);
				if (tmp_lex->next == NULL)
					return ;
				tmp_lex->next->prev = tmp_lex;
				tmp_lex = tmp_lex->next;
				tmp = tmp->next;
			}
			else
				break ;
		}
	}
}

void	ft_lexer(t_parse *parse, t_env *built, char **env)
{
	t_lex	*lex;

	lex = ft_calloc(sizeof(t_lex), 1);
	if (lex == NULL)
		return ;
	ft_indexing(parse, lex, env);
	ft_free_parser(parse);
	ft_execute(lex, built, env);
}
