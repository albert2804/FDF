/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:27 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/20 14:54:16 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/**
 * frees one double and one single pointer
 * @param dbl represents the double pointer, e.g from split or values_matrix
 * @param sgl represents soingle pointer like one line or string
 * @param c	represents the count variable
 * needs a typecast since the function takes void as an input parameter.
*/
void	fr_dblsgl_p(void **dbl, void *sgl, size_t c)
{
	size_t	i;

	if (!dbl && !sgl)
		return ;
	i = 0;
	while (i < c)
		free(dbl[i++]);
	free(dbl);
	if (sgl != NULL)
		free(sgl);
}

/**
 * determines the distance beweteen Nodes in x and y direction. 
 * and offset in x and y direction. First it has to check if the 
 * Map is wider or higher.
*/
void	determine_delta(t_readmap *map_data)
{
	int	rahmen_x;
	int	rahmen_y;

	rahmen_x = 200;
	rahmen_y = 200;
	if (map_data->count_x >= map_data->count_y)
	{
		map_data->delta = (WIDTH - rahmen_x) / (map_data->count_x - 1);
		map_data->offset_x = rahmen_x / 2;
		rahmen_y = HEIGHT - ((map_data->count_y - 1) * map_data->delta);
		map_data->offset_y = rahmen_y / 2;
	}
	else if (map_data->count_y > map_data->count_x)
	{
		map_data->delta = (HEIGHT - rahmen_y) / (map_data->count_y - 1);
		map_data->offset_y = rahmen_y / 2;
		rahmen_x = WIDTH - ((map_data->count_x - 1) * map_data->delta);
		map_data->offset_x = rahmen_x / 2;
	}
}

/**
 * bresenham from wikipedia
*/
void	bresenham(size_t node0, size_t node1, int n_pixel, t_trans *t)
{
	int	*rgb0;
	int	*rgb1;
	int	gr[3];
	int	i;
	//int	arr[10];
	
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	i = 0;
	x0 = t->b_x[node0];
	x1 = t->b_x[node1];
	y0 = t->b_y[node0];
	y1 = t->b_y[node1];
	rgb0 = t->map_data->rgb_values[node0];
	rgb1 = t->map_data->rgb_values[node1];
	n_pixel = n_pixel + 1;
	gr[0] = (rgb1[0] - rgb0[0]) / n_pixel;
	gr[1] = (rgb1[1] - rgb0[1]) / n_pixel;
	gr[2] = (rgb1[2] - rgb0[2]) / n_pixel;
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	error = dx + dy;
	while (true)
	{
		i ++;
		if ((x0 == x1 && y0 == y1) \
		|| (!ft_putpixel(x0, y0, get_rgba(rgb0[0] + (gr[0] * i), \
			rgb0[1] + (gr[1] * i), rgb0[2] + (gr[2] * i), 255), t)))
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break ;
			error = error + dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break ;
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}

/**
 * Initializes Map into isometric depiction
*/
void	init_map(char *map_name, t_readmap *map_data, t_trans *transform)
{
	get_map_information(map_name, map_data);
	transform->b_x = ft_calloc(sizeof(int), map_data->total_count);
	transform->b_y = ft_calloc(sizeof(int), map_data->total_count);
	transform->map_data = map_data;
	transform->matrix = map_data->values_matrix;
	transform->ex = 600;
	transform->ey = 600;
	transform->ez = 600;
	transform->cx = 600;
	transform->cy = 600;
	transform->cz = 0;
	transform->zoom = 1.5;
	transform->alpha = 55 + 90;
	transform->beta = 0 + 180;
	transform->gamma = -45 + 180;
	transform->color_gradient = 1;
	transform->perspective_projection = 0;
	transform->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!transform->mlx)
		exit(EXIT_FAILURE);
	transform->img = mlx_new_image(transform->mlx, WIDTH, HEIGHT);
}

void	init_perspective(t_trans *transform, mlx_image_t *g_img)
{
	if (transform->perspective_projection == 0)
	{
		transform->perspective_projection = 1;
		transform->cx = 1800;
		transform->cy = 1500;
		transform->cz = -2500;
		transform->zoom = 0.5;
		transform->alpha = 215;
		transform->beta = 180;
		transform->gamma = 130;
	}
	else if (transform->perspective_projection == 1)
	{
		transform->perspective_projection = 0;
		transform->cx = 600;
		transform->cy = 600;
		transform->ey = 600;
		transform->cz = 0;
		transform->zoom = 1.5;
		transform->alpha = 55 + 90;
		transform->beta = 0 + 180;
		transform->gamma = -45 + 180;
	}	
	make_new_image(transform, g_img);
}
