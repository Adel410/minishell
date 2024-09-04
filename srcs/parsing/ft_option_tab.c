/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:50 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 14:15:03 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui calcule la taille que fera option tab
int	ft_option_tab_size(t_a *a)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (a->tab_input[i])
	{
		if (a->tab_input[i][0] == '\0')
			c++;
		i++;
	}
	return (c);
}
// fonction qui creer option tab a partir de notre input tab

void	ft_option_new_tab(t_a *a)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = ft_strstrlen(a->tab_input);
	a->option_size = ft_option_tab_size(a);
	a->tab_option_input = calloc(sizeof (char *), size - a->option_size + 1);
	j = 0;
	while (a->tab_input[i])
	{
		if (a->tab_input[i][0] == '\0' && a->tab_input[i])
			i++;
		if (a->tab_input[i] == NULL)
			break ;
		a->tab_option_input[j] = ft_strdup(a->tab_input[i]);
		printf("%d = value of j\n", i);
		i++;
		j++;
	}
	i = ft_strstrlen(a->tab_option_input);
	a->tab_option_input[i] = NULL;
}
//fonction qui supprime le tab ou precedement il y avait l option

void	ft_option_cut_tab(t_a *a)
{
	a->tab_option_input = malloc(1024);
	a->i = 0;
	while (a->tab_input[a->i + 1])
	{
		ft_init_for_option_tab(a);
		a->tab_option_input[a->t] = malloc(1024);
		while (a->tab_input[a->i][a->j])
		{
			if ((a->tab_input[a->i][a->j] == '-') && (a->tab_input[a->i
					+ 1][0] == '-'))
			{
				a->tab_input[a->i + 1][0] = '\0';
				a->v = ft_strlen(a->tab_input[a->i]);
				a->tab_input[a->i][a->v + 2] = '-';
			}
			a->j++;
			a->b++;
		}
		a->t++;
		a->i++;
	}
}
//fonction qui joint les options a la commande

void	ft_option_join_tab(t_a *a)
{
	int	i;

	i = 0;
	if (!a->tab_input)
		return ;
	while (a->tab_input[i])
	{
		if (a->tab_input[i][1] == '-')
			a->tab_input[i - 1] = ft_strjoin(a->tab_input[i - 1],
					a->tab_input[i]);
		i++;
	}
}
