/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_11_sti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:22:16 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:40:00 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sti(t_data *data, t_process *process)
{
	t_byte		*val1;
	t_byte		*val2;
	t_byte		*val3;
	int			dest;

	if (INCORRECT_REG_NUM(REG_NUM(process, 0)))
		return ;
	val1 = VALUE(process, 0);
	val2 = TYPE(process, 0) == IND_CODE ? VALUE_IDX(process, 1) :
											VALUE(process, 1);
	val3 = VALUE(process, 2);
	dest = get_number(val2, SIZE(process, 1)) +
			get_number(val3, SIZE(process, 2));
	dest %= IDX_MOD;
	dest = process->pc + dest;
	write_arena_chunk(data, val1, dest, REG_SIZE);
	if (V_FLAG)
		update_color_map(data, process->champion, dest, REG_SIZE);
}
