/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/06 15:51:34 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction principale

void	ft_prompt(char **env, t_a *a, t_env	**built)
{
	// ft_setup_signals_handler -> gestions des signaux pour ctrl-C
	// et ctrl-backslash pendant le prompt
	// |
	// V
	ft_setup_signals_handler();
	
	// ft_init_history initialise les variables dynamiques pour l'historique
	// |
	// V
	ft_init_history();
	while (1)
	{
		ft_init_prompt(a);
		a->input = readline(GREEN BIG "➜ " CYAN BIG " Minishell 🔧 " RESET);
		// Gestion de l'historique et des built-in si on a un input
		// |
		// V
		if (a->input && *a->input)
		{
			// add_history ajoute l'input a l'historique dynamique
			add_history(a->input);
			// on envoie l'input dans ft_which_builtin pour checker si
			// c'est un built-in a executer
			ft_which_builtin(built, a, a->input, env);
		}
		// Ce if c'est le cas du CTRL-D, qui quitte l'execution si
		// il recoit cette combinaison de touche, si le retour de readline est 
		// NULL c'est que c'est un CTRL-D, sinon il est pas NULL mais de strlen = 0
		// |
		// V
		if (a->input == NULL)
			ft_cleanup(a);
			
		// On continue si on appuie juste sur entree sans rien input,
		// avant ca segfaultait
		// |
		// V
		if (ft_strlen(a->input) == 0)
			continue ;

		// On rentre dans le parsing si on a un input valide
		// pour eviter les segfault sur un split NULL
		// |
		// V
		if (ft_strlen(a->input) > 0)
		{
			a->tab_input = ft_split(a->input, ' ');
			if (!a->tab_input)
				ft_cleanup(a);
		}
		ft_nice_tab(a);
		ft_lexer(a, built);
		ft_free(a);
	}
}
