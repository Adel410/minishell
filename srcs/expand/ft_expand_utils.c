/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/26 17:08:42 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_dollar_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_iso_dol(char *str, int i)
{
	char	*dollar_string;
	int		start;
	int		end;

	start = i;
	end = 0;
	while (str[i])
	{
		if (str[i] == 32 || str[i] == '"' || str[i] == '\'')
		{
			end = i;
			break ;
		}
		i++;
	}
	if (end == 0)
		end = ft_strlen(str);
	dollar_string = ft_master_strndup(str, start, end - start);
	return (dollar_string);
}

char	*ft_isolate_dollar(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*dollar_string;

	i = 0;
	start = 0;
	end = 0;
	dollar_string = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar_string = ft_iso_dol(str, i + 1);
			break ;
		}
		i++;
	}
	return (dollar_string);
}
