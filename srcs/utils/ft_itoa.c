/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:48:56 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 14:52:18 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_str_len(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	else if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	long	num;

	num = n;
	i = ft_get_str_len(n);
	ptr = (char *)malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	i = ft_get_str_len(n) - 1;
	if (num == 0)
		ptr[0] = '0';
	if (num < 0)
	{
		ptr[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		ptr[i] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	return (ptr);
}
