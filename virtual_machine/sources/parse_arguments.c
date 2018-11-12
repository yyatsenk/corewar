/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:48:33 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 14:10:25 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_next_available_argument(t_process *process)
{
	int i;

	i = 0;
	while (USED(process, i))
		i++;
	return (i);
}

static void		read_register(t_data *data, int *padding, t_process *process)
{
	int i;
	int reg_num;

	if ((i = get_next_available_argument(process)) > 2)
		return ;
	(*padding)++;
	reg_num = data->arena[(process->pc + *padding) % MEM_SIZE];
	REG_NUM(process, i) = reg_num;
	SIZE(process, i) = REG_SIZE;
	TYPE(process, i) = REG_CODE;
	USED(process, i) = 1;
	if (INCORRECT_REG_NUM(reg_num))
		return ;
	ft_memcpy(VALUE(process, i), process->registers[reg_num], REG_SIZE);
}

static void		read_direct_value(t_data *data, int *padding,
									t_process *process)
{
	int		i;
	int		size;
	t_byte	temp[DIR_SIZE];

	if ((i = get_next_available_argument(process)) > 2)
		return ;
	(*padding)++;
	size = g_op_tab[process->oper.op_code].label_size;
	ft_bzero(temp, sizeof(temp));
	read_arena_chunk(data, temp, process->pc + *padding, size);
	if (temp[0] & 0b10000000)
		ft_memset(&VALUE(process, i), -1, DIR_SIZE);
	ft_memcpy(VALUE(process, i), temp, size);
	SIZE(process, i) = size;
	TYPE(process, i) = DIR_CODE;
	USED(process, i) = 1;
	(*padding) += size - 1;
}

void			read_indirect_value(t_data *data, int *padding,
										t_process *process)
{
	int		i;
	short	offset;
	t_byte	temp[T_IND];

	if ((i = get_next_available_argument(process)) > 2)
		return ;
	(*padding)++;
	ft_bzero(temp, sizeof(temp));
	read_arena_chunk(data, temp, process->pc + *padding, IND_SIZE);
	offset = get_short_number(temp);
	OFFSET(process, i) = offset;
	ft_bzero(temp, sizeof(temp));
	read_arena_chunk(data, temp, process->pc + offset, T_IND);
	ft_memcpy(VALUE(process, i), temp, T_IND);
	ft_bzero(temp, sizeof(temp));
	read_arena_chunk(data, temp, process->pc + (offset % IDX_MOD), T_IND);
	ft_memcpy(VALUE_IDX(process, i), temp, T_IND);
	SIZE(process, i) = REG_SIZE;
	TYPE(process, i) = IND_CODE;
	USED(process, i) = 1;
	(*padding) += IND_SIZE - 1;
}

/*
**  Parses arguments of instruction.
**  Determinates argument`s type (T_REG, T_DIR, T_IND) using codage.
**	Takes data and number of player;
**  Sets PC to the next instruction.
*/

void			parse_arguments(t_data *data, t_process *process)
{
	int		args_num;
	int		k;
	int		padding;
	t_byte	codage;

	padding = g_op_tab[process->oper.op_code].codage ? 1 : 0;
	if (!g_op_tab[process->oper.op_code].codage)
		read_direct_value(data, &padding, process);
	else
	{
		args_num = g_op_tab[process->oper.op_code].args_num;
		codage = data->arena[(process->pc + padding) % MEM_SIZE];
		while (args_num--)
		{
			k = (codage & 0b11000000) >> 6;
			if (k == REG_CODE)
				read_register(data, &padding, process);
			else if (k == DIR_CODE)
				read_direct_value(data, &padding, process);
			else if (k == IND_CODE)
				read_indirect_value(data, &padding, process);
			codage = codage << 2;
		}
	}
	process->padding = padding + 1;
}
