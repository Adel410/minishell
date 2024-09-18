/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:01:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 11:31:36 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_space_tab(t_a *a)
{
    int i;
    int j;

    i = 0;
    j = 0;
    a->tab_space_size = ft_strstrlen(a->tab_string_input);
    a->tab_space_input = ft_calloc(sizeof(char *), a->tab_space_size + 1);
    while (a->tab_string_input[i])
    {
        if (a->tab_string_input[i][0] == ' ')
            i++;
        else
        {
            a->tab_space_input[j] = ft_strdup(a->tab_string_input[i]);
            i++;
            j++;
        }
    }
}