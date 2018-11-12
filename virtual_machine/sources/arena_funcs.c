/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 23:56:31 by maks              #+#    #+#             */
/*   Updated: 2018/06/01 13:48:44 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Reads some peace of arena memory.
**	start - index of arena, where reading should begin.
**	n - size of data, that should be written.
**	Implements the idea of cycled memory
**	For exmaple: 	arena[-2] => arena[4094]
**					arena[4098] => arena[2]
*/

t_byte	*read_arena_chunk(t_data *data, t_byte *dest, int start, size_t n)
{
	size_t	i;
	int		index;

	i = 0;
	while (i < n)
	{
		index = normalize_index(start);
		dest[i] = data->arena[index];
		start++;
		i++;
	}
	return (dest);
}

/*
**	Writes some data to arena
**	start - index of arena, where writing should begin.
**	n - size of data, that should be written.
*/

void	write_arena_chunk(t_data *data, t_byte *src, int start, size_t n)
{
	size_t	i;
	int		index;

	i = 0;
	while (i < n)
	{
		index = normalize_index(start);
		data->arena[index] = src[i];
		start++;
		i++;
	}
}

/*
**	Set to zero live of every process and players as well as total live.
*/

void	set_lives_to_zero(t_data *data)
{
	t_list	*track;
	size_t	i;

	data->total_lives = 0;
	i = 0;
	while (i < data->players_qty)
		data->players[i++].live = 0;
	track = data->processes;
	while (track)
	{
		LIVE(track) = 0;
		track = track->next;
	}
}
