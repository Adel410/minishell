/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:01:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/07 18:25:36 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expand_variable(t_env *built)
{
	built->i = 0;
	built->j = 0;
	while (built->env[built->i])
	{
		if (ft_strncmp(built->env[built->i], built->expand_string,
				ft_strlen(built->expand_string)) == 0)
		{
			free(built->expand_string);
			built->expand_string = ft_strdup(built->env[built->i]);
			while (built->expand_string[built->j] != '=')
				built->j++;
			free(built->expand_string);
			built->expand_string = ft_strndup2(built->env[built->i], built->j
					+ 1);
			break ;
		}
		else if (built->i >= (ft_strstrlen(built->env) - 1)
			&& (ft_strncmp(built->env[built->i], built->expand_string,
					ft_strlen(built->expand_string)) != 0))
			(free(built->tmp), free(built->expand_string));
		built->i++;
	}
	if (built->env[built->i] == NULL)
		built->expand_string = ft_strdup("");
}

void	ft_expand_env(t_env *built)
{
	char	*tmp;

	tmp = ft_strdup(built->expand_string);
	free(built->expand_string);
	if (tmp[0] == '?')
	{
		free(tmp);
		built->expand_string = ft_itoa(built->exit_code);
		return ;
	}
	if (tmp[ft_strlen(tmp) - 1] == '\n')
		ft_strrtrim(tmp, '\n');
	built->expand_string = ft_strjoin2(tmp, "=");
	free(tmp);
	ft_expand_variable(built);
}

void	ft_join_string_env(char *str, char *expand, t_env *built)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*tmp2;
	int		size;

	built->i = 0;
	while (str[built->i])
	{
		if (str[built->i] != '$')
			built->i++;
		else
			break ;
	}
	before = ft_strndup(str, built->i);
	tmp = ft_strjoin2(before, expand);
	(free(before), free(expand));
	size = ft_size_of_expand(str);
	built->i = built->i + size + 1;
	after = ft_strndup2(str, built->i);
	tmp2 = ft_strjoin2(tmp, after);
	free(tmp);
	built->tmp = ft_strdup(tmp2);
	(free(after), free(tmp2));
}

char	*ft_expand_dollar(char *str, t_env *built)
{
	built->tmp = NULL;
	if (!str)
		return (NULL);
	if (str && str[0] == '$' && str[1] == '\0')
	{
		built->expand_string = ft_strdup("$");
		return (built->expand_string);
	}
	else if (str && str[0] == '"' && str[1] == '$' && str[2] == '"'
		&& str[3] == '\0')
	{
		built->expand_string = ft_strdup("$");
		return (built->expand_string);
	}
	ft_isolate_dollar(str, built);
	ft_expand_env(built);
	ft_join_string_env(str, built->expand_string, built);
	if (built->tmp[0] == '"')
		built->expand_string = ft_strjoin2(built->tmp, "\"");
	else if (built->tmp[0] == '\'')
		built->expand_string = ft_strjoin2(built->tmp, "\'");
	else
		built->expand_string = ft_strdup(built->tmp);
	(free(built->tmp), free(str));
	return (built->expand_string);
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
				tmp->arg = ft_expand_dollar(tmp->arg, built);
				while (ft_dollar_in_string(tmp->arg) == 1)
					tmp->arg = ft_expand_dollar(built->expand_string, built);
			}
		}
		tmp = tmp->next;
	}
}
