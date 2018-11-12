/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_15_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:08:36 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:40:49 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Creates a new process, that inherits all parameters
**	from the parent process, except pc.
**	Puts new cursor on new pc, wich is input argument.
**	The same as fork, bbut without % IDX_MOD.
*/

void	lfork_cor(t_data *data, t_process *process)
{
	t_list		*new_node;
	t_process	new_process;
	short		pc;

	new_process = *process;
	ft_bzero(&new_process.oper, sizeof(t_oper));
	pc = get_short_number(VALUE(process, 0));
	pc += process->pc;
	pc = normalize_index(pc);
	new_process.pc = pc;
	data->render.pc_map[pc]++;
	let_new_process_play(data, &new_process);
	new_node = ft_lstnew(&new_process, sizeof(t_process));
	if (!new_node)
		error_msg(MEM_ERROR, NULL);
	ft_lstadd(&data->processes, new_node);
	data->process_qty = ft_lstlen(data->processes);
}
