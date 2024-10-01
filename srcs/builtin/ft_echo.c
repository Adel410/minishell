/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:44:46 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/01 14:29:02 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (2);
	return (nb * sign);
}

void	ft_echo_without_n(t_exe *current)
{
	int	i;

	i = 1;
	while (current->cmds[i])
	{
		ft_putstr(current->cmds[i]);
		i++;
	}
	ft_putstr("\n");
}

void	ft_echo(t_exe *current, t_env *built)
{
	int	i;

	i = 2;
	if (current->cmds[1] && ft_strcmp(current->cmds[1], "-n") == 0)
	{
		while (current->cmds[i])
		{
			ft_putstr(current->cmds[i]);
			i++;
		}
	}
	else
		ft_echo_without_n(current);
	built->exit_code = 0;
}
