/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:35:02 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 14:43:54 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_correct_name_export(char *str, t_env *built)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			built->flag = 1;
			return (1);
		}
		else if (ft_is_alpha_num(str[i]) == 0)
		{
			write(1, &str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			built->exit_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_copy_env_for_export(t_env *built, char **new_env)
{
	int	i;

	i = ft_strstrlen(new_env);
	built->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (new_env[i])
	{
		built->env[i] = ft_strdup(new_env[i]);
		i++;
	}
	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
}

void	ft_export(t_env *built, char *str)
{
	char	**new_env;
	int		i;

	i = ft_strstrlen(built->env);
	if (ft_check_export(str, built) == 1)
	{
		new_env = ft_calloc(i + 2, sizeof(char *));
		i = 0;
		while (built->env[i])
		{
			if (ft_strncmpchar(built->env[i], str, '=') == 0)
			{
				free(built->env[i]);
				built->env[i] = ft_strdup(str);
				ft_free_tab(new_env);
				return ;
			}
			new_env[i] = ft_strdup(built->env[i]);
			i++;
		}
		new_env[i] = ft_strdup(str);
		ft_free_tab(built->env);
		ft_copy_env_for_export(built, new_env);
	}
	return ;
}

void	ft_set_export(t_env *built, t_exe *current)
{
	int		i;
	char	*tmp_cmd;

	i = 1;
	while (current->cmds[i])
	{
		if (current->cmds[i][ft_strlen(current->cmds[i]) - 2] == '='
			&& current->cmds[i][ft_strlen(current->cmds[i]) - 1] == ' '
			&& current->cmds[i + 1])
		{
			ft_putstr("CASSE TOI DE LA\n");
			return ;
		}
		else if (current->cmds[i][ft_strlen(current->cmds[i]) - 1] == '='
			&& current->cmds[i + 1])
		{
			tmp_cmd = ft_strjoin2(current->cmds[i], current->cmds[i + 1]);
			i++;
		}
		else
			tmp_cmd = ft_strdup(current->cmds[i]);
		ft_export(built, tmp_cmd);
		free(tmp_cmd);
		i++;
	}
}

void	ft_call_export(t_env *built, t_exe *current)
{
	if (current->cmds[1] == NULL)
	{
		ft_export_alphabetic_order(built);
		ft_print_env(built);
		return ;
	}
	built->flag = 0;
	ft_set_export(built, current);
}
