/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_12_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:08:36 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:44:00 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	let_new_process_play(t_data *data, t_process *process)
{
	if (IS_OPCODE(data->arena[process->pc]))
	{
		process->oper.op_code = data->arena[process->pc];
		process->oper.delay = g_op_tab[process->oper.op_code].delay - 1;
	}
}

/*
**	Creates a new process, that inherits all parameters
**	from the parent process, except pc.
**	Puts new cursor on new pc, wich is input argument.
*/

void	fork_cor(t_data *data, t_process *process)
{
	t_list		*new_node;
	t_process	new_process;
	short		new_pc;

	new_process = *process;
	ft_bzero(&new_process.oper, sizeof(t_oper));
	new_pc = get_short_number(VALUE(process, 0)) % IDX_MOD;
	new_pc += process->pc;
	new_pc = normalize_index(new_pc);
	new_process.pc = new_pc;
	data->render.pc_map[new_pc]++;
	let_new_process_play(data, &new_process);
	new_node = ft_lstnew(&new_process, sizeof(t_process));
	if (!new_node)
		error_msg(MEM_ERROR, NULL);
	ft_lstadd(&data->processes, new_node);
	data->process_qty = ft_lstlen(data->processes);
}
