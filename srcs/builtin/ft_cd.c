/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:58 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 13:21:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_find_home(t_env *built)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (built->env[i])
	{
		if (ft_strncmp("USER", built->env[i], 4) == 0)
		{
			tmp2 = ft_master_strndup(built->env[i], 5, ft_strlen(built->env[i])
					- 5);
			tmp = ft_strjoin2("/home/", tmp2);
			if (!tmp)
			{
				free(tmp2);
				return (NULL);
			}
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void	ft_cd_home(t_env *built)
{
	char	*path;

	path = ft_find_home(built);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		built->exit_code = 1;
		return ;
	}
	if (chdir(path) == -1)
		perror("minishell: cd");
	free(path);
}

void	ft_cd_to_path(t_exe *current, t_env *built)
{
	char	*current_dir;
	char	*path;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		perror("minishell: cd");
	else
		free(current_dir);
	path = ft_strdup(current->cmds[1]);
	if (access(path, X_OK) == 0)
	{
		if (chdir(path) == -1)
			perror("minishell: cd");
		else
			built->exit_code = 0;
	}
	free(path);
}

void	ft_cd(t_exe *current, t_env *built)
{
	if (current->cmds[1] && current->cmds[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		built->exit_code = 1;
		return ;
	}
	if (current->cmds[1] == NULL || (current->cmds[1][0] == '~'
		&& current->cmds[1][1] == '\0'))
		ft_cd_home(built);
	else
		ft_cd_to_path(current, built);
}
