/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detect_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:16:43 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/13 18:48:05 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if(a->tab_cmd[a->i][0][0] == 62 && a->tab_cmd[a->i][0][1] == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '5';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 62 && a->tab_cmd[a->i][0][1] == 62) 
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '#';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 60 && a->tab_cmd[a->i][0][1] == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '6';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if(a->tab_cmd[a->i][0][0] == 60 && a->tab_cmd[a->i][0][1] == 60) 
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '$';
		a->tab_cmd[a->i][1][1] = '\0';

	}
	else
		ft_detect_lexer3(a);
	
}

void	ft_detect_lexer3(t_a *a)
{
	if (ft_strncmp(a->tab_cmd[a->i][0], "pwd", 3) == 0 && *( a->tab_cmd[a->i][0] + 3) == '\0')
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if (ft_strncmp(a->tab_cmd[a->i][0], "env", 3) == 0 && *(a->tab_cmd[a->i][0]+ 3) == '\0')
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else if (ft_strncmp(a->tab_cmd[a->i][0], "unset", 5) == 0)
	{
		a->tab_cmd[a->i][1] = ft_calloc(sizeof(char), 2);
		a->tab_cmd[a->i][1][0] = '9';
		a->tab_cmd[a->i][1][1] = '\0';
	}
	else
		ft_detect_lexer4(a);
}