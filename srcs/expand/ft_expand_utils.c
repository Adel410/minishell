/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 20:04:34 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_dollar_in_string(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_iso_dol(char *str, int i, t_env *built)
{
	int		start;
	int		end;
	char	*tmp;

	start = i;
	end = 0;
	if (str[0] == '$' && str[1] == '?')
	{
		built->expand_string = ft_strdup("?");
		return ;
	}
	while (str[i])
	{
		if (ft_is_alpha(str[i]) == 0)
		{
			end = i;
			break ;
		}
		i++;
	}
	if (end == 0)
		end = ft_strlen(str);
	tmp = ft_master_strndup(str, start, end - start);
	built->expand_string = ft_strdup(tmp);
	free(tmp);
}

void	ft_isolate_dollar(char *str, t_env *built)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?')
		{
			built->expand_string = ft_strdup("?");
			break ;
		}
		if (str[i] == '$')
		{
			ft_iso_dol(str, i + 1, built);
			break ;
		}
		i++;
	}
	free(tmp);
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

void	ft_is_check_after_dollar(char *str, t_env *built)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (ft_isdigit(str[i + 1] == 1))
		ft_expand_dollar(str, built);
}
