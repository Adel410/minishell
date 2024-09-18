/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detect_lexer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:19:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 16:10:11 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_detect_lexer4(t_a *a)
{
	if (ft_strncmp(a->tab_cmd[a->i][0], "export", 6) == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if (ft_strncmp(a->tab_cmd[a->i][0], "echo", 4) == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if (ft_strncmp(a->tab_cmd[a->i][0], "cd", 2) == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else
		ft_detect_lexer5(a);
}

void	ft_detect_lexer5(t_a *a)
{
	if (ft_strncmp(a->tab_cmd[a->i][0], "..", 2) == 0 && *(a->tab_cmd[a->i][0] + 2) == '\0')
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if (ft_strncmp(a->tab_cmd[a->i][0], "exit", 4) == 0 && *(a->tab_cmd[a->i][0] + 4) == '\0')
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else
		ft_detect_lexer6(a);
}
void	ft_detect_lexer6(t_a *a)
{
	int		j;

	j = 0;
	while (a->cmd_path[j])
	{
		a->str_test = ft_strjoin2(a->cmd_path[j], a->tab_cmd[a->i][0]);
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