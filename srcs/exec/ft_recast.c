/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:21:18 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/18 16:38:53 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_recast_string(t_lex *lex, t_exe *new)
{
	if (new->here_doc == 1)
		new->limiter = ft_strdup(lex->str);
	else
		new->string = ft_strdup(lex->str);
}

void	ft_recast_meta(t_lex *lex, t_exe *new)
{
	if (lex->type == '#')
	{
		new->append_output = 1;
		if (lex->next && (lex->next->type == '2' || lex->next->type == '3'
				|| lex->next->type == '8'))
			new->output_file = ft_strdup(lex->next->str);
		else
			ft_putstr("minishell: syntax error\n");
	}
	else if (lex->type == '5')
	{
		if (lex->next && (lex->next->type == '2' || lex->next->type == '3'
				|| lex->next->type == '8'))
			new->output_file = ft_strdup(lex->next->str);
		else
			ft_putstr("minishell: syntax error\n");
	}
	else if (lex->type == '6')
	{
		if (lex->next && (lex->next->type == '2' || lex->next->type == '3'
				|| lex->next->type == '8'))
			new->input_file = ft_strdup(lex->next->str);
		else
			ft_putstr("minishell: syntax error\n");
	}
}

int	ft_check_for_options(t_lex *next, t_exe *new)
{
	if (next && next->type == '8' && next->str[0] == '-')
	{
		new->cmds[1] = ft_strdup(next->str);
		return (0);
	}
	else
	{
		new->cmds[1] = NULL;
		return (1);
	}
}

void	ft_recast_fts(t_lex *lex, t_exe *new)
{
	new->cmds = ft_calloc(10, sizeof(char *));
	if (new->cmds == NULL)
		return ;
	new->cmds[0] = ft_strdup(lex->str);
	if (lex->type == '9')
		new->builtin = 1;
	else
		new->builtin = 0;
	ft_check_for_options(lex->next, new);
}

void	ft_recast(t_lex *lex, t_exe *exec)
{
	t_exe	*new;

	new = exec;
	while (lex)
	{
		if (lex->type == '7' || lex->type == '9')
			ft_recast_fts(lex, new);
		else if (lex->type == '2' || lex->type == '3' || lex->type == '8')
			ft_recast_string(lex, new);
		else if (lex->type == '$')
			new->here_doc = 1;
		else if (lex->type == '5' || lex->type == '6' || lex->type == '#')
			ft_recast_meta(lex, new);
		if (lex->type == '4')
		{
			lex = lex->next;
			ft_create_new(new);
			new = new->next;
		}
		else
			lex = lex->next;
	}
	ft_check_here_doc(exec);
}
