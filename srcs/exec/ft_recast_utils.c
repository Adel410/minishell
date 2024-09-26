/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:04 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/23 17:00:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_if_null(t_exe *current)
{
	if (current->input_file != NULL)
		return (1);
	else if (current->output_file != NULL)
		return (2);
	else if (current->cmds != NULL)
		return (3);
	else if (current->cmds[0] != NULL)
		return (4);
	else if (current->limiter != NULL)
		return (5);
	else if (current->string != NULL)
		return (6);
	else
		return (0);
}

int	ft_check_if_already(t_exe *current, char *str)
{
	if (current->input_file && ft_strcmp(current->input_file, str) == 0)
		return (1);
	else if (current->output_file && ft_strcmp(current->output_file, str) == 0)
		return (2);
	else if (current->cmds && current->cmds[0] && ft_strcmp(current->cmds[0],
			str) == 0)
		return (3);
	else if (current->cmds && current->cmds[1] && ft_strcmp(current->cmds[1],
			str) == 0)
		return (4);
	else if (current->limiter && ft_strcmp(current->limiter, str) == 0)
		return (5);
	else if (current->string && ft_strcmp(current->string, str) == 0)
		return (6);
	else
		return (0);
}
