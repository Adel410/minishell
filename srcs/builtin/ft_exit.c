/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:09 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/25 15:33:53 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_exit(t_exe *exec, t_env *built)
{
	ft_free_exec(exec);
	ft_free_env(built);
	exit(0);
}
