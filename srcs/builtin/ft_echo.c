/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:44:46 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 15:53:53 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_exe *current)
{
	(void)current;
	// int	i;

	// if (current->cmds[1] && ft_strcmp(current->cmds[1], "-n") == 0)
	// {
	// 	i = 2;
	// 	if (!current->cmds[i])
	// 		return ;
	// 	while (current->cmds[i])
	// 	{
	// 		printf("%s", current->cmds[i]);
	// 		printf(" ");
	// 		i++;
	// 	}
	// 	return ;
	// }
	// else
	// {
	// 	i = 1;
	// 	current = current->next;
	// 	while (current)
	// 	{
	// 		if (current->type == '2' || current->type == '3'
	// 			|| current->type == '8')
	// 		{
	// 			ft_putstr(current->string);
	// 			ft_putstr(" ");
	// 		}
	// 		current = current->next;
	// 	}
		ft_putstr("\n");
	}


// int		ft_check_env(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_copy_var_env(t_a *a)
// {
// 	int	start;
// 	int	size;

// 	start = a->c + 1;
// 	size = 0;
// 	while (a->tab_cmd[a->i][0][a->c])
// 	{
// 		if (a->tab_cmd[a->i][0][a->c] == 32)
// 			break ;
// 		if (a->tab_cmd[a->i][0][a->c] == '"')
// 			break ;
// 		a->c++;
// 		size++;
// 	}
// 	a->str_var_env = ft_master_strndup(a->tab_cmd[a->i][0], start, size);

// }

// void	ft_catch_env_var(t_a *a, char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != '=')
// 		i++;
// 	free(a->str_var_env);
// 	a->str_var_env = ft_strndup2(str, i + 1);
// 	ft_putstr(a->str_var_env);
// }
// void	ft_find_var_env(t_a *a, t_env **built)
// {
// 	t_env	*ptr;
// 	int		size;

// 	ptr = *built;
// 	size = ft_strlen(a->str_var_env);
// 	while (ptr->next)
// 	{
// 		if (ft_strncmp(a->str_var_env, ptr->env_str, size - 1) == 0)
// 			ft_catch_env_var(a, ptr->env_str);
// 		ptr = ptr->next;
// 	}
// }
// void	ft_write_env(t_a *a, t_env **built)
// {
// 	ft_copy_var_env(a);
// 	ft_find_var_env(a, built);
// }
// void	ft_quotes_with_dollar(t_a *a, t_env **built)
// {

// 	a->c = 1;
// 	while (a->tab_cmd[a->i][0][a->c + 1])
// 	{
// 		if (a->tab_cmd[a->i][0][a->c] == '$')
// 			ft_write_env(a, built);
// 		ft_putchar(a->tab_cmd[a->i][0][a->c]);
// 		a->c++;
// 	}
// 	write (1, " ", 1);
// }
// void	ft_echo(t_a *a, t_env **built)
// {
// 	printf("WELCOME TO ECHO\n");
// 	a->i++;
// 	while (a->tab_cmd[a->i])
// 	{
// 		if (a->tab_cmd[a->i][1][0] == '3')
// 			printf("%s",a->tab_cmd[a->i][0]);
// 		else if (a->tab_cmd[a->i][1][0] == '7')
// 			printf("%s ",a->tab_cmd[a->i][0]);
// 		else if (a->tab_cmd[a->i][1][0] == '8')
// 			printf("%s ",a->tab_cmd[a->i][0]);
// 		else if (a->tab_cmd[a->i][1][0] == '2')
// 		{
// 			if (ft_check_env(a->tab_cmd[a->i][0]) == 0)
// 				printf("%s",a->tab_cmd[a->i][0]);
// 			else
// 				ft_quotes_with_dollar(a, built);
// 		}
// 		else
// 			break ;
// 		a->i++;
// 	}
// 	printf("\n");
// }
