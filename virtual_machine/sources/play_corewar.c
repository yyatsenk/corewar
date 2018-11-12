/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:43:30 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/10 09:35:03 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	compute_pc(t_data *data, t_process *process, int steps)
{
	data->render.pc_map[process->pc]--;
	process->pc = normalize_index(process->pc + steps);
	data->render.pc_map[process->pc]++;
	if (V_FLAG)
		render_arena(data);
}

void	execute_instruction(t_data *data, t_list *track)
{
	t_process *test;

	test = track->content;
	parse_arguments(data, track->content);
	g_op_tab[OPCODE(track)].action(data, track->content);
	if (OPCODE(track) != 9 || !CARRY(track))
		compute_pc(data, track->content, PADDING(track));
	if (V_FLAG)
		render_arena(data);
	if (V_FLAG && OPCODE(track) == 1)
		render_players_data(data);
	ft_bzero(&GET_OPERATION(track), sizeof(t_oper));
}

/*
**	Goes through each process.
**	Reads instructions and it`s arguments then execute them.
** 	Compute delay and pc.
*/

void	compute_instructions(t_data *data)
{
	t_list	*track;

	track = data->processes;
	while (track)
	{
		if (!OPCODE(track) && !IS_OPCODE(PC_VAL(track)))
			compute_pc(data, track->content, 1);
		if (OPCODE(track) && DELAY(track) == 0)
			execute_instruction(data, track);
		if (!OPCODE(track) && IS_OPCODE(PC_VAL(track)))
		{
			OPCODE(track) = PC_VAL(track);
			DELAY(track) = g_op_tab[OPCODE(track)].delay;
		}
		if (DELAY(track))
			DELAY(track)--;
		track = track->next;
	}
}

/*
**	Reduces cycle_to_die.
*/

void	handle_cycle(t_data *data)
{
	data->counter = 0;
	if (data->total_lives >= NBR_LIVE)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->live_checks = MAX_CHECKS;
	}
	else
		data->live_checks--;
	if (!data->live_checks)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->live_checks = MAX_CHECKS;
	}
}

/*
**	Main function for corewar game cycle.
*/

int		play_corewar(t_data *data)
{
	if (data->cycle_to_die <= 0)
		return (0);
	if (DUMPED && data->cycle == DUMP_VALUE && !V_FLAG)
		dump_arena(data);
	compute_instructions(data);
	if (data->counter == data->cycle_to_die)
	{
		if (!data->total_lives)
			return (0);
		handle_cycle(data);
		kill_processes(data);
		set_lives_to_zero(data);
		if (V_FLAG)
		{
			render_arena(data);
			render_side_bar(data);
		}
	}
	if (V_FLAG)
		render_cycle_data(data);
	data->cycle++;
	data->counter++;
	return (1);
}
