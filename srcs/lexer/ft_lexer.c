/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 15:36:11 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tmp_to_lex(t_a *a)
{
	int	size;

	size = ft_strlen(a->tab_space_input[a->i]);
	a->tab_cmd[a->j] = ft_calloc(size + 2, sizeof(char *));
	a->tab_cmd[a->j][0] = ft_strdup(a->str_tmp);
	a->tab_cmd[a->j][1] = NULL;
	free(a->str_tmp);
	a->j++;
}

void	ft_parse_to_lex(t_a *a)
{
	ft_init_for_lexer(a);
	while (a->tab_space_input[a->i])
	{
		a->str_tmp = ft_strdup(a->tab_space_input[a->i]);
		ft_tmp_to_lex(a);
		a->i++;
	}
}

void	ft_define_lexer(t_a *a)
{
	a->i = 0;
	while (a->tab_cmd[a->i])
	{
		ft_detect_lexer(a);
		a->i++;
	}
}
void	ft_add_slash_to_paths(char **paths)
{
	int		i;
	char	*new_path;
	int		len;

	i = 0;
	while (paths[i])
	{
		len = strlen(paths[i]);
		if (paths[i][len - 1] != '/')
		{
			new_path = ft_calloc(len + 2, sizeof(char));
			if (!new_path)
				return ;
			strcpy(new_path, paths[i]);
			new_path[len] = '/';
			new_path[len + 1] = '\0';
			free(paths[i]);
			paths[i] = new_path;
		}
		i++;
	}
	free(new_path);
}

void	ft_find_env_path(t_a *a, t_env **built)
{
	t_env	*ptr;

	ptr = *built;
	while (ptr->next)
	{
		if (ft_strncmp(ptr->env_str, "PATH", 4) == 0)
			a->str_path = ft_strdup(ptr->env_str);
		ptr = ptr->next;
	}
}
int	ft_check_lexer_redirection(t_a *a)
{
	int	i;
	int	redir;

	i = -1;
	redir = 0;
	while (a->tab_cmd[++i])
	{
		if (a->tab_cmd[i][1][0] == '5')
			redir = redir + 1;
		if (a->tab_cmd[i][1][0] == '6')
			redir = redir + 1;
		if (a->tab_cmd[i][1][0] == '#')
			redir = redir + 2;
		if (a->tab_cmd[i][1][0] == '$')
			redir = redir + 2;
		if (a->tab_cmd[i][1][0] == '4')
			redir = redir + 1;
		if (redir >= 3)
			return (1);
		if (a->tab_cmd[i][1][0] == '7' || a->tab_cmd[i][1][0] == '8')
			redir = 0;
		if (a->tab_cmd[i][1][0] == '2' || a->tab_cmd[i][1][0] == '3')
			redir = 0;
	}
	return (0);
}

int	ft_check_lexer_command(t_a *a)
{
	int	size;

	size = ft_strstrstrlen(a->tab_cmd);
	if (size == 1 && a->tab_cmd[0][1][0] == '8')
		return (1);
	if (a->tab_cmd[0][1][0] == '4')
		return (2);
	return (0);
}

void	ft_check_lexer(t_a *a)
{
	if (ft_check_lexer_redirection(a) == 1)
	{
		ft_putstr("syntax error\n");
		a->error = 1;
		return ;
	}
	if (ft_check_lexer_command(a) == 1)
	{
		ft_putstr("zsh: ");
		ft_putstr(a->tab_cmd[0][0]);
		ft_putstr(": command not found\n");
		a->error = 1;
		return ;
	}
	if (ft_check_lexer_command(a) == 2)
	{
		ft_putstr("zsh: parse error near `|'\n");
		a->error = 1;
		return ;
	}
}
void	ft_lexer(t_a *a, t_env **built, char **env)
{
	int		i;
	t_lex	*lex;

	if (a->error == 0)
	{
		// printf("LEXER\n");
		lex = ft_calloc(sizeof(t_lex), 1);
		if (lex == NULL)
			return ;
		i = ft_strstrlen(a->tab_space_input);
		a->tab_cmd = ft_calloc(sizeof(char **), i + 10);
		ft_find_env_path(a, built);
		a->cmd_path = ft_split2(a->str_path, ":");
		ft_add_slash_to_paths(a->cmd_path);
		ft_parse_to_lex(a);
		ft_define_lexer(a);
		ft_check_lexer(a);
		ft_recast_to_lst(a, lex);
		ft_free_parser(a);
		if (a->debug == 1)
			ft_debug_lexer(a);
		if (a->error == 0)
			ft_execute(lex, built, env);
	}
}
