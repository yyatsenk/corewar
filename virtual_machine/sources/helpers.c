/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:52:05 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 16:25:39 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error_msg(char *msg, char *arg)
{
	if (arg == NULL)
		ft_printf("Error: %s\n", msg);
	else
	{
		ft_printf("Error: ");
		ft_printf(msg, arg);
		ft_printf("\n");
	}
	exit(1);
}

void	dump_arena(t_data *data)
{
	size_t	i;

	ft_printf("\n\t\t\t\t\t\t~~~ MEMORY DUMP ~~~\t\t\tcycle: %u\n\n",
				data->cycle);
	i = 0;
	ft_printf("\t");
	while (i < DUMP_SIZE)
		ft_printf("%2i ", i++);
	ft_printf("\n\t-----------------------------------------------");
	ft_printf("------------------------------------------------\n");
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % DUMP_SIZE == 0)
			ft_printf("%i\t", i / DUMP_SIZE);
		ft_printf("%02hhx", data->arena[i]);
		i++;
		ft_printf(" ");
		if (i % DUMP_SIZE == 0)
			ft_printf("\n");
	}
	exit(1);
}

void	print_usage(void)
{
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("Usage: ./corewar [champ-file]\n");
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("minimun number of champions 1\n");
	ft_printf("maximum number of champions 4\n\n");
	ft_printf("Additional flags:\n");
	ft_printf("    -dump [n] - prints memory dump of the game on n cycle\n\n");
	ft_printf("*---                                                   ---*\n");
	ft_printf("|   -v - turns on visualization:                          |\n");
	ft_printf("|        Visualistion controls:                           |\n");
	ft_printf("\n");
	ft_printf("         i - interactive step by step mode\n\n");
	ft_printf("         space - run / pause the game\n\n");
	ft_printf("         When the game pused it`s speed can be change:\n");
	ft_printf("            s - reduce speed for 100 cycles/second\n");
	ft_printf("            q - reduce speed for 10 cycles/second\n");
	ft_printf("            w - reduce speed for 1 cycles/second\n");
	ft_printf("            r - increase speed for 1 cycles/second\n");
	ft_printf("|           t - increase speed for 10 cycles/second       |\n");
	ft_printf("|           d - increase speed for 100 cycles/second      |\n");
	ft_printf("*---                                                   ---*\n");
	exit(1);
}
