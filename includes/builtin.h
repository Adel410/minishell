/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:59:11 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/04 14:41:00 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "./minishell.h"

typedef struct s_env
{
	char			*env_str;
	struct s_env	*next;
}					t_env;

void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *str);
void				ft_free_stack(t_env **head);

#endif