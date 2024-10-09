/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:02:10 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/09 19:15:13 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_d(t_env *built)
{
	built->exit_code = 143;
	exit(143);
}

void	ft_save_std(t_env *built)
{
	built->save_stdin = dup(STDIN_FILENO);
	built->save_stdout = dup(STDOUT_FILENO);
}

void	ft_reset_std(t_env *built)
{
	dup2(built->save_stdin, STDIN_FILENO);
	dup2(built->save_stdout, STDOUT_FILENO);
	(close(built->save_stdin), close(built->save_stdout));
}

void	ft_multiple_checks(t_env *built, char *input)
{
	if (!input)
		ft_ctrl_d(built);
	if (input && *input)
		add_history(input);
}

void	ft_zsh_prompt(t_env *built)
{
	if (built->exit_code == 0)
		built->input = readline(GREEN BIG "➜ " CYAN BIG " Minishell " RESET);
	else
		built->input = readline(RED BIG "➜ " CYAN BIG " Minishell " RESET);
}
