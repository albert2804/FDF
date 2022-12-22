/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:17:27 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 14:52:13 by aestraic         ###   ########.fr       */
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
	if (sgl)
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

void	effect(t_trans *transform, mlx_image_t *g_img)
{
	if (transform->perspective_projection == 1 || \
	transform->perspective_projection == 0)
	{
		transform->perspective_projection = 0;
		transform->cx = 600;
		transform->cy = 600;
		transform->ey = 600;
		transform->cz = 0;
		transform->zoom = 1.5;
		transform->alpha = 0 + 90;
		transform->beta = 0 + 180;
		transform->gamma = 0 + 180;
	}
	make_new_image(transform, g_img);
}
