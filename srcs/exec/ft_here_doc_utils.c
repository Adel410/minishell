/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:29:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 17:25:40 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_int_to_str(int num, char *buffer)
{
	int	i;
	int	temp;

	i = 0;
	temp = num;
	if (num == 0)
	{
		buffer[i++] = '0';
	}
	else
	{
		while (temp > 0)
		{
			temp /= 10;
			i++;
		}
		buffer[i] = '\0';
		while (num > 0)
		{
			buffer[--i] = (num % 10) + '0';
			num /= 10;
		}
	}
}

char	*ft_create_filename(int here_doc_count)
{
	char	*tmp;
	char	*count_str;

	tmp = ft_calloc(sizeof(char), 20);
	ft_strcpy(tmp, "here_doc_");
	count_str = ft_itoa(here_doc_count);
	ft_strcat(tmp, count_str);
	ft_strcat(tmp, ".tmp");
	free(count_str);
	return (tmp);
}

void	ft_dup_here_doc(t_exe *exec, char *file_name, t_b *b)
{
	int	i;

	if (exec->input_file == NULL)
	{
		exec->input_file = ft_calloc(b->size_in + 1, sizeof(char *));
		if (exec->input_file == NULL)
			return ;
		exec->input_file[0] = ft_strdup(file_name);
	}
	else
	{
		i = 0;
		while (exec->input_file[i] && exec->input_file[i][0] != '\0')
			i++;
		exec->input_file[i] = ft_strdup(file_name);
	}
}

char	*ft_here_doc_bis(char *str)
{
	char	*tmp;

	tmp = ft_strjoin2(str, "_bis");
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}
