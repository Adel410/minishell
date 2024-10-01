/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:04:23 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/01 13:50:26 by ahadj-ar         ###   ########.fr       */
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

// void	ft_prompt(char **env, t_env *built, t_parse *parse)
void	ft_prompt(char **env, t_env *built)
{
	char	*input;
	t_parse	*parse;

	ft_setup_signals_handler();
	ft_init_history();
	while (1)
	{
		parse = (t_parse *)malloc(sizeof(t_parse));
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
		// save std
		built->save_stdin = dup(STDIN_FILENO);
		built->save_stdout = dup(STDOUT_FILENO);
		if (ft_strlen(input) > 0)
			parse->arg = ft_strdup(input);
		free(input);
		ft_parsing(parse, built, env);
		// reset std
		dup2(built->save_stdin, STDIN_FILENO);
		dup2(built->save_stdout, STDOUT_FILENO);
		(close(built->save_stdin), close(built->save_stdout));
	}
}
