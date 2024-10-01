/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:18:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:20 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_find_str_to_unset(char *str)
{
	char	*to_del;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	to_del = ft_master_strndup(str, 0, i);
	return (to_del);
}

char	*ft_add_equal(char *str)
{
	char	*to_del;
	int		i;
	int		size;

	size = ft_strlen(str);
	to_del = malloc(sizeof(char) * size + 2);
	i = 0;
	while (str[i])
	{
		to_del[i] = str[i];
		i++;
	}
	to_del[i] = '=';
	to_del[i + 1] = '\0';
	free(str);
	return (to_del);
}

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

void	ft_unset(t_env *built, char *str)
{
	char	**new_env;
	int		i;
	int		j;

	i = ft_strstrlen(built->env);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (built->env[i])
	{
		if (ft_strncmp(built->env[i], str, ft_strlen(str)) != 0)
		{
			new_env[j] = ft_strdup(built->env[i]);
			j++;
		}
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
