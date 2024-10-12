/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:20:32 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/12 18:24:32 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

void	ft_setup_signals_handler(void)
{
	signal(SIGSEGV, ft_handle_sigsegv);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
