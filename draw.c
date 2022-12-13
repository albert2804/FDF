/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:10:46 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/13 16:02:13 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_image(mlx_image_t *g_img, t_trans *transform)
{
	int		x;
	int		y;
	size_t	node;

	node = 0;
	x = 0;
	y = 0;
	//(void)g_img;
	while (node < transform->map_data->total_count)
	{
		x = transform->b_x[node];
		y = transform->b_y[node];
		ft_putpixel2(node, transform, x, y);
		//ft_putpixel(g_img, x, y, get_rgba(255, 255, 255, 255));
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
	while (counter < trans->map_data->count_x - 1)
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
void	ver_line(size_t node, mlx_image_t *g_img, t_trans *trans)
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
	while (counter < trans->map_data->count_y - 1)
	{
		x0 = trans->b_x[node];
		y0 = trans->b_y[node];
		x1 = trans->b_x[node + trans->map_data->count_x];
		y1 = trans->b_y[node + trans->map_data->count_x];
		bresenham(g_img, x0, x1, y0, y1);
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

void	ft_putpixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

void	ft_putpixel2(size_t node, t_trans *t, int x, int y)
{
	int			*rgb;
	int			color;
	mlx_image_t	*image;
	
	image = t->img;
	rgb = t->map_data->rgb_values[node];
	color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}