/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:23:43 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/01 15:10:39 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_islower(char c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

char	ft_tolower(char c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}
