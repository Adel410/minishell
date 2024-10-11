/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/11 18:20:53 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt(t_env *built)
{
	t_parse	*parse;

	ft_setup_signals_handler();
	ft_init_history();
	while (1)
	{
		if (g_signal_received)
			g_signal_received = 0;
		parse = (t_parse *)malloc(sizeof(t_parse));
		if (!parse)
			exit(EXIT_FAILURE);
		ft_zsh_prompt(built);
		ft_multiple_checks(built, built->input);
		if (ft_strlen(built->input) == 0)
		{
			(free(parse), free(built->input));
			continue ;
		}
		ft_save_std(built);
		if (ft_strlen(built->input) > 0)
			parse->arg = ft_strdup(built->input);
		free(built->input);
		ft_parsing(parse, built);
		ft_reset_std(built);
	}
}
