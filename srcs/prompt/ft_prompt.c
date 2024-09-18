/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/17 18:17:14 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction principale

void	ft_prompt(char **env, t_a *a, t_env	**built)
{
	(void)env;
	ft_setup_signals_handler();
	ft_init_history();
	a->error = 0;
	while (1)
	{
		if (a->error == 0)
			a->input = readline(GREEN BIG "➜ " CYAN BIG " Minishell 🔧 " RESET);
		else
			a->input = readline(RED BIG "➜ " CYAN BIG " Minishell 🔧 " RESET);
		ft_init_prompt(a);
		if (a->input && *a->input)
			add_history(a->input);
		a->len_input = ft_strlen(a->input);
		if (a->len_input == 0)
			continue ;
		if (ft_strlen(a->input) > 0)
			a->tab_input = ft_split(a->input, ' ');
		ft_nice_tab(a);
		ft_lexer(a, built, env);
	}
}
