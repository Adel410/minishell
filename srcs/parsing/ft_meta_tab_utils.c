/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta_tab_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:30:41 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 12:12:00 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui check si le char est un meta char
int	ft_meta_char(char c)
{
	int	i;

	i = 0;
	if (c == 34)
		return (1);
	if (c == 39)
		return (1);
	while (TOKEN[i])
	{
		if (c == TOKEN[i])
			return (1);
		i++;
	}
	return (0);
}

//fonction qui calcule la taille de meta_tab 
void	ft_meta_tab_size(t_a *a)
{
	int	i;
	int	j;

	i = 0;
	a->meta_size = 0;
	while (a->tab_input[i])
	{
		j = 0;
		while (a->tab_input[i][j])
		{
			if (ft_meta_char(a->tab_input[i][j]) == 1)
				a->meta_size++;
			j++;
		}
		i++;
	}
}


//fonction qui check si la str contient un meta char
int	ft_meta_detect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_meta_char(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
