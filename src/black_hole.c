/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_hole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:35:40 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 17:22:48 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static void	render_with_offset(t_data *data, t_img *img, t_point *location,
				t_point *offset);
static void	destroy_wall(char **map, t_point *location);
static void	get_dir(t_point *b_loc, t_point *p_loc, t_point *offset);
static void	animate_black_hole(t_data *data);

void	render_black_hole(t_data *data)
{
	static int		curr_offset;
	static t_point	direction;
	static t_point	offset;
	t_entity		*black_hole;

	if (data->moves < 3)
		return ;
	black_hole = data->black_hole;
	if (curr_offset == 0)
		get_dir(black_hole->location, data->player->location, &direction);
	curr_offset += BH_SPEED;
	offset.x = direction.x * curr_offset;
	offset.y = direction.y * curr_offset;
	destroy_wall(data->map->grid, black_hole->location);
	render_with_offset(data, black_hole->img, black_hole->location, &offset);
	animate_black_hole(data);
	if (curr_offset == 128)
	{
		curr_offset = 0;
		black_hole->location->x += direction.x;
		black_hole->location->y += direction.y;
	}
}

static void	get_dir(t_point *b_loc, t_point *p_loc, t_point *directoin)
{
	int	x_diff;
	int	y_diff;

	x_diff = b_loc->x - p_loc->x;
	y_diff = b_loc->y - p_loc->y;
	directoin->x = 0;
	directoin->y = 0;
	if (get_abs(x_diff) >= get_abs(y_diff))
	{
		if (x_diff < 0)
			directoin->x = 1;
		else
			directoin->x = -1;
	}
	else
	{
		if (y_diff < 0)
			directoin->y = 1;
		else
			directoin->y = -1;
	}
}

static void	render_with_offset(t_data *data, t_img *img, t_point *location,
		t_point *offset)
{
	int	*img_data;
	int	y;
	int	x;
	int	color;

	img_data = (int *)mlx_get_data_addr(img->addr, &y, &y, &y);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = img_data[y * (img->width) + x];
			if (color != TRANSPARENT_COLOR)
			{
				mlx_pixel_put(data->process, data->window, (128 * location->x)
					+ x + offset->x, (128 * location->y) + y + offset->y,
					color);
			}
			x++;
		}
		y++;
	}
}

static void	animate_black_hole(t_data *data)
{
	static int	rate;
	t_entity	*black_hole;

	black_hole = data->black_hole;
	if (rate == BLACK_HOLE_FRAMERATE)
	{
		if (black_hole->img == data->imgs[blackhole1])
			black_hole->img = data->imgs[blackhole2];
		else if (black_hole->img == data->imgs[blackhole2])
			black_hole->img = data->imgs[blackhole3];
		else if (black_hole->img == data->imgs[blackhole3])
			black_hole->img = data->imgs[blackhole4];
		else if (black_hole->img == data->imgs[blackhole4])
			black_hole->img = data->imgs[blackhole5];
		else if (black_hole->img == data->imgs[blackhole5])
			black_hole->img = data->imgs[blackhole1];
		rate = 0;
	}
	rate++;
}

static void	destroy_wall(char **map, t_point *location)
{
	if (map[location->y][location->x] == '1')
		map[location->y][location->x] = '0';
}
