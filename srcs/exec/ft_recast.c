/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:21:18 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 19:38:55 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_recast_string(t_lex *lex, t_exe *new)
{
	if (new->string && (lex->type == '2' || lex->type == '3'))
		new->string = ft_strjoin(new->string, lex->str);
	else
		new->string = ft_strdup(lex->str);
}

void	ft_recast_meta(t_lex *lex, t_exe *new)
{
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
}

int	ft_check_for_options(t_lex *next, t_exe *new)
{
	int	i;

	i = 1;
	while (new->cmds[i] != NULL)
		i++;
	new->cmds[i] = ft_strdup(next->str);
	return (0);
}

void	ft_recast_fts(t_lex *lex, t_exe *new)
{
	if (new->cmds == NULL)
	{
		new->cmds = ft_calloc(10, sizeof(char *));
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

void	ft_recast(t_lex *lex, t_exe *exec)
{
	t_exe	*new;

	new = exec;
	while (lex)
	{
		if (lex->type == '5' || lex->type == '6' || lex->type == '#'
			|| lex->type == '*' || lex->type == '@' || lex->type == '%')
			ft_recast_meta(lex, new);
		else if (lex->type == ':')
			new->limiter = ft_strdup(lex->str);
		else if (lex->type == '2' || lex->type == '3')
			ft_recast_string(lex, new);
		else if (lex->type == '8')
			ft_recast_fts(lex, new);
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
