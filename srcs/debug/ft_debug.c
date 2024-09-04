/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:11:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/02 16:30:28 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_debug(t_a *a)
{
    printf("\n\n\n");
    printf(GREEN"%s == input\n"RESET,a->input);
    printf(GREEN"%d == nombre de metachar\n"RESET, a->token_count);
    int i = 0;
    int j;
    printf("\n\n\n");
    printf(YELLOW"###INPUT TAB###\n\n"RESET);
    while (a->tab_input[i])
    {
        printf(YELLOW"commande num = %d \n %s\n"RESET,i ,a->tab_input[i]);
        i++;
    }
    printf("\n\n\n");
    i = 0;
    printf(RED"###OPTION TAB###\n\n"RESET);
    while (a->tab_option_input[i])
    {
        printf(RED"commande num = %d \n %s\n"RESET,i ,a->tab_option_input[i]);
        i++;
    }
    i = 0;
    printf("\n\n\n");
    printf(BLUE"###META TAB###\n\n"RESET);
    while (a->tab_meta_input[i])
    {
        printf(BLUE"commande num = %d \n %s\n"RESET,i ,a->tab_meta_input[i]);
        i++;
    }
    i = 0;
    printf("\n\n\n");
    printf(MAGENTA"###CMD TAB###\n\n"RESET);
    while (a->tab_cmd[i])
    {
        j = 0;
        while (a->tab_cmd[i][j])
        {
            printf(MAGENTA"commande num = %d \n lexer %d \n %s\n"RESET,i, j,a->tab_cmd[i][j]);
            j++;
        }
        i++;
    }
    
}