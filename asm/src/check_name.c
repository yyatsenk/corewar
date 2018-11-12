/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:59:42 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:59:45 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		help_0(char *str, int i, int j)
{
	if (!str[i])
	{
		i = 4;
		while (str[++i])
		{
			j = i - 1;
			while ((str[++j] >= 'a' && str[j] <= 'z')\
				|| (str[j] >= '0' && str[j] <= '9'))
				if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]))
				{
					ft_printf("%&Syntax error at token [TOKEN][%03i:%03i]\
	INSTRUCTION \"%s\"\n", 2,\
						g_num_str, i + 1, ft_strsub(str, i, j - i));
					error_exit_with_sound(-1);
				}
		}
	}
	if (!str[i])
	{
		ft_printf("%&Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n", 2,\
			g_num_str, i + 1);
		error_exit_with_sound(-1);
	}
}

static void		help_1(char *str, int i, int fd, int kavi)
{
	if (!str[i])
	{
		while (kavi != 2 && get_next_line(fd, &str) != 0)
		{
			if (str == NULL)
				continue ;
			g_num_str++;
			i = -1;
			while (str[++i])
				if (str[i] == '\"')
				{
					kavi++;
					break ;
				}
			free(str);
		}
		if (kavi == 2)
			ft_printf("%&Lexical error at [%i:%i]\n", 2, g_num_str, i + 2);
		else
			ft_printf("%&Syntax error at token [TOKEN][%03i:%03i]\
	END \"(null)\"\n", 2, g_num_str, 1);
		error_exit_with_sound(-1);
	}
}

int				check_name(char *str, char **name, int fd)
{
	int			i;
	int			j;
	int			kavi;

	kavi = 0;
	i = ft_strlen(NAME_CMD_STRING);
	if (ft_strncmp(str, NAME_CMD_STRING, i))
		return (-1);
	while (str[i++] && str[i] != '\"')
		if (str[i] != '\t' && str[i] != ' ')
		{
			ft_printf("%&Lexical error at [%i:%i]\n", 2, g_num_str, i + 1);
			return (-1);
		}
	help_0(str, i, 0);
	j = ++i;
	while (str[i] && str[i] != '\"')
		i++;
	help_1(str, i, fd, ++kavi);
	*name = ft_strsub(str, j, i - j);
	return (check_end_string(&str[i + 1]));
}

int				check_open_champ_file(char *name_champ_file, int fd)
{
	int		length;

	length = ft_strlen(name_champ_file);
	if (name_champ_file[length - 1] == 's' \
		&& name_champ_file[length - 2] == '.')
	{
		fd = open(name_champ_file, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("%&Can not open file\n", 2);
			error_exit_with_sound(-1);
		}
		return (fd);
	}
	else
	{
		ft_printf("%&Wrong file extension.\n", 2);
		error_exit_with_sound(-1);
		return (-1);
	}
}
