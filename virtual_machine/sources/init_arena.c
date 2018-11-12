/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:23:55 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:51:28 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Sets player`s execution code to arena.
*/

void	init_arena(t_data *data)
{
	t_list	*track;
	size_t	pc;
	size_t	i;
	char	*exec_code;
	int		size;

	data->cycle_to_die = CYCLE_TO_DIE;
	data->live_checks = MAX_CHECKS;
	track = data->processes;
	i = data->players_qty - 1;
	ft_memset(data->render.color_map, 43, MEM_SIZE);
	while (track)
	{
		pc = ((t_process *)track->content)->pc;
		exec_code = data->players[i].exec_code;
		size = data->players[i].exec_code_size;
		ft_memcpy(&(data->arena[pc]), exec_code, size);
		ft_memset(&(data->render.color_map[pc]), data->players[i].number, size);
		track = track->next;
		i--;
	}
}
