/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:41:19 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/04 15:17:55 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
	
void	ft_debug_lst(t_exe *exe)
{
	t_exe	*ptr;
	int		i;

	ptr = exe;
	while (ptr)
	{
		printf("%s == input_file\n", ptr->input_file);
		printf("%s == limiter\n", ptr->limiter);
		printf("%s == output_file\n", ptr->output_file);
		printf("%d == append_output\n", ptr->append_output);
		printf("%d == here_doc\n", ptr->here_doc);
		printf("%d == builtin\n", ptr->builtin);
		i = 0;
		while (ptr->cmds[i])
		{
			printf("%s == cmds\n", ptr->cmds[i]);
			i++;
		}
		i = 0;
		ptr = ptr->next;
		printf("\n\n");
	}
}
