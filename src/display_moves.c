/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:51:16 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/28 14:59:08 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	init_moves(t_data *data)
{
	data->moves_location = ft_pointnew(data->map->width - 1, data->map->height
			- 1);
	if (!data->moves_location)
		print_error_exit("Memory allocation failed", NULL, data);
}

void	render_moves(t_data *data)
{
	int	moves;

	moves = data->moves;
	if (moves == 0)
		render_img(data, data->imgs[num0], data->moves_location, 0);
	while (moves > 0)
	{
		render_img(data, data->imgs[num0 + (moves % 10)], data->moves_location,
			0);
		data->moves_location->x--;
		moves /= 10;
	}
	data->moves_location->x = data->map->width - 1;
}
