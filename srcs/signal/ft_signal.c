/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:20:32 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/29 20:19:01 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CTRL-C qui normalement sort du processus et qui maintenant affiche juste une
// newline sans sortir du minishell
void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// CTRL-backslash n'a aucun comportement maintenant, on reprompt juste
void	ft_handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// initialise les conditions avec signal() pour CTRL-C (SIGINT) et
// CTRL-backslash(SIGQUIT)
void	ft_setup_signals_handler(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}
