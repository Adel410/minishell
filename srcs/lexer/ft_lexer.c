/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/06 18:24:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// transforme la tmp en stable
void	ft_tmp_to_lex(t_a *a)
{
	int	size;

	size = ft_strlen(a->tab_string_input[a->i]);
	a->tab_cmd[a->j] = ft_calloc(sizeof(char *), size + 1);
	a->tab_cmd[a->j][a->k] = ft_strdup(a->str_tmp);
	a->j++;
}
// transforme la **str en ***str
void	ft_parse_to_lex(t_a *a)
{
	ft_init_for_lexer(a);
	while (a->tab_string_input[a->i])
	{
		a->str_tmp = ft_strdup(a->tab_string_input[a->i]);
		ft_tmp_to_lex(a);
		a->i++;
	}
}
void	ft_detect_lexer(t_a *a)
{
	if(a->tab_cmd[a->i][0][0] == ' ')
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 5);
		a->tab_cmd[a->i][1][0] = '1';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 34)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '2';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 39)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '3';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else
		ft_detect_lexer2(a);
}
void	ft_detect_lexer2(t_a *a)
{
	if(a->tab_cmd[a->i][0][0] == 124)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '4';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 62)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '5';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 60)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '6';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else
		ft_detect_lexer3(a);
	
}

void	ft_detect_lexer3(t_a *a)
{
	int		j;

	j = 0;
	a->str_test = NULL;
	while (a->cmd_path[j])
	{
		a->str_test = ft_strjoin2(a->cmd_path[j], a->tab_cmd[a->i][0]);
		printf(GREEN"%s\n"RESET, a->str_test);
		printf(BLUE"%c == char\n"RESET, a->tab_cmd[a->i][0][0]);
		if (access(a->str_test, X_OK) == 0)
		{
			a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
			a->tab_cmd[a->i][1][0] = '7';
			a->tab_cmd[a->i][1][1] = '\0';
			free(a->str_test);
			return ;
		}
		j++;
		free(a->str_test);
	}
	a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
	a->tab_cmd[a->i][1][0] = '8';
	a->tab_cmd[a->i][1][1] = '\0';
	return ;
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
}

void	ft_find_env_path(t_a *a, t_env **built)
{
	t_env	*ptr;
	
	ptr = *built;
	while (ptr->next)
	{
		if (strncmp(ptr->env_str, "PATH", 4) == 0)
			a->str_path = ft_strdup(ptr->env_str);
		ptr = ptr->next;
	}
}
void	ft_lexer(t_a *a, t_env **built)
{
	int	i;

	i = ft_strstrlen(a->tab_string_input);
	a->tab_cmd = ft_calloc (sizeof (char **), i + 1);
	ft_find_env_path(a,built);
	a->cmd_path = ft_split2(a->str_path, ":");
	ft_add_slash_to_paths(a->cmd_path);
	ft_parse_to_lex(a);
	ft_define_lexer(a);
	ft_debug(a);
}
