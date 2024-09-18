/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:41:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 15:31:20 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_a *a)
{
	int	i;

	i = 0;
	if (a->str_tmp != NULL)
		free(a->str_tmp);
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
	if (a->tab_option_input != NULL)
	{
		while (a->tab_option_input[i])
		{
			free(a->tab_option_input[i]);
			i++;
		}
		free (a->tab_option_input);
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
	free(a->input);
}

void	ft_free_lexer(t_a *a)
{
	int	i;
	int	j;

	i = 0;
	while (a->tab_cmd[i] != NULL)
	{
		j = 0;
		while (a->tab_cmd[i][j])
		{
			free(a->tab_cmd[i][j]);
			j++;
		}
		free(a->tab_cmd[i]);
		i++;
	}
	free(a->tab_cmd);
	free(a->str_path);
}

void	ft_cleanup(t_a *a)
{
	ft_free(a);
	exit(0);
}
