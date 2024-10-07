/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/07 13:37:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt(char **env, t_env *built)
{
	char	*input;
	t_parse	*parse;

	ft_setup_signals_handler();
	ft_init_history();
	while (1)
	{
		parse = (t_parse *)malloc(sizeof(t_parse));
		input = ft_zsh_prompt(built);
		ft_multiple_checks(built, input);
		if (ft_strlen(input) == 0)
			continue ;
		ft_save_std(built);
		if (ft_strlen(input) > 0)
			parse->arg = ft_strdup(input);
		free(input);
		if (g_signal_received)
		{
			g_signal_received = 0;
			continue ;
		}
		ft_parsing(parse, built, env);
		ft_reset_std(built);
	}
}
