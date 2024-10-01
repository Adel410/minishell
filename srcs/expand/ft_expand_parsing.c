/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:01:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 18:50:52 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_while_expand_env(t_env *built, char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (built->env[i])
// 	{
// 		if (ft_strncmp(built->env[i], str, ft_strlen(str)) == 0)
// 		{
// 			free(str);
// 			str = ft_strdup(built->env[i]);
// 			while (str[j] != '=')
// 				j++;
// 			free(str);
// 			str = ft_strndup2(built->env[i], j + 1);
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (built->env[i] == NULL)
// 		str = ft_strdup("");
// 	return (str);
// }

char	*ft_expand_env(char *str, t_env *built)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] == '?')
	{
		free(str);
		str = ft_itoa(built->exit_code);
		return (str);
	}
	if (str[ft_strlen(str) - 1] == '\n')
		ft_strrtrim(str, '\n');
	str = ft_strjoin2(str, "=");
	//str = ft_while_expand_env(built, str);
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
			i++;
			if (str[i] == '?')
				return (1);
			while (str[i] && ft_is_alpha(str[i]) == 1)
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
	i = i + size + 1;
	after = ft_strndup2(str, i);
	;
	tmp = ft_strjoin2(tmp, after);
	return (tmp);
}

char	*ft_expand_dollar(char *str, t_env *built, int flag)
{
	char	*expand_string;

	if (str[0] == '$' && str[1] == '\0')
	{
		expand_string = ft_strdup("$");
		return (expand_string);
	}
	else if (str[0] == '"' && str[1] == '$' && str[2] == '"' && str[3] == '\0')
	{
		expand_string = ft_strdup("$");
		return (expand_string);
	}
	expand_string = ft_isolate_dollar(str);
	if (flag == 0)
		expand_string = ft_expand_env(expand_string, built);
	expand_string = ft_join_string_env(str, expand_string);
	if (ft_dollar_in_string(expand_string) == 1)
		expand_string = ft_expand_dollar(expand_string, built, 0);
	if (expand_string[0] == '"')
		expand_string = ft_strjoin2(expand_string, "\"");
	else if (expand_string[0] == '\'')
		expand_string = ft_strjoin2(expand_string, "\'");
	return (expand_string);
}

void	ft_is_check_after_dollar(char *str, t_env *built)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (ft_isdigit(str[i + 1] == 1))
		ft_expand_dollar(str, built, 1);
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
			{
				ft_is_check_after_dollar(tmp->arg, built);
				tmp->arg = ft_expand_dollar(tmp->arg, built, 0);
			}
		}
		tmp = tmp->next;
	}
}
