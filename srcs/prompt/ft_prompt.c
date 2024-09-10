/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/10 16:55:06 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction principale

void	ft_prompt(char **env, t_a *a, t_env	**built)
{
	ft_setup_signals_handler();
	ft_init_history();
	while (1)
	{
		ft_init_prompt(a);
		a->input = readline(GREEN BIG "➜ " CYAN BIG " Minishell 🔧 " RESET);
		if (a->input && *a->input)
		{
			add_history(a->input);
			ft_which_builtin(built, a, a->input, env);
		}
		if (a->input == NULL)
			ft_cleanup(a);
		if (ft_strlen(a->input) == 0)
			continue ;
		if (ft_strlen(a->input) > 0)
		{
			a->tab_input = ft_split(a->input, ' ');
			if (!a->tab_input)
				ft_cleanup(a);
		}
		ft_nice_tab(a);
		ft_lexer(a, built);
		ft_execute(a, env);
		ft_free(a);
	}
}
