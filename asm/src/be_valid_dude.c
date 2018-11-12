/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   be_valid_dude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:45:05 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 13:45:09 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

int				check_com_or_name(char *str, t_i_j *n_c_set, int fd)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	if (!ft_strncmp(&str[i], ".co", 3))
	{
		if (check_comment(&str[i], &n_c_set->comment, fd) == -1)
		{
			ft_memdel((void **)&str);
			error_exit_with_sound(-1);
		}
		return (n_c_set->comm_is_set = 1);
	}
	else if (!ft_strncmp(&str[i], ".na", 3))
	{
		if (check_name(&str[i], &n_c_set->name, fd) == -1)
		{
			ft_memdel((void **)&str);
			error_exit_with_sound(-1);
		}
		return (n_c_set->name_is_set = 1);
	}
	return ((str[i] == ';' || str[i] == '#') ? 1 : 0);
}

void			check_header(t_i_j *n_c_set)
{
	if (n_c_set->name_is_set == 0 && n_c_set->comm_is_set == 1)
	{
		ft_printf("%&Error: no valid name\n", 2);
		error_exit_with_sound(-1);
	}
	else if (n_c_set->name_is_set == 1 && n_c_set->comm_is_set == 0)
	{
		ft_printf("%&Error: no valid comment\n", 2);
		error_exit_with_sound(-1);
	}
	else if (n_c_set->name_is_set == 0 && n_c_set->comm_is_set == 0)
	{
		ft_printf("%&Error: no valid comment and name\n", 2);
		error_exit_with_sound(-1);
	}
}

int				be_valid_dude(int fd, t_command **command, t_i_j *n_c_set)
{
	char		*str;

	str = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		g_num_str++;
		if (str == NULL)
			continue ;
		if (!check_com_or_name(str, n_c_set, fd))
		{
			ft_memdel((void**)&str);
			return (0);
		}
		ft_memdel((void**)&str);
		if (n_c_set->name_is_set == 1 && n_c_set->comm_is_set == 1)
			break ;
	}
	check_header(n_c_set);
	if (!code_analyse(fd, str, command, *n_c_set))
		return (0);
	return (1);
}
