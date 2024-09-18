/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:05:08 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/16 14:13:46 by nicjousl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void    ft_debug_parser(t_a *a)
{
    int i;

    i = 0;
    printf(GREEN" ### DEBUG PARSER ###\n\n"RESET);
    printf(GREEN"%s == input\n"RESET,a->input);
    printf(GREEN"%d == nombre de metachar\n"RESET, a->token_count);
    printf("\n\n\n");
    printf(YELLOW"###INPUT TAB###\n\n"RESET);
    while (a->tab_input[i])
    {
        printf(YELLOW"commande num = %d \n %s\n"RESET,i ,a->tab_input[i]);
        i++;
    }
    ft_debug_parser2(a);
}
void    ft_debug_parser2(t_a *a)
{
    int i;
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
    printf(CYAN"###NEW META TAB###\n\n"RESET);
    while (a->tab_meta_new_input[i])
    {
        printf(CYAN"commande num = %d \n %s\n"RESET,i ,a->tab_meta_new_input[i]);
        i++;
    }
    ft_debug_parser3(a);
}

void    ft_debug_parser3(t_a *a)
{
    int i;
    
    i = 0;
    printf("\n\n\n");
    printf(GREEN"###SPACE TAB###\n\n"RESET);
    while (a->tab_space_input[i])
    {
        printf(GREEN"commande num = %d \n %s\n"RESET,i ,a->tab_space_input[i]);
        i++;
    }
    i = 0;
    printf("\n\n\n");
    printf(RED"###STRING TAB###\n\n"RESET);
    while (a->tab_string_input[i])
    {
        printf(RED"commande num = %d \n %s\n"RED,i ,a->tab_string_input[i]);
        i++;
    }
}

void    ft_debug_lexer(t_a *a)
{
    int i;

    i = 0;
    printf("###CMD TAB###\n\n");
    while (a->tab_cmd[i])
    {
            printf("commande num = %d \n lexer = %s \n contenu = %s\n\n\n ",i, a->tab_cmd[i][1],a->tab_cmd[i][0]);
        i++;
    }
}
