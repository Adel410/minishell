/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nice_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:41:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 10:04:15 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction relai qui parse les options
void	ft_option_tab(t_a *a)
{
	ft_option_join_tab(a);
	ft_option_cut_tab(a);
	ft_option_new_tab(a);
}

//fonction relai qui parse les meta chars
void	ft_meta_tab(t_a *a)
{
	ft_meta_tab_size(a);
	ft_init_for_meta_tab(a);
	a->option_size = ft_strstrlen(a->tab_option_input);
	a->meta_tab_size = a->option_size + a->meta_size;
	a->tab_meta_input = ft_calloc(sizeof (char *), 10000);
	ft_meta_new_tab(a);
}
//fonction relai qui parse les strings
void	ft_string_tab(t_a *a)
{
	a->tab_string_input = ft_calloc(sizeof (char *), 10000);
	ft_string_new_tab(a);
}
//fonction relai qui nous creer notre tab***
void	ft_nice_tab(t_a *a)
{
	ft_option_tab(a);
	ft_meta_tab(a);
	ft_string_tab(a);
}
