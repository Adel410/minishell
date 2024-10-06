/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:51:29 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/06 11:57:01 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtrim_spaces(char *str)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed_str;

	start = 0;
	end = strlen(str) - 1;
	while (str[start] == ' ')
		start++;
	while (end >= start && str[end] == ' ')
		end--;
	len = end - start + 1;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strncpy(trimmed_str, &str[start], len);
	trimmed_str[len] = '\0';
	return (trimmed_str);
}

void	ft_trim_quotes(t_parse *tmp)
{
	int	len;

	if (!tmp->next->arg)
		return ;
	len = ft_strlen(tmp->next->arg);
	if (len < 2)
		return ;
	if (tmp->next->arg[0] == '"' || tmp->next->arg[0] == '\'')
		ft_strtrim(tmp->next->arg, tmp->next->arg[0]);
	else if (tmp->next->arg[len - 1] == '"' || tmp->next->arg[len - 1] == '\'')
		ft_strrtrim(tmp->next->arg, tmp->next->arg[len - 1]);
}

char	*ft_concat_args(char *current, char *next)
{
	char	*trimmed_current;
	char	*trimmed_next;
	char	*new_arg;

	trimmed_current = ft_strtrim_spaces(current);
	trimmed_next = ft_strtrim_spaces(next);
	new_arg = (char *)malloc(ft_strlen(trimmed_current)
			+ ft_strlen(trimmed_next) + 1);
	if (!new_arg)
		return (NULL);
	ft_strcpy(new_arg, trimmed_current);
	ft_strcat(new_arg, trimmed_next);
	free(trimmed_current);
	free(trimmed_next);
	return (new_arg);
}

void	ft_delete_node(t_parse *tmp)
{
	t_parse	*to_delete;

	to_delete = tmp->next;
	tmp->next = tmp->next->next;
	free(to_delete->arg);
	free(to_delete);
}

void	ft_concatenate(t_parse *parse)
{
	t_parse	*tmp;
	char	*new_arg;

	tmp = parse;
	while (tmp && tmp->next)
	{
		if (tmp->next->arg && tmp->next->arg[0] != ' '
			&& tmp->next->arg[0] != '|' && tmp->next->arg[0] != '<'
			&& tmp->next->arg[0] != '>')
		{
			ft_trim_quotes(tmp);
			if (tmp->arg && tmp->next->arg)
			{
				new_arg = ft_concat_args(tmp->arg, tmp->next->arg);
				if (!new_arg)
					return ;
				free(tmp->arg);
				tmp->arg = new_arg;
			}
			ft_delete_node(tmp);
		}
		else
			tmp = tmp->next;
	}
}
