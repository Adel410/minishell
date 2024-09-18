/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nice_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:41:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 14:30:02 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//fonction relai qui parse les meta chars
void	ft_meta_tab(t_a *a)
{
	ft_meta_tab_size(a);
	ft_init_for_meta_tab(a);
	a->option_size = ft_strstrlen(a->tab_input);
	a->meta_tab_size = a->option_size + a->meta_size;
	a->tab_meta_input = ft_calloc(sizeof (char *), a->meta_tab_size + 1);
	ft_meta_new_tab(a);
	ft_double_redir(a);
}

//fonction relai qui parse les strings
void	ft_string_tab(t_a *a)
{
	a->string_tab_size = ft_strstrlen(a->tab_meta_new_input);
	a->tab_string_input = ft_calloc(sizeof (char *), a->string_tab_size + 1);
	ft_string_new_tab(a);
}

//fonction relai qui nous creer notre tab***
void	ft_nice_tab(t_a *a)
{
	ft_meta_tab(a);
	ft_string_tab(a);
	if (a->error == 0)
		ft_space_tab(a);
	if (a->debug == 1)
		ft_debug_parser(a);
	
}
