/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:05:35 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/25 15:34:56 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_lstadd_back(t_env **lst, t_env *new)
// {
// 	t_env	*ptr;

// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		ptr = *lst;
// 		while (ptr->next != NULL)
// 		{
// 			ptr = ptr->next;
// 		}
// 		ptr->next = new;
// 	}
// }

// t_env	*ft_lstnew(char	*str)
// {
// 	t_env	*new_node;

// 	new_node = ft_calloc(sizeof(t_env), 1);
// 	if (new_node == NULL)
// 	{
// 		return (NULL);
// 	}
// 	new_node->env_str = ft_strdup(str);
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void	ft_free_stack(t_env **head)
// {
// 	t_env	*current;
// 	t_env	*next;

// 	current = *head;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// 	free(head);
// }

// void	ft_read_list(t_env **head)
// {
// 	t_env	*current;

// 	current = *head;
// 	while(current != NULL)
// 	{
// 		printf("%s\n", current->env_str);
// 		current = current->next;
// 	}
// }