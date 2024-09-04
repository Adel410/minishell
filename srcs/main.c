/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:54:49 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 16:39:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtin.h"

t_env	*ft_add_env(t_env	*head, char **env)
{
	int	i;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		new = ft_lstnew(env[i]);
		if (!new)
			printf("erreur la\n");
		ft_lstadd_back(&head, new);
		i++;
	}
	return (head);
}

int	main(int ac, char **av, char **env)
{
	t_a	a;
	t_env	**built;
	
	(void) av;
	(void) env;
	built = (t_env **)malloc(sizeof(t_env **));
	if (!built)
	{
		printf("error here\n");
		exit(1);
	}
	*built = ft_add_env(*built, env);
	if (ac == 1)
		ft_prompt(env, &a, built);
	else
		ft_error(0, &a);
}
