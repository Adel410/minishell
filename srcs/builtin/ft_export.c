/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:35:02 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/02 19:33:42 by ahadj-ar         ###   ########.fr       */
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

// int	ft_correct_def_export(char *str, t_env *built)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 		{
// 			built->flag = 1;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	built->exit_code = 0;
// 	return (0);
// }

int	ft_check_export(char *str, t_env *built)
{
	if (built->flag == 0)
	{
		if (ft_correct_name_export(str, built) == 0)
			return (0);
	}
	// else if (built->flag == 1)
	// {
	// 	if (ft_correct_def_export(str, built) == 0)
	// 		return (0);
	// }
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
	built->env[i] = NULL;
	ft_free_tab(new_env);
}

void	ft_export(t_env *built, char *str)
{
	char	**new_env;
	int		i;

	// int		end;
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
				return ;
			}
			new_env[i] = ft_strdup(built->env[i]);
			i++;
		}
		new_env[i] = ft_strdup(str);
		ft_free_tab(built->env);
		ft_copy_env_for_export(built, new_env);
		// end = ft_find_end_def(str);
	}
	return ;
}

void	ft_call_export(t_env *built, t_exe *current)
{
	int	i;

	i = 1;
	built->flag = 0;
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
