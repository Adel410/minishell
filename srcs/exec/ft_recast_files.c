/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:27:21 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:27:54 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_file_array(t_exe *new, t_b *b, char c)
{
	if (c == '@' && new->output_file == NULL)
	{
		b->output_index = 0;
		new->output_file = ft_calloc(sizeof(char *), b->output_count + 1);
		if (new->output_file)
			new->output_file[b->output_count] = NULL;
	}
	else if (c == '%' && new->input_file == NULL)
	{
		b->input_index = 0;
		new->input_file = ft_calloc(sizeof(char *), b->input_count + 1);
		if (new->input_file)
			new->input_file[b->input_count] = NULL;
	}
}

void	ft_add_output_file(t_exe *new, t_b *b, char *str)
{
	if (b->output_index < b->output_count)
	{
		new->output_file[b->output_index] = ft_strdup(str);
		if (new->output_file[b->output_index] != NULL)
			b->output_index++;
	}
}

void	ft_add_input_file(t_exe *new, t_b *b, char *str)
{
	if (b->input_index < b->input_count)
	{
		new->input_file[b->input_index] = ft_strdup(str);
		if (new->input_file[b->input_index] != NULL)
			b->input_index++;
	}
}

void	ft_infile_outfile(t_lex *lex, t_exe *new, t_b *b, char c)
{
	if (!lex->str)
		return ;
	ft_init_file_array(new, b, c);
	if (c == '@' && new->output_file)
		ft_add_output_file(new, b, lex->str);
	else if (c == '%' && new->input_file)
		ft_add_input_file(new, b, lex->str);
}
