/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:18:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/09 17:57:37 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_copy_env_for_unset(t_env *built, char **new_env)
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
	built->exit_code = 0;
	ft_free_tab(new_env);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_env *built, char *str)
{
	char	**new_env;
	int		i;
	int		j;

	if (!is_valid_identifier(str))
	{
		ft_putstr_fd("unset: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		built->exit_code = 1;
		return ;
	}
	new_env = ft_calloc(ft_strstrlen(built->env) + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (built->env[i])
	{
		if (ft_strncmp(built->env[i], str, ft_strlen(str)) != 0
			|| built->env[i][ft_strlen(str)] != '=')
			new_env[j++] = ft_strdup(built->env[i]);
		i++;
	}
	ft_free_tab(built->env);
	ft_copy_env_for_unset(built, new_env);
}

void	ft_call_unset(t_env *built, t_exe *current)
{
	int	i;

	i = 1;
	while (current->cmds[i])
	{
		ft_unset(built, current->cmds[i]);
		i++;
	}
}
