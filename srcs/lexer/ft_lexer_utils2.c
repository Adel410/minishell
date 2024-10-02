/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:35:44 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/02 16:40:23 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_test_if_execute(char *arg, char **env)
{
	char	*path;
	char	**cmd_path;

	if (arg[0] == '\0')
		return (0);
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

void	ft_join_echo_args(t_parse *tmp, t_lex *lex, char index)
{
	if (tmp->next && tmp->next->arg && ft_strcmp(tmp->next->arg, " ") == 0)
	{
		lex->type = index;
		lex->str = ft_strjoin2(tmp->arg, " ");
	}
	else
	{
		lex->type = index;
		if (tmp->arg)
			lex->str = ft_strdup(tmp->arg);
	}
}

int	ft_manage_string(t_lex *lex, t_parse *tmp, char index)
{
	if (index == '2')
	{
		ft_strtrim(tmp->arg, '"');
		ft_strrtrim(tmp->arg, '"');
		if (lex->flag_echo == 1)
			ft_join_echo_args(tmp, lex, index);
		return (1);
	}
	else if (index == '3')
	{
		ft_strtrim(tmp->arg, '\'');
		ft_strrtrim(tmp->arg, '\'');
		if (lex->flag_echo == 1)
			ft_join_echo_args(tmp, lex, index);
		return (1);
	}
	else if (index == '8')
	{
		if (lex->flag_echo == 1)
			ft_join_echo_args(tmp, lex, index);
		return (1);
	}
	return (0);
}
