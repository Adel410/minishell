/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:53 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 16:53:38 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_dollar_in_string(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) ==  0)
		return (0);
	while (str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] != ' ')
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
	if (str[0] == '$' && str[1] == '?')
	{
		dollar_string = ft_strdup("?");
		return (dollar_string);
	}
	if (ft_isdigit(str[i + 1]) == 1)
	{
		
	}
	while (str[i])
	{
		if (ft_is_alpha(str[i]) == 0)
		{
			write(1,"ENTRY\n", 6);
			// printf("value i == %d\n",i);
			end = i;
			break ;
		}
		i++;
	}
	if (end == 0)
		end = ft_strlen(str);
	// printf("start == %d\n", start);
	// printf("end == %d\n", end);
	// printf("str == %s\n", str);
	dollar_string = ft_master_strndup(str, start, end - start);
	// printf("dollar_string == %s\n", dollar_string);
	return (dollar_string);
}

char	*ft_isolate_dollar(char *str)
{
	int		i;

	char	*dollar_string;

	i = 0;

	dollar_string = NULL;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?')
		{
			dollar_string = ft_strdup("?");
			return(dollar_string);
		}
		if (str[i] == '$')
		{
			dollar_string = ft_iso_dol(str, i + 1);
			break ;
		}
		i++;
	}
	return (dollar_string);
}
