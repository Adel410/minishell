/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:12:37 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 19:36:26 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	ft_check_access(char *to_test, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin2(paths[i], to_test);
		if (access(tmp, X_OK) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

void	ft_free_lex(t_lex *lex)
{
	t_lex	*tmp;

	while (lex)
	{
		tmp = lex->next;
		free(lex->str);
		free(lex);
		lex = tmp;
	}
}

void	ft_check_type(t_lex *lex)
{
	t_lex	*current;

	current = lex;
	if (current->type == '4')
		ft_putstr("minishell: syntax error near unexpected token '|'\n");
	else if (current->type == '5' || current->type == '6'
		|| current->type == '#' || current->type == '*')
		ft_putstr("minishell: syntax error near unexpected token `newline'\n");
}

int	ft_count_pipe(t_lex *lex)
{
	int		count;
	t_lex	*current;

	current = lex;
	count = 0;
	while (current)
	{
		if (current->type == '4')
			count++;
		current = current->next;
	}
	return (count);
}
