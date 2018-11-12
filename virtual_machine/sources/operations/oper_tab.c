/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <mgayduk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:55:18 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 16:35:43 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Global array, that contains instructions of Corewar
**	{op_code, name, description, codage, argc, cycles, carry, label size}
*/

const t_op	g_op_tab[OPER_QTY] =
{
	{0, NULL, NULL, 0, 0, 0, 0, 0, NULL},
	{0x01, "live", "alive", 0, 1, 10, 0, REG_SIZE, live},
	{0x02, "ld", "load", 1, 2, 5, 1, REG_SIZE, ld},
	{0x03, "st", "store", 1, 2, 5, 0, REG_SIZE, st},
	{0x04, "add", "addition", 1, 3, 10, 1, REG_SIZE, add},
	{0x05, "sub", "substruction", 1, 3, 10, 1, REG_SIZE, sub},
	{0x06, "and", "r1 & r2 -> r3", 1, 3, 6, 1, REG_SIZE, and},
	{0x07, "or", "r1 | r2 -> r3", 1, 3, 6, 1, REG_SIZE, or},
	{0x08, "xor", "r1 ^ r2 -> r3", 1, 3, 6, 1, REG_SIZE, xor},
	{0x09, "zjmp", "jump if zero", 0, 1, 20, 0, IND_SIZE, zjmp},
	{0x0A, "ldi", "load index", 1, 3, 25, 0, IND_SIZE, ldi},
	{0x0B, "sti", "store index", 1, 3, 25, 0, IND_SIZE, sti},
	{0x0C, "fork", "fork procces", 0, 1, 800, 0, IND_SIZE, fork_cor},
	{0x0D, "lld", "long load", 1, 2, 10, 1, REG_SIZE, lld},
	{0x0E, "lldi", "long load index", 1, 3, 50, 1, IND_SIZE, lldi},
	{0x0F, "lfork", "long fork", 0, 1, 1000, 0, IND_SIZE, lfork_cor},
	{0x10, "aff", "aff", 1, 1, 2, 0, REG_SIZE, aff},
	{0, NULL, NULL, 0, 0, 0, 0, 0, NULL}
};
