/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:09 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 18:25:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf(BIG "%s\n" RESET, tab[i]);
		i++;
	}
}

void	ft_export_alphabetic_order(t_env *built)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (built->env[i])
	{
		j = i + 1;
		while (built->env[j])
		{
			if (ft_strcmp(built->env[i], built->env[j]) > 0)
			{
				tmp = built->env[i];
				built->env[i] = built->env[j];
				built->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_env(t_env *head)
{
	int	i;

	i = 0;
	while (head->env[i])
	{
		if (head->env[i][0] == '_' && head->env[i][1] == '=')
		{
			ft_putstr("_=/usr/bin/export\n");
			break;
		}
		ft_putstr(head->env[i]);
		ft_putstr("\n");
		i++;
	}
}

void	ft_free_env(t_env *built)
{
	int	i;

	i = 0;
	while (built->env[i])
	{
		free(built->env[i]);
		i++;
	}
	free(built->env);
	free(built);
}
