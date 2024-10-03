/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:03:20 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 19:51:35 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strtrim(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	ft_strrtrim(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
		{
			str[i] = '\0';
			break ;
		}
		i--;
	}
}

void	ft_print_lex(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		printf("index == %c\n", tmp->type);
		printf("element == %s\n", tmp->str);
		tmp = tmp->next;
	}
}

int	ft_check_access(char *to_test, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = NULL;
		tmp = ft_strjoin2(paths[i], to_test);
		if (access(tmp, X_OK) == 0)
		{
			free(tmp);
			return (1);
		}
		if (tmp)
			free(tmp);
		i++;
	}
	return (0);
}
