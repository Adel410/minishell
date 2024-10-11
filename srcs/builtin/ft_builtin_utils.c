/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:09 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 14:19:24 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export_alphabetic_order(t_env *built)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (built->env[i])
	{
		j = i + 1;
		while (built->env[j])
		{
			if (ft_strcmp(built->env[i], built->env[j]) > 0)
			{
				tmp = built->env[i];
				built->env[i] = built->env[j];
				built->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_env(t_env *head)
{
	int	i;

	i = 0;
	while (head->env[i])
	{
		if (head->env[i][0] == '_' && head->env[i][1] == '=')
		{
			ft_putstr("_=/usr/bin/export\n");
			break ;
		}
		ft_putstr(head->env[i]);
		ft_putstr("\n");
		i++;
	}
}

void	ft_free_env(t_env *built)
{
	int	i;

	i = 0;
	while (built->env[i])
	{
		free(built->env[i]);
		i++;
	}
	if (!built->input)
		free(built->input);
	free(built->env);
	free(built);
}

int	ft_check_export(char *str, t_env *built)
{
	if (built->flag == 0)
	{
		if (ft_correct_name_export(str, built) == 0)
			return (0);
	}
	return (1);
}

void	ft_update_oldpwd(t_env *built, char *path)
{
	int	i;

	if (built->env)
	{
		i = 0;
		if (path)
		{
			while (built->env[i])
			{
				if (ft_strncmp("OLDPWD", built->env[i], 6) == 0)
				{
					free(built->env[i]);
					built->env[i] = ft_strjoin2("OLDPWD=", path);
					return ;
				}
				i++;
			}
		}
	}
}
