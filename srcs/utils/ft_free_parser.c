/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:18:33 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 12:19:09 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_parser(t_a *a)
{
	int	i;

	i = 0;
	if (a->tab_input != NULL)
	{
		while (a->tab_input[i])
		{
			free(a->tab_input[i]);
			i++;
		}
		free (a->tab_input);
	}
	i = 0;
	if (a->tab_meta_input != NULL)
	{
		while (a->tab_meta_input[i])
		{
			free(a->tab_meta_input[i]);
			i++;
		}
		free (a->tab_meta_input);
	}
	ft_free_parser2(a);
}

void	ft_free_parser2(t_a *a)
{
	int i;


	i = 0;
	if (a->tab_meta_new_input != NULL)
	{
		while (a->tab_meta_new_input[i])
		{
			free(a->tab_meta_new_input[i]);
			i++;
		}
		free (a->tab_meta_new_input);
	}
	i = 0;
	if (a->tab_space_input != NULL)
	{
		while (a->tab_space_input[i])
		{
			free(a->tab_space_input[i]);
			i++;
		}
		free (a->tab_space_input);
	}
	ft_free_parser3(a);
}

void	ft_free_parser3(t_a *a)
{
	int i;


	i = 0;
	if (a->tab_string_input != NULL)
	{
		while (a->tab_string_input[i])
		{
			free(a->tab_string_input[i]);
			i++;
		}
		free (a->tab_string_input);
	}
	if (a->str_tmp2 != NULL)
		free(a->str_tmp2);
	if (a->input != NULL)
		free(a->input);
}