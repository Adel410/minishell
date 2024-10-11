/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:21:18 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:33:44 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_recast_meta(t_lex *lex, t_exe *new, t_b *b)
{
	if ((lex->type == '5' || lex->type == '6' || lex->type == '#'
			|| lex->type == '*') && lex->next == NULL)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (2);
	}
	if (lex->type == '#')
		new->append_output = 1;
	else if (lex->type == '@' || lex->type == '%')
		ft_infile_outfile(lex, new, b, lex->type);
	return (0);
}

void	ft_recast_fts(t_lex *lex, t_exe *new, t_b *b)
{
	if (new->cmds == NULL)
	{
		if (lex->str)
		{
			new->cmds = ft_calloc(b->nb_cmds1 + 1, sizeof(char *));
			if (new->cmds == NULL)
				return ;
			new->cmds[0] = ft_strdup(lex->str);
			if (ft_is_builtin(lex->str) == 1)
				new->builtin = 1;
		}
		else
			new->cmds = NULL;
	}
	else
		ft_check_for_options(lex, new);
}

void	ft_recast_limiter(t_lex *lex, t_exe *new, t_b *b)
{
	if (lex->str)
	{
		if (new->limiter == NULL)
		{
			new->hd_index = 0;
			new->limiter = ft_calloc(sizeof(char *), b->limiter_count + 1);
			if (new->limiter == NULL)
				return ;
			new->limiter[b->limiter_count] = NULL;
		}
		if (new->hd_index < b->limiter_count)
		{
			new->limiter[new->hd_index] = ft_strdup(lex->str);
			if (new->limiter[new->hd_index] != NULL)
				new->hd_index++;
		}
	}
}

int	ft_get_type(t_lex *lex, t_exe *new, t_b *b)
{
	if (!lex)
		return (1);
	if (lex->type == '8' && lex->str && ft_strcmp(lex->str, " ") == 0)
		return (1);
	if (lex->type == '5' || lex->type == '6' || lex->type == '#'
		|| lex->type == '*' || lex->type == '@' || lex->type == '%')
		ft_recast_meta(lex, new, b);
	else if (lex->type == ':')
		ft_recast_limiter(lex, new, b);
	else if (lex->type == '8' || lex->type == '2' || lex->type == '3')
		ft_recast_fts(lex, new, b);
	return (0);
}

int	ft_recast(t_lex *lex, t_exe *exec, t_env *built, t_b *b)
{
	t_exe	*new;

	new = exec;
	while (lex)
	{
		ft_get_type(lex, new, b);
		if (lex->type == '4')
		{
			lex = lex->next;
			ft_create_new(new);
			new = new->next;
		}
		else
			lex = lex->next;
	}
	ft_check_list(exec, built, b);
	return (0);
}
