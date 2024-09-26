/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/26 18:47:17 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_d(t_env *built, t_parse *parse)
{
	(void)built;
	(void)parse;
	built->exit_code = 143;
	exit(143);
}

void	ft_prompt(char **env, t_env *built, t_parse *parse)
{
	char	*input;

	ft_setup_signals_handler();
	ft_init_history();
	while (1)
	{
		input = NULL;
		if (built->exit_code == 0)
			input = readline(GREEN BIG "➜ " CYAN BIG " Minishell 🔧🐪 " RESET);
		else
			input = readline(RED BIG "➜ " CYAN BIG " Minishell 🔧🐪 " RESET);
		if (!input)
			ft_ctrl_d(built, parse);
		if (input && *input)
			add_history(input);
		if (ft_strlen(input) == 0)
			continue ;
		if (ft_strlen(input) > 0)
			parse->arg = ft_strdup(input);
		free(input);
		// ft_free_env(built);
		//printf("%d", exit_code);
		ft_parsing(parse, built, env);
	}
}
