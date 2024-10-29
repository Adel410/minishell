/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:54:49 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/12 17:10:42 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_shlvl(char *old_shlvl)
{
	char	*shlvl;
	char	*level_str;
	int		level;

	level = ft_atoi(old_shlvl + 6);
	level++;
	level_str = ft_itoa(level);
	if (!level_str)
		return (NULL);
	shlvl = ft_calloc(sizeof(char), 7 + ft_strlen(level_str));
	if (!shlvl)
		return (NULL);
	ft_strcpy(shlvl, "SHLVL=");
	ft_strcat(shlvl, level_str);
	free(level_str);
	return (shlvl);
}

void	ft_add_env(t_env *head, char **env)
{
	int	i;
	int	end;

	i = 0;
	if (env)
	{
		end = ft_strstrlen(env);
		head->env = ft_calloc(end + 1, sizeof(char *));
		while (env[i])
		{
			if (ft_strncmp(env[i], "SHLVL", 5) == 0)
			{
				free(head->env[i]);
				head->env[i] = ft_get_shlvl(env[i]);
				i++;
			}
			head->env[i] = ft_strdup(env[i]);
			i++;
		}
	}
	return ;
}

int		g_signal_received = 0;

int	main(int ac, char **av, char **env)
{
	t_env	*built;

	(void)av;
	g_signal_received = 0;
	built = (t_env *)malloc(sizeof(t_env));
	if (!built)
		exit(EXIT_FAILURE);
	built->exit_code = 0;
	ft_add_env(built, env);
	if (ac == 1)
		ft_prompt(built);
	else
	{
		free(built);
		ft_error(0);
	}
}
