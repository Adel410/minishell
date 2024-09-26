/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:44:46 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/24 14:28:52 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_exe *current)
{
	int	i;

	i = 0;
	if (current->cmds[1] && ft_strcmp(current->cmds[1], "-n") == 0)
	{
		if (!current->string)
			return ;
		ft_putstr(current->string);
		ft_putstr(" ");
	}
	else
	{
		if (current->string)
		{
			ft_putstr(current->string);
			ft_putstr(" ");
		}
		while (current->cmds[++i])
		{
			ft_putstr(current->cmds[i]);
			ft_putstr(" ");
		}
		ft_putstr("\n");
	}
}
