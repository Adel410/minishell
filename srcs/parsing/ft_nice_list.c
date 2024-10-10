/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nice_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:41:28 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/10 21:33:01 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_join_double_redir(t_parse *tmp, int redir_type)
{
	char	*new_arg;
	t_parse	*to_free;

	to_free = NULL;
	if (!tmp || !tmp->arg || !tmp->next || !tmp->next->arg)
		return ;
	if (redir_type == 1)
		new_arg = ft_strdup(">>");
	else
		new_arg = ft_strdup("<<");
	free(tmp->arg);
	tmp->arg = new_arg;
	to_free = tmp->next;
	tmp->next = tmp->next->next;
	free(to_free->arg);
	free(to_free);
}

void	ft_check_double_redir(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp && tmp->next)
	{
		if (tmp->arg && tmp->next->arg)
		{
			if (tmp->arg[0] == '>' && tmp->next->arg[0] == '>')
			{
				if (tmp->next->next && tmp->next->next->arg
					&& tmp->next->next->arg[0] != '>')
					ft_join_double_redir(tmp, 1);
				else
					tmp = tmp->next;
			}
			else if (tmp->arg[0] == '<' && tmp->next->arg[0] == '<')
			{
				if (tmp->next->next && tmp->next->next->arg
					&& tmp->next->next->arg[0] != '<')
					ft_join_double_redir(tmp, 2);
				else
					tmp = tmp->next;
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

int	ft_unclosed_quote(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (str[0] == '\'')
	{
		if (str[len - 1] != '\'' && (len - 1) == 0)
			return (1);
	}
	else if (str[0] == '\"')
	{
		if (str[len - 1] != '\"' && (len - 1) == 0)
			return (1);
	}
	return (0);
}

int	ft_check_input(char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (*str == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*str == '"' && single_quote == 0)
			double_quote = !double_quote;
		str++;
	}
	if (single_quote || double_quote)
		return (0);
	return (1);
}

void	ft_parsing(t_parse *parse, t_env *built)
{
	if (ft_check_input(parse->arg) == 1)
	{
		if (ft_space_arg(parse) == 1)
		{
			ft_putstr("Error: unclosed quote\n");
			return ;
		}
		if (ft_meta_arg(parse) == 0)
		{
			ft_free_parser(parse);
			built->exit_code = 2;
			return ;
		}
		ft_join_string(parse);
		ft_expand_arg(parse, built);
		ft_trim_arg(parse);
		ft_check_double_redir(parse);
		ft_concatenate(parse);
		ft_lexer(parse, built);
	}
	else
	{
		ft_invalid_input(parse);
		return ;
	}
}
