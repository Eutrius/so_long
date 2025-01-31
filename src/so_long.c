/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:12:38 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/27 22:14:51 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	static t_data	data;

	if (argc == 2)
	{
		init_data(&data, argv[1]);
		render_all(&data);
		hooks(&data);
		mlx_loop(data.process);
	}
	return (0);
}
