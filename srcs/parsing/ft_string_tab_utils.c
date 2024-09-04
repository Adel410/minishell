/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_tab_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:11:37 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 16:12:28 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui detecte la quote ou doble quote
int	ft_string_char(char c)
{
	if (c == 34)
		return (1);
	if (c == 39)
		return (2);
	else
		return (0);
}

// fonction qui detect une quotes dans une string
int	ft_string_detect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_string_char(str[i]) == 1)
			return (1);
		if (ft_string_char(str[i]) == 2)
			return (2);
		i++;
	}
	return (0);
}

//fonction qui termine la tmp
void	ft_string_end_tmp(t_a *a)
{
	a->str_tmp2[a->k] = '\0';
	a->tab_string_input[a->j] = ft_strdup(a->str_tmp2);
	free(a->str_tmp2);
	a->j++;
}

//fonction qui creer la tmp
void	ft_string_tmp(t_a *a)
{
	a->k = 0;
	a->str_tmp2 = ft_calloc(sizeof(char), 10000);
	a->str_tmp2[a->k] = a->tab_meta_input[a->i][0];
	a->k++;
	a->i++;
}
