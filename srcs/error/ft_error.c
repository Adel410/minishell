/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:38:04 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/23 12:14:07 by ahadj-ar         ###   ########.fr       */
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
	{
		printf("command not found\n");
	}
	if (i == 2)
	{
		printf("quotes problems !\n");
	}
	if (i == 3)
	{
		printf(BIG RED"TA PAS L IMPRESSION D ABUSER ?\n");
		printf("RAMENE TON MINISHELL JE VAIS FAIRE PAREIL\n"RESET);
	}
}
