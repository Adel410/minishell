/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:21:18 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/10 22:18:23 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_infile_outfile(t_lex *lex, t_exe *new, t_b *b, char c)
{
	if (!lex->str)
		return ;
	if (c == '@')
	{
		if (new->output_file == NULL)
		{
			b->output_index = 0;
			new->output_file = ft_calloc(sizeof(char *), b->nb_cmds1 + 1);
			if (new->output_file == NULL)
				return ;
			new->output_file[b->nb_cmds1] = NULL;
		}
		if (b->output_index < b->nb_cmds1)
		{
			new->output_file[b->output_index] = ft_strdup(lex->str);
			if (new->output_file[b->output_index] != NULL)
				b->output_index++;
		}
	}
	else if (c == '%')
	{
		if (new->input_file == NULL)
		{
			b->input_index = 0;
			new->input_file = ft_calloc(sizeof(char *), b->nb_cmds1 + 1);
			if (new->input_file == NULL)
				return ;
			new->input_file[b->nb_cmds1] = NULL;
		}
		if (b->input_index < b->nb_cmds1)
		{
			new->input_file[b->input_index] = ft_strdup(lex->str);
			if (new->input_file[b->input_index] != NULL)
				b->input_index++;
		}
	}
}

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

int	ft_check_for_options(t_lex *next, t_exe *new)
{
	int	i;

	i = 1;
	if (next->str && next->str[0] == '\0')
		return (0);
	else if (next->str && next->str[0] == ' ' && next->str[0] == '\0')
		return (0);
	while (new->cmds[i] != NULL)
		i++;
	if (next->str)
		new->cmds[i] = ft_strdup(next->str);
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
	int	i;

	i = 0;
	if (new->limiter == NULL)
	{
		new->hd_index = 0;
		new->limiter = ft_calloc(sizeof(char *), b->nb_cmds1 + 1);
		if (new->limiter == NULL)
			return ;
		new->limiter[b->nb_cmds1] = NULL;
	}
	if (new->hd_index < b->nb_cmds1)
	{
		new->limiter[new->hd_index] = ft_strdup(lex->str);
		if (new->limiter[new->hd_index] != NULL)
			new->hd_index++;
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
