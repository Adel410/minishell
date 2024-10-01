/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:54:49 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/30 18:18:24 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_end_def(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	ft_add_env(t_env *head, char **env)
{
	int		i;
	int		end;

	i = 0;
	end = ft_strstrlen(env);
	head->env = ft_calloc(end + 1, sizeof(char *));
	while (env[i])
	{
		head->env[i] = ft_strdup(env[i]);
		i++;
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_env	*built;
	// t_parse	*parse;

	built = (t_env *)malloc(sizeof(t_env ));
	// parse = (t_parse *)malloc(sizeof(t_parse));
	if (!built)
	{
		printf("error here\n");
		exit(1);
	}
	built->exit_code = 0;
	ft_add_env(built, env);
	if (ac == 1)
		// ft_prompt(env, built, parse);
		ft_prompt(env, built);
	else
		ft_error(0);
}
