/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:09 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/10 20:39:34 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_validate_number_and_exit(char *str, t_env *built)
{
	char	*endptr;
	long	code;

	if (!ft_is_valid_number(str))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_env(built);
		exit(2);
	}
	code = ft_strtol(str, &endptr, 10);
	if (*endptr != '\0')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_env(built);
		exit(2);
	}
	built->exit_code = code;
}

int	ft_process_exit_arguments(t_exe *exec, char *str, char *merged_str,
		t_env *built)
{
	ft_validate_number_and_exit(str, built);
	if (ft_handle_too_many_args(exec->cmds, merged_str, built) == 1)
	{
		return (1);
		free(merged_str);
	}
	else
		return (0);
}

int	ft_is_exit_code_invalid(long exit_code, char *str)
{
	if (exit_code > INT_MAX || exit_code < INT_MIN)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

void	ft_cleanup_and_exit(t_b *b, t_exe *exec, t_env *built, long exit_code)
{
	int	normalized_code;

	ft_free_exec(exec, b->nb_cmds1);
	ft_free_b(b);
	ft_free_env(built);
	normalized_code = exit_code % 256;
	if (normalized_code < 0)
		normalized_code += 256;
	exit(normalized_code);
}

void	ft_exit(t_exe *exec, t_env *built, t_b *b)
{
	long	exit_code;
	char	*str;
	char	*merged_str;

	ft_print_and_close(built);
	merged_str = NULL;
	if (exec->cmds[1])
	{
		str = ft_merge_sign_with_arg(exec->cmds, built);
		if (str)
		{
			if (ft_process_exit_arguments(exec, str, merged_str, built) == 1)
			{
				built->exit_code = 1;
				return ;
			}
		}
	}
	else
		str = NULL;
	exit_code = built->exit_code;
	if (ft_is_exit_code_invalid(exit_code, str))
		exit_code = 2;
	ft_cleanup_and_exit(b, exec, built, exit_code);
}
