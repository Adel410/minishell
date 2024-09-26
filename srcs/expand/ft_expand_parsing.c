/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:01:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 18:46:11 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_env(char *str, t_env *built)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	str = ft_strjoin2(str, "=");
	while (built->env[i])
	{
		if (ft_strncmp(built->env[i], str, ft_strlen(str)) == 0)
		{
			free(str);
			str = ft_strdup(built->env[i]);
			while (str[j] != '=')
				j++;
			free(str);
			str = ft_strndup2(built->env[i], j + 1);
			break ;
		}
		i++;
	}
	if (built->env[i] == NULL)
		str = ft_strdup("");
	return (str);
}

int	ft_size_of_expand(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ' && str[i] != '\0')
			{
				size++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (size);
}

char	*ft_join_string_env(char *str, char *expand)
{
	char	*before;
	char	*after;
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			i++;
		else
			break ;
	}
	before = ft_strndup(str, i);
	tmp = ft_strjoin2(before, expand);
	size = ft_size_of_expand(str);
	i = i + size;
	after = ft_strndup2(str, i);
	tmp = ft_strjoin2(tmp, after);
	return (tmp);
}

char	*ft_expand_dollar(char *str, t_env *built)
{
	char	*expand_string;

	expand_string = ft_isolate_dollar(str);
	if (expand_string[0] == '?' && expand_string[1] == '\0')
	{
		free(expand_string);
		expand_string = ft_itoa(built->exit_code);
	}
	else
		expand_string = ft_expand_env(expand_string, built);
	expand_string = ft_join_string_env(str, expand_string);
	if (ft_dollar_in_string(expand_string) == 1)
		expand_string = ft_expand_dollar(expand_string, built);
	return (expand_string);
}

void	ft_expand_arg(t_parse *parse, t_env *built)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp && tmp->arg && tmp->arg[0] != '\'')
		{
			if (ft_dollar_in_string(tmp->arg) == 1)
				tmp->arg = ft_expand_dollar(tmp->arg, built);
		}
		tmp = tmp->next;
	}
}
