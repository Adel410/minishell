/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:09 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 15:07:35 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	int		negative;
	long	result;
	int		digit;

	negative = 0;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative = 1;
		else
			negative = 0;
		nptr++;
	}
	while (1)
	{
		if (*nptr >= '0' && *nptr <= '9')
			digit = *nptr - '0';
		else if (*nptr >= 'a' && *nptr <= 'z')
			digit = *nptr - 'a' + 10;
		else if (*nptr >= 'A' && *nptr <= 'Z')
			digit = *nptr - 'A' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		if (result > (LONG_MAX - digit) / base)
		{
			if (negative)
				result = LONG_MIN;
			else
				result = LONG_MAX;
			while ((*nptr >= '0' && *nptr <= '9') || (*nptr >= 'a'
					&& *nptr <= 'z') || (*nptr >= 'A' && *nptr <= 'Z'))
				nptr++;
			break ;
		}
		result = result * base + digit;
		nptr++;
	}
	if (endptr)
		*endptr = (char *)nptr;
	if (negative)
		return (-result);
	else
		return (result);
}

void	ft_exit(t_exe *exec, t_env *built, t_b *b)
{
	long	code;
	char	*str;
	char	*endptr;
	char	*merged_str;

	merged_str = NULL;
	ft_putstr_fd("exit\n", 1);
	(close(built->save_stdin), close(built->save_stdout));
	if (exec->cmds[1])
	{
		str = exec->cmds[1];
		if ((ft_strcmp(str, "+") == 0 || ft_strcmp(str, "-") == 0)
			&& exec->cmds[2])
		{
			merged_str = ft_calloc(strlen(str), ft_strlen(exec->cmds[2]) + 1);
			if (!merged_str)
				built->exit_code = 1;
			ft_strcpy(merged_str, str);
			ft_strcat(merged_str, exec->cmds[2]);
			str = merged_str;
		}
		if (!is_valid_number(str))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			code = 2;
		}
		else
		{
			code = ft_strtol(str, &endptr, 10);
			if (*endptr != '\0')
			{
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				code = 2;
			}
			else if (exec->cmds[2] && !merged_str)
			{
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
				free(merged_str);
				return ;
			}
		}
		free(merged_str);
	}
	else
		code = built->exit_code;
	if (code > INT_MAX || code < INT_MIN)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
	}
	ft_free_b(b);
	ft_free_exec(exec);
	ft_free_env(built);
	exit((code % 256 + 256) % 256);
}
