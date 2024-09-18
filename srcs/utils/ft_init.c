/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:17:01 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 14:54:40 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_prompt(t_a *a)
{
	a->error = 0;
	a->meta_copy = 0;
	a->option_index = 0;
	a->meta_index = 0;
	a->option_size = 0;
	a->meta_size = 0;
	a->token_count = 0;
	a->cmd_tab_size = 0;
	a->cmd_size = 0;
	a->tab_cmd = NULL;
	a->cmd_path = NULL;
	a->str_tmp = NULL;
	a->str_tmp2 = NULL;
	a->tab_input = NULL;
	a->tab_meta_input = NULL;
	a->tab_meta_new_input = NULL;
	a->tab_space_input = NULL;
	a->tab_string_input = NULL;
}

void	ft_init_for_meta_tab(t_a *a)
{	
	a->i = -1;
	a->j = 0;
	a->start = 0;
	a->size = 0;
}

void	ft_init_for_option_tab(t_a *a)
{
	a->j = 0;
	a->u = 0;
	a->t = 0;
	a->v = 1;
	a->k = 0;
}
void	ft_init_for_lexer(t_a *a)
{
	a->i = 0;
	a->j = 0;
	a->k = 0;
}
void	ft_init_for_check_close_quotes(t_a *a)
{
	a->i = 0;
	a->j = 0;
	a->flag = 0;
	a->detect = 0;
}
void	ft_init_for_string_tab(t_a *a)
{
	a->i = 0;
	a->j = 0;
	a->k = 0;
	a->h = 0;
}