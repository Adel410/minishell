/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:13:47 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 10:11:57 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui creer le meta tab
void	ft_meta_new_tab(t_a *a)
{
	int	size;
	int	start;

	size = 0;
	start = 0;
	while (a->tab_input[++a->i])
	{
		if (ft_meta_detect(a->tab_input[a->i]) == 0)
		{
			a->tab_meta_input[a->j] = ft_strdup(a->tab_input[a->i]);
			a->j++;
		}
		else if (ft_meta_detect(a->tab_input[a->i]) == 1)
			ft_meta_new_tab2(a);
	}
}

//fonction qui regarde char par char la string
void	ft_meta_new_tab2(t_a *a)
{
	a->k = 0;
	while (a->tab_input[a->i][a->k])
	{
		a->size = 0;
		if (ft_meta_char(a->tab_input[a->i][a->k]) == 0)
			ft_meta_new_tab4(a);
		else if (ft_meta_char(a->tab_input[a->i][a->k]) == 1)
			ft_meta_new_tab3(a);
		a->k++;
	}
}

//fonction qui creer un tab pour le meta char
void	ft_meta_new_tab3(t_a *a)
{
	if (a->meta_tab_size >= 0)
	{
		a->tab_meta_input[a->j] = ft_malloc_copy_char(
				a->tab_input[a->i][a->k]);
		a->j++;
		a->meta_tab_size--;
	}
}

//fonction qui creer un tab sans le meta char
void	ft_meta_new_tab4(t_a *a)
{
	a->start = a->k;
	while (ft_meta_char(a->tab_input[a->i][a->k]) == 0)
	{
		a->size++;
		a->k++;
		if (a->k >= ft_strlen(a->tab_input[a->i]))
			break ;
	}
	if (a->meta_tab_size >= 0)
	{
		a->tab_meta_input[a->j] = ft_master_strndup(
				a->tab_input[a->i], a->start, a->size);
		a->j++;
		a->k--;
	}
}


void	ft_double_redir(t_a *a)
{
	int	size;
	a->i = 0;
	a->j = 0;

	size = ft_strstrlen(a->tab_meta_input);
	a->tab_meta_new_input = ft_calloc(sizeof(char *), size + 1);
	if (!a->tab_meta_new_input)
		return ;
	while (a->tab_meta_input[a->i])
	{
		if (a->tab_meta_input[a->i + 1] != NULL)
		{
			if (a->tab_meta_input[a->i][0] == '>' && a->tab_meta_input[a->i
				+ 1][0] == '>')
			{
				a->tab_meta_new_input[a->j] = malloc(sizeof(char) * 3);
				if (!a->tab_meta_new_input[a->j])
					return ;
				a->tab_meta_new_input[a->j][0] = '>';
				a->tab_meta_new_input[a->j][1] = '>';
				a->tab_meta_new_input[a->j][2] = '\0';
				a->j++;
				a->i += 2;
				continue ;
			}
			if (a->tab_meta_input[a->i][0] == '<' && a->tab_meta_input[a->i
				+ 1][0] == '<')
			{
				a->tab_meta_new_input[a->j] = malloc(sizeof(char) * 3);
				if (!a->tab_meta_new_input[a->j])
					return ;
				a->tab_meta_new_input[a->j][0] = '<';
				a->tab_meta_new_input[a->j][1] = '<';
				a->tab_meta_new_input[a->j][2] = '\0';
				a->j++;
				a->i += 2;
				continue ;
			}
		}
		a->tab_meta_new_input[a->j] = ft_strdup(a->tab_meta_input[a->i]);
		if (!a->tab_meta_new_input[a->j])
			return ;
		a->j++;
		a->i++;
	}
	a->tab_meta_new_input[a->j] = NULL;
}
