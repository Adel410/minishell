/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:13:47 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/02 14:02:53 by nicjousl         ###   ########.fr       */
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
	while (a->tab_option_input[++a->i])
	{
		if (ft_meta_detect(a->tab_option_input[a->i]) == 0)
		{
			a->tab_meta_input[a->j] = ft_strdup(a->tab_option_input[a->i]);
			a->j++;
		}
		else if (ft_meta_detect(a->tab_option_input[a->i]) == 1)
			ft_meta_new_tab2(a);
	}
}

//fonction qui regarde char par char la string
void	ft_meta_new_tab2(t_a *a)
{
	a->k = 0;
	while (a->tab_option_input[a->i][a->k])
	{
		a->size = 0;
		if (ft_meta_char(a->tab_option_input[a->i][a->k]) == 0)
			ft_meta_new_tab4(a);
		else if (ft_meta_char(a->tab_option_input[a->i][a->k]) == 1)
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
				a->tab_option_input[a->i][a->k]);
		a->j++;
		a->meta_tab_size--;
	}
}

//fonction qui creer un tab sans le meta char
void	ft_meta_new_tab4(t_a *a)
{
	a->start = a->k;
	while (ft_meta_char(a->tab_option_input[a->i][a->k]) == 0)
	{
		a->size++;
		a->k++;
		if (a->k >= ft_strlen(a->tab_option_input[a->i]))
			break ;
	}
	if (a->meta_tab_size >= 0)
	{
		a->tab_meta_input[a->j] = ft_master_strndup(
				a->tab_option_input[a->i], a->start, a->size);
		a->j++;
		a->k--;
	}
}
