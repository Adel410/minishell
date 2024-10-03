/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:21:18 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 18:47:23 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_recast_meta(t_lex *lex, t_exe *new)
{
	if ((lex->type == '5' || lex->type == '6' || lex->type == '#'
			|| lex->type == '*') && lex->next == NULL)
	{
		ft_putstr("bash: syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (lex->type == '#')
		new->append_output = 1;
	else if (lex->type == '*')
	{
		new->here_doc = 1;
		new->input_file = ft_strdup("here_doc");
	}
	else if (lex->type == '@')
		new->output_file = ft_strdup(lex->str);
	else if (lex->type == '%')
		new->input_file = ft_strdup(lex->str);
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
		new->cmds = ft_calloc(b->nb_cmds1 + 1, sizeof(char *));
		if (new->cmds == NULL)
			return ;
		new->cmds[0] = ft_strdup(lex->str);
		if (ft_is_builtin(lex->str) == 1)
			new->builtin = 1;
		else
			new->builtin = 0;
	}
	else
		ft_check_for_options(lex, new);
}

int	ft_get_type(t_lex *lex, t_exe *new, t_b *b)
{
	int	check;

	check = 0;
	if (lex->type == '8' && ft_strcmp(lex->str, " ") == 0)
		return (1);
	if (lex->type == '5' || lex->type == '6' || lex->type == '#'
		|| lex->type == '*' || lex->type == '@' || lex->type == '%')
		check = ft_recast_meta(lex, new);
	else if (lex->type == ':')
		new->limiter = ft_strdup(lex->str);
	else if (lex->type == '8' || lex->type == '2' || lex->type == '3')
		ft_recast_fts(lex, new, b);
	return (check);
}

int	ft_recast(t_lex *lex, t_exe *exec, t_env *built, t_b *b)
{
	t_exe	*new;
	int		check;

	new = exec;
	check = 0;
	while (lex)
	{
		check = ft_get_type(lex, new, b);
		built->exit_code = check;
		if (lex->type == '4')
		{
			lex = lex->next;
			ft_create_new(new);
			new = new->next;
		}
		else
			lex = lex->next;
	}
	ft_check_list(exec);
	ft_check_here_doc(exec, built);
	if (check != 0)
		return (1);
	return (0);
}
