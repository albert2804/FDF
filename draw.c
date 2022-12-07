/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:10:46 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/07 11:30:30 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_image(mlx_image_t *g_img, t_readmap *map_data, t_trans *transform)
{
	int		x;
	int		y;
	size_t	node;

	node = 0;
	while (node < map_data->total_count)
	{
		x = transform->b_x[node];
		y = transform->b_y[node];
		ft_putpixel(g_img, x, y, get_rgba(255, 255, 255, 255));
		node ++;
	}
	determine_center(map_data);
	x = map_data->center_x;
	y = map_data->center_y;
	ft_putpixel(g_img, x, y, get_rgba(255, 255, 255, 255));
	draw_grid(map_data, transform, g_img);
}

/**
 * draws horizontal gridlines for one row
 * @param node represents the nodenumber of startpoint
*/
void	hor_line(size_t node, t_readmap *map_data, mlx_image_t *g_img, t_trans *trans)
{
	size_t	x0;
	size_t	y0;
	size_t	x1;
	size_t	y1;
	size_t	counter;

	x0 = 0;
	y0 = 0;
	x1 = 0;
	y1 = 0;
	counter = 0;
	while(counter < map_data->count_x - 1)
	{
		x0 = trans->b_x[node];
		y0 = trans->b_y[node];
		x1 = trans->b_x[node + 1];
		y1 = trans->b_y[node + 1];
		bresenham(g_img, x0, x1, y0, y1);
		node ++;
		counter ++;
	}
}
/**
 * draws vertical gridlines for one column
 * @param node represents the nodenumber of startpoint
*/
void	ver_line(size_t node, t_readmap *map_data, mlx_image_t *g_img, t_trans *trans)
{
	size_t	x0;
	size_t	y0;
	size_t	x1;
	size_t	y1;
	size_t	counter;

	x0 = 0;
	y0 = 0;
	x1 = 0;
	y1 = 0;
	counter = 0;
	while(counter < map_data->count_y - 1)
	{
		x0 = trans->b_x[node];
		y0 = trans->b_y[node];
		x1 = trans->b_x[node + map_data->count_x];
		y1 = trans->b_y[node + map_data->count_x];
		bresenham(g_img, x0, x1, y0, y1);
		node += map_data->count_x;
		counter ++;
	}
}
/**
 * draws a grid, first all horizontal lines, afterwards all vertical lines
*/
void draw_grid(t_readmap *map_data, t_trans *transform, mlx_image_t *g_img)
{
	size_t	node;
	
	node = 0;
	while (node <= map_data->total_count - map_data->count_y)
	{
		hor_line(node, map_data, g_img, transform);
		node += map_data->count_x;
	}
	node = 0;
	while (node < map_data->count_x)
	{
		ver_line(node, map_data, g_img, transform);
		node ++;
	}
}
