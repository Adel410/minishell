/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:38:04 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/30 13:53:58 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(int i)
{
	if (i == 0)
	{
		ft_color("!! Don't put arg !!\n", 3, BIG, RED, FLASH);
		exit(0);
	}
	if (i == 1)
		printf("command not found\n");
	if (i == 2)
		printf("quotes problems !\n");
	if (i == 3)
	{
		printf(BIG RED "TA PAS L IMPRESSION D ABUSER ?\n");
		printf("RAMENE TON MINISHELL JE VAIS FAIRE PAREIL\n" RESET);
	}
}

void	ft_put_error(char *str, int exit_code)
{
	if (exit_code == 126)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (exit_code == 127)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (exit_code == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		exit(127);
	}
	else if (exit_code == 2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	exit(exit_code);
}

void	ft_put_error2(char *str, int exit_code)
{
	if (exit_code == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	exit (exit_code);
}
