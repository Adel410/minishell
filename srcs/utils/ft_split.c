/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:58 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/17 16:59:41 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction pour libérer la mémoire allouée pour le tableau de chaînes de caractères
void freetab(char **tab, int k)
{
    while (k >= 0)
    {
        free(tab[k]);
        k--;
    }
    free(tab);
}

char    *ft_strncpy(char *dest, const char *src, unsigned int n)
{
    unsigned int i = 0;
    while (src[i] && i < n)
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

// Alloue et copie un mot dans une nouvelle chaîne
static char *ft_put_word_in_malloc(const char *s, char c)
{
    int i = 0;
    while (s[i] && s[i] != c)
        i++;
    char *word = malloc(sizeof(char) * (i + 1));
    if (!word)
        return NULL;
    ft_strncpy(word, s, i);
    word[i] = '\0';
    return word;
}

// Alloue et remplit le tableau de mots
static char **ft_malloc_word(char *s, char c)
{
    int i = 0;
    int j = 0;
    int word_count = ft_strlen(s);
    char **tab = malloc(sizeof(char *) * (word_count + 1));
    if (!tab)
        return NULL;
    while (s[i])
    {
        if (s[i] != c)
        {
            tab[j] = ft_put_word_in_malloc(&s[i], c);
            if (!tab[j])
            {
                freetab(tab, j - 1);
                return NULL;
            }
            while (s[i] && s[i] != c)
                i++;
            j++;
        }
        else
        {
            tab[j] = malloc(sizeof(char) * 2);
            tab[j][0] = c;
            tab[j][1] = '\0';
            j++;
            i++;
        }
    }
    tab[j] = NULL;
    return tab;
}

// Fonction principale de découpage de chaîne
char **ft_split(char *s, char c)
{
    if (!s)
        return NULL;
    return ft_malloc_word(s, c);
}
