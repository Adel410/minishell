/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:35:02 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 17:33:00 by ahadj-ar         ###   ########.fr       */
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


int	ft_check_export(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] && str[i + 1] != '\0')
				flag = 2;
			else
				flag = 1;
		}
		i++;
	}
	return (flag);
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
	built->env[i] = NULL;
	ft_free_tab(new_env);
}

void	ft_export(t_env *built, char *str)
{
	char	**new_env;
	int		end;
	int	i;	

	i = ft_strstrlen(built->env);
	if (ft_check_export(str) != 0)
	{
		new_env = ft_calloc(i + 2, sizeof(char *));
		i = 0;
		while (built->env[i])
		{
			if (ft_strncmpchar(built->env[i], str, '=') == 0)
			{
				free(built->env[i]);
				built->env[i] = ft_strdup(str);
				return ;
			}
			new_env[i] = ft_strdup(built->env[i]);
			i++;
		}
		new_env[i] = ft_strdup(str);
		ft_free_tab(built->env);
		ft_copy_env_for_export(built, new_env);
		end = ft_find_end_def(str);
	}
	return ;
}

void	ft_call_export(t_env *built, t_exe *current)
{
	int	i;

	i = 1;
	(void)built;
	if (current->cmds[1] == NULL)
	{
		ft_export_alphabetic_order(built);
		ft_print_env(built);
		return ;
	}
	while (current->cmds[i])
	{
		ft_export(built, current->cmds[i]);
		i++;
	}
}
