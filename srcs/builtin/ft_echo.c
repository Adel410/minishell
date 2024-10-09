/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:44:46 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/08 16:40:03 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo_without_n(t_exe *current)
{
	int	i;

	i = 1;
	while (current->cmds[i])
	{
		ft_putstr(current->cmds[i]);
		if (current->cmds[i + 1])
			ft_putstr(" ");
		i++;
	}
	ft_putstr("\n");
}

int	ft_echo_option(char *str)
{
	int	i;
	int	size;

	i = 1;
	size = ft_strlen(str);
	while (str[i] == 'n')
		i++;
	if (i != size)
		return (1);
	return (0);
}

void	ft_echo(t_exe *current, t_env *built)
{
	int	i;

	i = 2;
	if (current->cmds[1] && ft_strncmp(current->cmds[1], "-n", 2) == 0
		&& ft_echo_option(current->cmds[1]) == 0)
	{
		while (current->cmds[i])
		{
			ft_putstr(current->cmds[i]);
			if (current->cmds[i + 1] != NULL)
				ft_putstr(" ");
			i++;
		}
	}
	else
		ft_echo_without_n(current);
	built->exit_code = 0;
}
