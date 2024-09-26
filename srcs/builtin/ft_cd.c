/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:58 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/24 15:25:13 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CD
void	ft_cd(t_exe *current)
{
	char	*path;

	if (current->cmds[1] == NULL)
		path = ft_strdup("/home");
	else
		path = ft_strdup(current->cmds[1]);
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
}
