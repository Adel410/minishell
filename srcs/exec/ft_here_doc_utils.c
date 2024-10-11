/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:29:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:30:44 by ahadj-ar         ###   ########.fr       */
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

void	ft_dup_here_doc(t_exe *exec, char *file_name, int nb_count1)
{
	int	i;

	if (exec->input_file == NULL)
	{
		exec->input_file = ft_calloc(sizeof(char *), nb_count1 + 1);
		if (exec->input_file == NULL)
			return ;
	}
	i = 0;
	while (i < nb_count1 && exec->input_file[i] != NULL)
		i++;
	if (i < nb_count1)
	{
		exec->input_file[i] = ft_strdup(file_name);
		if (exec->input_file[i] == NULL)
			return ;
		exec->input_file[i + 1] = NULL;
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
