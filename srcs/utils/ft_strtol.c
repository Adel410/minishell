/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:31:02 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/05 13:16:40 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*ft_skip_whitespace(const char *nptr)
{
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	return (nptr);
}

const char	*ft_skip_remaining(const char *nptr)
{
	while ((*nptr >= '0' && *nptr <= '9') || (*nptr >= 'a' && *nptr <= 'z')
		|| (*nptr >= 'A' && *nptr <= 'Z'))
		nptr++;
	return (nptr);
}

const char	*ft_process_sign(const char *nptr, int *negative)
{
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			*negative = 1;
		else
			*negative = 0;
		nptr++;
	}
	return (nptr);
}

const char	*ft_convert_digits(const char *nptr, long *result, int base,
		int negative)
{
	int	digit;

	while (1)
	{
		digit = ft_get_digit(*nptr);
		if (digit < 0 || digit >= base)
			break ;
		if (*result > (LONG_MAX - digit) / base)
		{
			if (negative)
				*result = LONG_MIN;
			else
				*result = LONG_MAX;
			nptr = ft_skip_remaining(nptr);
			break ;
		}
		*result = *result * base + digit;
		nptr++;
	}
	return (nptr);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	int		negative;
	long	result;

	negative = 0;
	result = 0;
	nptr = ft_skip_whitespace(nptr);
	nptr = ft_process_sign(nptr, &negative);
	nptr = ft_convert_digits(nptr, &result, base, negative);
	if (endptr)
		*endptr = (char *)nptr;
	if (negative)
		return (-result);
	return (result);
}
