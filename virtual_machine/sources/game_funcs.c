/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:26:35 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 14:59:21 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce_players(t_data *data)
{
	size_t i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < data->players_qty)
	{
		ft_printf("* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
					data->players[i].signature,
					data->players[i].exec_code_size,
					data->players[i].name,
					data->players[i].comment);
		i++;
	}
}

/*
**	Determinates which player sad live last.
**	Writes message who is winner returns number of winner.
*/

size_t	announce_the_winner(t_data *data)
{
	size_t	i;
	size_t	p_num;

	i = 1;
	p_num = 0;
	while (i < data->players_qty)
	{
		if (data->players[i].last_live > data->players[p_num].last_live)
			p_num = i;
		i++;
	}
	if (V_FLAG)
		return (p_num);
	ft_printf("Contestant %d, \" %s \", has won !\n",
				data->players[p_num].signature,
				data->players[p_num].name);
	ft_printf("The game end on %d cycle\n", data->cycle);
	return (0);
}

void	announce_killed_qty(int killed_qty)
{
	char *str;
	char buff[32];

	ft_bzero(buff, sizeof(buff));
	str = ft_itoa(killed_qty);
	ft_strcat(buff, "say ");
	ft_strcat(buff, str);
	if (killed_qty == 1)
		ft_strcat(buff, " process was killed &");
	else
		ft_strcat(buff, " processes were killed &");
	system(buff);
	ft_strdel(&str);
}
