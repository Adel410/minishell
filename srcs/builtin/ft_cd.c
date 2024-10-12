/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:58 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/12 17:33:09 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_pwd(t_env *built)
{
	char	*current_pwd;
	int		i;

	if (built->env)
	{
		current_pwd = getcwd(NULL, 0);
		if (current_pwd == NULL)
			return ;
		else
		{
			i = 0;
			while (built->env[i])
			{
				if (ft_strncmp("PWD", built->env[i], 3) == 0)
				{
					free(built->env[i]);
					built->env[i] = ft_strjoin2("PWD=", current_pwd);
					free(current_pwd);
					return ;
				}
				i++;
			}
		}
		free(current_pwd);
	}
}

char	*ft_find_home(t_env *built)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (built->env[i])
	{
		while (built->env[i])
		{
			if (ft_strncmp("USER", built->env[i], 4) == 0)
			{
				tmp2 = ft_master_strndup(built->env[i], 5,
						ft_strlen(built->env[i]) - 5);
				tmp = ft_strjoin2("/home/", tmp2);
				free(tmp2);
				if (!tmp)
					return (NULL);
				return (tmp);
			}
			i++;
		}
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
	else
		ft_update_pwd(built);
	free(path);
}

void	ft_cd_to_path(t_exe *current, t_env *built)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		perror("minishell: cd");
	else
	{
		ft_update_oldpwd(built, current_dir);
		free(current_dir);
	}
	if (access(current->cmds[1], F_OK) == 0)
	{
		if (chdir(current->cmds[1]) == -1)
		{
			perror("minishell: cd");
			built->exit_code = 1;
		}
		else
			ft_update_pwd(built);
	}
	else
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		built->exit_code = 1;
	}
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
