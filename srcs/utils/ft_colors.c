/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:56:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/08/30 13:46:19 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_color(char *str, int n, ...)
{
	va_list		args;
	int			i;
	char		**arg;

	arg = malloc(n * sizeof(char *));
	if (!arg)
		return ;
	i = 0;
	va_start(args, n);
	while (i < n)
	{
		arg[i] = va_arg(args, char *);
		i++;
	}
	i = 0;
	while (i < n)
	{
		ft_putstr2(arg[i]);
		i++;
	}
	ft_putstr2(str);
	write (1, RESET, 5);
	va_end(args);
	free(arg);
}
