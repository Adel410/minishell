/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:42:54 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 16:15:38 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui gere les double quotes
void	ft_string_doble_quotes(t_a *a)
{
	ft_string_tmp(a);
	while (a->tab_meta_input[a->i])
	{
		a->h = 0;
		while (a->tab_meta_input[a->i][a->h])
		{
			if (ft_string_char(a->tab_meta_input[a->i][a->h]) == 1)
			{
				a->str_tmp2[a->k] = a->tab_meta_input[a->i][a->h];
				a->k++;
				a->str_tmp2[a->k] = '\0';
				a->tab_string_input[a->j] = ft_strdup(a->str_tmp2);
				a->j++;
				return ;
			}
			else
			{
				a->str_tmp2[a->k] = a->tab_meta_input[a->i][a->h];
				a->k++;
			}
			a->h++;
		}
		a->i++;
	}
	ft_string_end_tmp(a);
}

void	ft_string_simple_quotes(t_a *a)
{
	ft_string_tmp(a);
	while (a->tab_meta_input[a->i])
	{
		a->h = 0;
		while (a->tab_meta_input[a->i][a->h])
		{
			if (ft_string_char(a->tab_meta_input[a->i][a->h]) == 2)
			{
				a->str_tmp2[a->k] = a->tab_meta_input[a->i][a->h];
				a->k++;
				a->str_tmp2[a->k] = '\0';
				a->tab_string_input[a->j] = ft_strdup(a->str_tmp2);
				a->j++;
				return ;
			}
			else
			{
				a->str_tmp2[a->k] = a->tab_meta_input[a->i][a->h];
				a->k++;
			}
			a->h++;
		}
		a->i++;
	}
	ft_string_end_tmp(a);
}

void	ft_string_new_tab(t_a *a)
{
	a->i = 0;
	a->j = 0;
	a->k = 0;
	a->h = 0;
	while (a->tab_meta_input[a->i])
	{
		if (ft_string_detect(a->tab_meta_input[a->i]) == 0)
		{
			a->tab_string_input[a->j] = ft_strdup(a->tab_meta_input[a->i]);
			a->j++;
		}
		if (ft_string_detect(a->tab_meta_input[a->i]) == 1)
		{
			printf(FLASH "\nENTRY\n" RESET);
			ft_string_doble_quotes(a);
		}
		if (ft_string_detect(a->tab_meta_input[a->i]) == 2)
			ft_string_simple_quotes(a);
		a->i++;
	}
}
