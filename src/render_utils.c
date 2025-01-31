/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:42:52 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 16:35:50 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

void	render_entity(t_data *data, t_entity *entity)
{
	render_img(data, entity->img, entity->location, entity->mirror);
}

void	render_img(t_data *data, t_img *img, t_point *location, int mirror)
{
	int	*img_data;
	int	translate_x;
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
				translate_x = x + (mirror * (img->width - 1 - x - x));
				mlx_pixel_put(data->process, data->window, (128 * location->x)
					+ translate_x, (128 * location->y) + y, color);
			}
			x++;
		}
		y++;
	}
}

void	render_tile(t_data *data, t_imgname name, int x, int y)
{
	t_img	*img;
	int		index;

	index = name;
	img = data->imgs[index];
	mlx_put_image_to_window(data->process, data->window, img->addr, x
		* (img->width), y * (img->height));
}

void	render_explosion(t_data *data)
{
	int	i;

	i = 0;
	if (!data->explosion)
		return ;
	while (i < EXPLOSION_FRAMERATE)
	{
		if (i == 0)
			render_img(data, data->imgs[explosion1], data->explosion, 0);
		if (i == EXPLOSION_FRAMERATE / 3)
			render_img(data, data->imgs[explosion2], data->explosion, 0);
		if (i == EXPLOSION_FRAMERATE - EXPLOSION_FRAMERATE / 8)
			render_img(data, data->imgs[explosion3], data->explosion, 0);
		i++;
	}
	free(data->explosion);
	data->explosion = NULL;
}

int	get_abs(int num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}
