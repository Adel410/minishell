/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:04:32 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 16:17:47 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// transforme la tmp en stable
void	ft_tmp_to_lex(t_a *a)
{
	int	size;

	size = ft_strlen(a->tab_string_input[a->i]);
	a->tab_cmd[a->j] = ft_calloc(sizeof(char *), size + 1);
	a->tab_cmd[a->j][a->k] = ft_strdup(a->str_tmp);
	a->j++;
}
// transforme la **str en ***str
void	ft_parse_to_lex(t_a *a)
{
	ft_init_for_lexer(a);
	while (a->tab_string_input[a->i])
	{
		a->str_tmp = ft_strdup(a->tab_string_input[a->i]);
		ft_tmp_to_lex(a);
		a->i++;
	}
}
void	ft_lexer(t_a *a)
{
	int	i;

	i = ft_strstrlen(a->tab_string_input);
	a->tab_cmd = ft_calloc (sizeof (char **), i + 1);
	ft_parse_to_lex(a);
	ft_debug(a);
}
