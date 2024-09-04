/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:38:04 by nicjousl          #+#    #+#             */
/*   Updated: 2024/08/30 17:55:49 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(int i, t_a *a)
{
	if (i == 0)
	{
		ft_color("!! Don't put arg !!\n", 3, BIG, RED, FLASH);
		exit(0);
	}
	if (i == 1)
	{
		printf("command not found\n");
		ft_free(a);
	}
	if (i == 2)
	{
		printf("quotes problems !\n");
		ft_free(a);
	}
}
