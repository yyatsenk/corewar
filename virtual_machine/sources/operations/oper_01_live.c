/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_01_live.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <mgayduk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 09:22:48 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 16:33:42 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	The instruction that allows a process to stay alive.
**	It can also record that the player whose number is the argument
**	is indeed alive.
*/

int		is_player_num(t_data *data, int val)
{
	size_t	i;

	i = 0;
	while (i < data->players_qty)
	{
		if (data->players[i].signature == val)
			return (i);
		i++;
	}
	return (-42);
}

void	live(t_data *data, t_process *process)
{
	int			val;
	int			p_num;

	val = get_int_number(VALUE(process, 0));
	if ((p_num = is_player_num(data, val)) != -42)
	{
		data->players[p_num].live++;
		data->players[p_num].last_live = data->cycle;
		if (V_FLAG)
		{
			data->render.live_mark[process->pc] = p_num + 11;
			data->render.brightness_map[process->pc] = data->cycle;
		}
	}
	process->live++;
	data->total_lives++;
}
