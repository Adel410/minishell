/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:30:29 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/05 12:40:48 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_and_close(t_env *built)
{
	ft_putstr_fd("exit\n", 1);
	close(built->save_stdin);
	close(built->save_stdout);
}

char	*ft_merge_sign_with_arg(char **cmds, t_env *built)
{
	char	*merged_str;
	char	*str;

	merged_str = NULL;
	str = cmds[1];
	if ((ft_strcmp(str, "+") == 0 || ft_strcmp(str, "-") == 0) && cmds[2])
	{
		merged_str = ft_calloc(strlen(str) + ft_strlen(cmds[2]) + 1,
				sizeof(char));
		if (!merged_str)
		{
			built->exit_code = 1;
			return (NULL);
		}
		ft_strcpy(merged_str, str);
		ft_strcat(merged_str, cmds[2]);
		return (merged_str);
	}
	return (str);
}

int	ft_handle_too_many_args(char **cmds, char *merged_str, t_env *built)
{
	if (cmds[2] && !merged_str)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		built->exit_code = 1;
		return (1);
	}
	return (0);
}
