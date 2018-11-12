/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_bar_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:20:20 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 15:20:19 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	render_speed_data(t_data *data)
{
	if (!SPEED_WIN)
	{
		SPEED_WIN = subwin(data->render.side_win,
								SPEED_WIN_HEIGHT, SPEED_WIN_WIDTH,
								SPEED_Y_OFFSET, SPEED_X_OFFSET);
		wrefresh(data->render.side_win);
	}
	if (INTERACTIVE)
		mvwprintw(SPEED_WIN, 0, 0, "** INTERACTIVE MODE **");
	else
	{
		if (data->render.paused)
			mvwprintw(SPEED_WIN, 0, 0, "     ** PAUSED **     ");
		if (!data->render.paused)
			mvwprintw(SPEED_WIN, 0, 0, "     ** RUNNING **    ");
	}
	mvwprintw(SPEED_WIN, 2, 0, "Max Speed: %4i cycle/second",
				data->render.speed);
	touchwin(SPEED_WIN);
	wrefresh(SPEED_WIN);
}

void	render_cycle_data(t_data *data)
{
	if (!CYCLE_WIN)
	{
		CYCLE_WIN = subwin(data->render.side_win,
										CYCLE_WIN_HEIGHT, CYCLE_WIN_WIDTH,
										CYCLE_Y_OFFSET, CYCLE_X_OFFSET);
		wrefresh(data->render.side_win);
	}
	mvwprintw(CYCLE_WIN, 0, 0, "Cycle:\t\t%zu", data->cycle);
	mvwprintw(CYCLE_WIN, 2, 0, "Processes:\t%zu", data->process_qty);
	mvwprintw(CYCLE_WIN, 4, 0, "Total lives:                    ");
	mvwprintw(CYCLE_WIN, 4, 0, "Total lives:\t%zu", data->total_lives);
	touchwin(CYCLE_WIN);
	wrefresh(CYCLE_WIN);
}

void	render_players_data(t_data *data)
{
	size_t	i;

	if (!PLAYER_WIN)
	{
		PLAYER_WIN = subwin(data->render.side_win,
		PLAYER_WIN_HEIGHT, PLAYER_WIN_WIDTH, PLAYER_Y_OFFSET, PLAYER_X_OFFSET);
		wrefresh(data->render.side_win);
	}
	i = 0;
	while (i < data->players_qty)
	{
		mvwprintw(PLAYER_WIN, i * 4, 0, "Player %i: ",
				data->players[i].signature);
		wattron(PLAYER_WIN, COLOR_PAIR(i + 1));
		wprintw(PLAYER_WIN, "%.38s", data->players[i].name);
		wattroff(PLAYER_WIN, COLOR_PAIR(i + 1));
		mvwprintw(PLAYER_WIN, i * 4 + 1, 4, "Last live:\t\t\t%4i",
			data->players[i].last_live);
		mvwprintw(PLAYER_WIN, i * 4 + 2, 4,
				"Lives in current period:\t%4i", data->players[i].live);
		i++;
	}
	touchwin(PLAYER_WIN);
	wrefresh(PLAYER_WIN);
}

void	render_parameters(t_data *data)
{
	if (!PARAM_WIN)
	{
		PARAM_WIN = subwin(data->render.side_win,
										PARAM_WIN_HEIGHT, PARAM_WIN_WIDTH,
										PARAM_Y_OFFSET, PARAM_X_OFFSET);
		wrefresh(data->render.side_win);
	}
	mvwprintw(PARAM_WIN, 0, 0, "CYCLE_TO_DIE:\t%4i", data->cycle_to_die);
	mvwprintw(PARAM_WIN, 2, 0, "CYCLE_DELTA:\t%4i", CYCLE_DELTA);
	mvwprintw(PARAM_WIN, 4, 0, "NBR_LIVE:\t%4i", NBR_LIVE);
	mvwprintw(PARAM_WIN, 6, 0, "MAX_CHECKS:\t%4i", MAX_CHECKS);
	touchwin(PARAM_WIN);
	wrefresh(PARAM_WIN);
}

void	render_side_bar(t_data *data)
{
	if (!data->render.side_win)
		data->render.side_win = create_new_window(SIDE_WIN_HEIGHT,
					SIDE_WIN_WIDTH, SIDE_Y_OFFSET, SIDE_X_OFFSET);
	wattron(data->render.side_win, A_BOLD);
	render_speed_data(data);
	render_cycle_data(data);
	render_players_data(data);
	render_parameters(data);
	wrefresh(data->render.side_win);
}
