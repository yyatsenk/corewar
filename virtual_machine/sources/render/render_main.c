/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:50:38 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 15:09:19 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

WINDOW	*create_new_window(int height, int width, int start_y, int start_x)
{
	WINDOW *local_win;

	local_win = newwin(height, width, start_y, start_x);
	refresh();
	wattron(local_win, COLOR_PAIR(42) | A_DIM);
	box(local_win, BORDER_VER, BORDER_HOR);
	wattroff(local_win, COLOR_PAIR(42) | A_DIM);
	wrefresh(local_win);
	return (local_win);
}

void	render_winner(t_data *data)
{
	WINDOW *s_win;
	size_t winner;

	render_side_bar(data);
	winner = announce_the_winner(data);
	s_win = data->render.side_win;
	mvwprintw(s_win, WINNER_Y_OFFSET, WINNER_X_OFFSET, "The winner is: ");
	wattron(s_win, COLOR_PAIR(winner + 1));
	wprintw(s_win, "%.34s", data->players[winner].name);
	wattroff(s_win, COLOR_PAIR(winner + 1));
	mvwprintw(s_win, WINNER_Y_OFFSET + 2, WINNER_X_OFFSET,
				"Press any key to finish");
	wrefresh(data->render.side_win);
	wgetch(s_win);
}

void	init_start_window(t_data *data)
{
	data->render.main_win = initscr();
	curs_set(0);
	init_colors();
	noecho();
	data->render.speed = 50;
	data->render.paused = 1;
	render_side_bar(data);
	render_arena_win(data);
}

int		render_game(t_data *data)
{
	int c;

	init_start_window(data);
	set_speed(data);
	while (1)
	{
		if (INTERACTIVE)
			handle_interactive_mode(data);
		if (!play_corewar(data))
			break ;
		if (!INTERACTIVE)
		{
			timeout(1000 / ((data->render.speed) * 1.4));
			if ((c = getch()) == ' ')
				set_speed(data);
		}
	}
	render_winner(data);
	delwin(data->render.arena_win);
	delwin(data->render.side_win);
	endwin();
	return (0);
}
