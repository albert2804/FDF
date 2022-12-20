/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:10:46 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/20 14:21:56 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_image(mlx_image_t *g_img, t_trans *transform)
{
	int		x;
	int		y;
	size_t	node;
	int		color;

	node = 0;
	x = 0;
	y = 0;
	(void)g_img;
	while (node < transform->map_data->total_count)
	{
		color = get_rgba(transform->map_data->rgb_values[node][0], \
						transform->map_data->rgb_values[node][1], \
						transform->map_data->rgb_values[node][2], 255);
		x = transform->b_x[node];
		y = transform->b_y[node];
		ft_putpixel(x, y, color, transform);
		node ++;
	}
	draw_grid(transform, g_img);
}

/**
 * draws horizontal gridlines for one row
 * @param node represents the nodenumber of startpoint
*/
void	hor_line(size_t node, mlx_image_t *g_img, t_trans *trans)
{
	size_t	counter;
	int		n_pixel;

	counter = 0;
	n_pixel = 0;
	(void)g_img;
	while (counter < trans->map_data->count_x - 1)
	{
		n_pixel = sqrt(pow(abs(trans->b_x[node] - trans->b_x[node + 1]), 2) \
				+ pow(abs(trans->b_y[node] - trans->b_y[node + 1]), 2));
		bresenham(node, node + 1, n_pixel, trans);
		node ++;
		counter ++;
	}
}

/**
 * draws vertical gridlines for one column
 * @param node represents the nodenumber of startpoint
*/
void	ver_line(size_t node, mlx_image_t *g_img, t_trans *trans)
{
	size_t	counter;
	int		n_pixel;

	counter = 0;
	n_pixel = 0;
	(void)g_img;
	while (counter < trans->map_data->count_y - 1)
	{
		n_pixel = sqrt(pow(abs(trans->b_x[node] - trans->b_x[node \
		+ trans->map_data->count_x]), 2) \
		+ pow(abs(trans->b_y[node] - trans->b_y[node \
		+ trans->map_data->count_x]), 2));
		bresenham(node, node + trans->map_data->count_x, n_pixel, trans);
		node += trans->map_data->count_x;
		counter ++;
	}
}

/**
 * draws a grid, first all horizontal lines, afterwards all vertical lines
*/
void	draw_grid(t_trans *transform, mlx_image_t *g_img)
{
	size_t	node;
	size_t	total_count;
	size_t	count_x;
	size_t	count_y;

	total_count = transform->map_data->total_count;
	count_x = transform->map_data->count_x;
	count_y = transform->map_data->count_y;
	node = 0;
	while (node <= total_count - count_x)
	{
		hor_line(node, g_img, transform);
		node += count_x;
	}
	node = 0;
	while (node < count_x)
	{
		ver_line(node, g_img, transform);
		node ++;
	}
}

bool	ft_putpixel(uint32_t x, uint32_t y, int color, t_trans *t)
{	
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(t->img, x, y, color);
	else
		return (false);
	return (true);
}
