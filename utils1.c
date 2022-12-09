/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:27 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/09 11:49:24 by aestraic         ###   ########.fr       */
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

	if (!dbl || !sgl)
		return ;
	i = 0;
	while (i < c)
		free(dbl[i++]);
	free(dbl);
	if (sgl != NULL)
		free(sgl);
}

int	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * finds the maximum number within an size_t array and stores it in 
 * the map_data struct
 * 
 * ----->!!!NEEDS to be IMPROVED, only works for positive numbers!!!
 * 
*/
void	find_max_nbr(size_t *array, t_readmap *map_data)
{
	size_t	i;
	size_t	max_value;

	i = 0;
	max_value = array[i];
	if (array == NULL)
		max_value = -1;
	while (array[i] != 0)
	{
		if (array[i] > max_value)
			max_value = array[i];
		i ++;
	}
	map_data->max_xy = max_value;
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
		map_data->delta = (WIDTH - rahmen_x)/ (map_data->count_x - 1);
		map_data->offset_x = rahmen_x/ 2;
		rahmen_y = HEIGHT - ((map_data->count_y - 1) * map_data->delta);
		map_data->offset_y = rahmen_y/ 2;
	}
	else if (map_data->count_y > map_data->count_x)
	{
		map_data->delta = (HEIGHT - rahmen_y)/ (map_data->count_y - 1);
		map_data->offset_y = rahmen_y/ 2;
		rahmen_x = WIDTH - ((map_data->count_x - 1) * map_data->delta);
		map_data->offset_x = rahmen_x/ 2;
	}
}

/**
 * calculates the center coordinates of the map
*/
void	determine_center(t_readmap *map_data)
{
	map_data->center_x = map_data->offset_x + \
						(map_data->delta * (map_data->count_x - 1)) / 2;
	map_data->center_y = map_data->offset_y + \
						(map_data->delta * (map_data->count_y  - 1)) / 2;
}

/**
 * bresenham from wikipedia
*/
void bresenham(mlx_image_t *g_img, int x0, int x1, int y0, int y1)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int error;
	int e2;
	
	dx = abs(x1 - x0);
    sx = x0 < x1 ? 1 : -1;
    dy = -abs(y1 - y0);
    sy = y0 < y1 ? 1 : -1;
    error = dx + dy;
    
    while (true)
	{
		ft_putpixel(g_img, x0, y0, get_rgba(255, 255, 255, 255));
        if (x0 == x1 && y0 == y1)
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

void	ft_putpixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

/**
 * Initializes Map into isometric depiction
*/
void	init_map(char *map_name, t_readmap *map_data, t_trans *transform)
{
	get_map_information(map_name, map_data);
	transform->matrix = map_data->values_matrix;
	transform->b_x = ft_calloc(sizeof(int), map_data->total_count);
	transform->b_y = ft_calloc(sizeof(int), map_data->total_count);
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
	transform->perspective_projection = 0;
}

void init_mlx(mlx_image_t	*g_img,	mlx_t	*mlx, t_trans *trans)
{
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(g_img->pixels, 0, g_img->width * g_img->height * sizeof(int));
	trans->mlx = mlx;
	trans->img = g_img;
}