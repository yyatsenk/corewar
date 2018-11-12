/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:27:51 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 14:40:06 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	parse_dump(t_data *data, char *d_arg, size_t *arg_num)
{
	if (!d_arg)
		error_msg("dump value wasn`t specified", NULL);
	if (!ft_is_number(d_arg))
		error_msg("dump value should be non-negative number", NULL);
	data->input_params.dump_value = ft_atoi(d_arg);
	if (data->input_params.dump_value < 0)
		error_msg("dump value should be non-negative number", NULL);
	data->input_params.dump = 1;
	(*arg_num)++;
}

/*
**	Every player should have unique number. This functions checks it.
*/

static void	check_uniqueness(t_data *data, int number)
{
	size_t	i;

	i = 0;
	while (i < MAX_PLAYERS && data->input_params.players_info[i].used)
	{
		if (data->input_params.players_info[i].signature == number)
			error_msg("player with the same number is already exist", NULL);
		i++;
	}
}

static void	parse_player_info(t_data *data, char **p_args, size_t *arg_num)
{
	size_t	i;
	int		number;

	if (!p_args[0] || !p_args[1])
		error_msg("some parameter is missing", NULL);
	if (!ft_is_number(p_args[0]))
		error_msg("player number should be numeric", NULL);
	i = 0;
	while (data->input_params.players_info[i].used)
		i++;
	data->input_params.players_info[i].file_path = p_args[1];
	number = ft_atoi(p_args[0]);
	check_uniqueness(data, number);
	data->input_params.players_info[i].signature = number;
	data->input_params.players_info[i].used = 1;
	*arg_num += 2;
}

/*
**	If player`s number was not specified it should be computed.
**	number of new player = number of previous player + 1.
*/

static void	compute_player_info(t_data *data, char *file_path)
{
	size_t	i;
	int		number;

	i = 0;
	while (data->input_params.players_info[i].used)
		i++;
	data->input_params.players_info[i].file_path = file_path;
	if (i == 0)
		number = 1;
	else
		number = data->input_params.players_info[i - 1].signature + 1;
	check_uniqueness(data, number);
	data->input_params.players_info[i].signature = number;
	data->input_params.players_info[i].used = 1;
}

void		parse_input_params(t_data *data, char **argv)
{
	size_t	i;

	i = 0;
	data->players_qty = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-v"))
		{
			data->input_params.v = 1;
			i++;
		}
		else if (ft_strequ(argv[i], "-dump"))
			parse_dump(data, argv[++i], &i);
		else
		{
			if (data->players_qty == MAX_PLAYERS)
				error_msg("limit of players is exceeded", NULL);
			if (ft_strequ(argv[i], "-n"))
				parse_player_info(data, &(argv[++i]), &i);
			else
				compute_player_info(data, argv[i++]);
			data->players_qty++;
		}
	}
}
