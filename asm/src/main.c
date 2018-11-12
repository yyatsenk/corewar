/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:10:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/04/26 13:10:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

t_op					g_op_tab[17] =
{
	{"live", 1, (2), (0), (0), 1, 10, "alive", 1, 4},
	{"ld", 2, (4), (1), (0), 2, 5, "load", 2, 4},
	{"st", 2, (1), (5), (0), 3, 5, "store", 2, 4},
	{"add", 3, (1), (1), (1), 4, 10, "addition", 2, 4},
	{"sub", 3, (1), (1), (1), 5, 10, "soustraction", 2, 4},
	{"and", 3, (7), (7), (1), 6, 6, "et (and r1, r2, r3 r1&r2 -> r3", 2, 4},
	{"or", 3, (7), (7), (1), 7, 6, "ou (or r1, r2, r3 r1 | r2 -> r3", 2, 4},
	{"xor", 3, (7), (7), (1), 8, 6, "ou (xor r1, r2, r3 r1^r2 -> r3", 2, 4},
	{"zjmp", 1, (2), (0), (0), 9, 20, "jump if zero", 1, 2},
	{"ldi", 3, (7), (6), (1), 10, 25, "load index", 2, 2},
	{"sti", 3, (1), (7), (6), 11, 25, "store index", 2, 2},
	{"fork", 1, (2), (0), (0), 12, 800, "fork", 1, 2},
	{"lld", 2, (4), (1), (0), 13, 10, "long load", 2, 4},
	{"lldi", 3, (7), (6), (1), 14, 50, "long load index", 2, 2},
	{"lfork", 1, (2), (0), (0), 15, 1000, "long fork", 1, 2},
	{"aff", 1, (1), (0), (0), 16, 2, "aff", 2, 4},
	{0, 0, (0), (0), (0), 0, 0, 0, 0, 0}
};

static void		fill_op(t_i_j *name_i_j)
{
	g_num_str = 0;
	g_arg_num = 0;
	init_i_j(name_i_j);
}

static void		check_bynary(char *file_name)
{
	int			fd;
	char		*str;
	int			i;
	int			ret;

	bad_file(&ret, &fd, &str, file_name);
	while (ret > 0)
	{
		str[ret] = '\0';
		i = -1;
		while (str && ++i < ret)
			if ((str[i] < 32 || str[i] > 127 || (!str[i] && i != ret))\
			&& str[i] != '\t' && str[i] != '\n')
			{
				free(str);
				ft_printf("%&Binary file,sorry\n", 2);
				error_exit_with_sound(-1);
			}
		free(str);
		str = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
		ret = read(fd, str, BUFF_SIZE);
	}
	ft_memdel((void **)&str);
	close(fd);
}

static void		check_n_c_num(char *file_name, t_all_data **obj_all)
{
	int			fd;
	char		*str;
	t_i_j		name_i_j;

	name_i_j.name_is_set = 0;
	name_i_j.comm_is_set = 0;
	fd = open(file_name, O_RDONLY);
	if (!(*obj_all = NULL) && fd < 0)
		return ;
	while (get_next_line(fd, &str) != 0)
	{
		if (str == NULL)
			continue ;
		check_if_dir(str, fd);
		(!ft_strncmp(str, ".name", 5)) ? name_i_j.name_is_set++ : 0;
		(!ft_strncmp(str, ".comment", 8)) ? name_i_j.comm_is_set++ : 0;
		*obj_all = add_all_data(init_all_data(str), *obj_all);
	}
	if (name_i_j.name_is_set > 1 || name_i_j.comm_is_set > 1)
	{
		ft_printf("%&Too many names or comments\n", 2);
		free_all_data(*obj_all);
		error_exit_with_sound(-1);
	}
	close(fd);
}

static int		main_help(t_i_j *name_i_j, int argc,\
char **argv, t_all_data **obj_all)
{
	fill_op(name_i_j);
	name_i_j->file = argv[1];
	if (argc != 2 && argc != 4)
	{
		ft_printf("%&Usage ./asm filename [-a] [directory]\n", 2);
		ft_printf("%&\t-a : creating a file in select directory.\n", 2);
		return (0);
	}
	if (argc == 4)
		parse_direct(name_i_j, argv);
	check_bynary(argv[1]);
	check_n_c_num(argv[1], obj_all);
	return (1);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_i_j		name_i_j;
	t_command	*command;
	t_all_data	*obj_all;

	fd = 0;
	if (!main_help(&name_i_j, argc, argv, &obj_all))
		return (1);
	fd = check_open_champ_file(argv[1], fd);
	if (!be_valid_dude(fd, &command, &name_i_j))
	{
		ft_printf("%&Error\n", 2);
		error_exit_with_sound(-1);
	}
	make_evil_warrior(command, name_i_j.file, name_i_j.name, name_i_j.comment);
	print_all_data_free(obj_all);
	free_all_structs(command);
	close(fd);
	system("say 'The bot compilation is successful'");
	return (0);
}
