/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:19:08 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/03 17:27:05 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_parser(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (parse)
	{
		tmp = NULL;
		if (parse->next)
			tmp = parse->next;
		else if (parse && parse->arg && parse->arg[0] == '\0')
			free(parse->arg);
		if (parse && parse->arg)
			free(parse->arg);
		if (parse)
			free(parse);
		parse = tmp;
	}
}

void	ft_printf_lst(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp->arg)
			printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}

void	ft_free_node(t_parse *node)
{
	free(node->arg);
	free(node);
}

int	ft_string_is_closed(char *str)
{
	int	i;
	int	size;

	size = ft_strlen(str);
	i = 0;
	if (str[size - 1] == str[i])
		return (1);
	return (0);
}
