/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryabchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 17:54:08 by oryabchu          #+#    #+#             */
/*   Updated: 2018/06/02 17:54:09 by oryabchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"
#include <dirent.h>

void	add_file_name(t_i_j *name_i_j, char **argv)
{
	int		len;
	char	*buff;
	int		len_name_file;

	len = ft_strlen(argv[3]) - 1;
	len_name_file = ft_strlen(argv[1]);
	while (len_name_file != 0 && argv[1][len_name_file] != '/')
		len_name_file--;
	if (argv[1][len_name_file] == '/')
		len_name_file++;
	if (argv[3][len] != '/')
	{
		buff = ft_strjoin(argv[3], "/");
		name_i_j->file = ft_strjoin(buff, &(argv[1][len_name_file]));
		ft_memdel((void **)&buff);
	}
	else
		name_i_j->file = ft_strjoin(argv[3], &(argv[1][len_name_file]));
}

void	parse_direct(t_i_j *name_i_j, char **argv)
{
	DIR		*dir;

	if (!ft_strcmp(argv[2], "-a"))
	{
		if (!(dir = opendir(argv[3])))
		{
			ft_printf("%&Invalid dir name or not enough rights to save file\n",
																			2);
			error_exit_with_sound(-1);
		}
		add_file_name(name_i_j, argv);
		(dir != NULL) ? closedir(dir) : 0;
	}
	else
	{
		ft_printf("%&Usage ./asm filename [-a] [directory]\n", 2);
		ft_printf("%&\t-a : creating a file in select directory.\n", 2);
		error_exit_with_sound(-1);
	}
}

void	error_exit_with_sound(int error)
{
	system("say 'An error occurred while compiling the bot'");
	exit(error);
}
