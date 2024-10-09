/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:58 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/08 16:21:02 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CD
void	ft_cd(t_exe *current, t_env *built)
{
	char	*path;

	path = NULL;
	if (current->cmds[1] && current->cmds[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		built->exit_code = 1;
		return ;
	}
	else if (current->cmds[1] == NULL)
		path = ft_strdup("/home/ahadj-ar");
	else
		path = ft_strdup(current->cmds[1]);
	if (chdir(path) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : no such file or directory\n", 2);
		free(path);
		built->exit_code = 1;
		return ;
	}
	free(path);
}
