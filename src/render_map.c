/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:40:44 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/27 16:02:33 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_wall(t_data *data, int x, int y);
static void	render_ground(t_data *data, int x, int y);

void	render_map(t_data *data)
{
	t_map	*map;
	int		y;
	int		x;
	char	c;

	map = data->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c == '1')
				render_wall(data, x, y);
			else
				render_ground(data, x, y);
			x++;
		}
		y++;
	}
}

static void	render_wall(t_data *data, int x, int y)
{
	t_map	*map;

	map = data->map;
	render_tile(data, wall, x, y);
	if (y == 0)
		render_tile(data, wall, x, y);
	if (y == map->height - 1)
		render_tile(data, bottom_wall, x, y);
	if (x == 0)
		render_tile(data, left_wall, x, y);
	if (x == map->width - 1)
		render_tile(data, right_wall, x, y);
	if (y == 0 && x == 0)
		render_tile(data, top_left_wall, x, y);
	if (y == 0 && x == map->width - 1)
		render_tile(data, top_right_wall, x, y);
	if (y == map->height - 1 && x == 0)
		render_tile(data, bottom_left_wall, x, y);
	if (y == map->height - 1 && x == map->width - 1)
		render_tile(data, bottom_right_wall, x, y);
}

static void	render_ground(t_data *data, int x, int y)
{
	char	**map;

	map = data->map->grid;
	if (map[y][x] == 'P')
		render_tile(data, start, x, y);
	else
		render_tile(data, ground, x, y);
}
