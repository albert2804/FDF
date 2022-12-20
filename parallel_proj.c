/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:16:28 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/20 14:23:59 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/**
 * transforms the object's original coordinates from map_data
 * into 2D coordinates, which will be displazed on the screen,
 * depending if it will be parallel or perspective projection.
*/
void	transformation(t_trans *transform)
{	
	int		p_x;
	int		p_y;
	int		p_z;
	size_t	node;

	node = 0;
	while (node < transform->map_data->total_count)
	{
		p_x = transform->map_data->values_matrix[node][0];
		p_y = transform->map_data->values_matrix[node][1];
		p_z = transform->map_data->values_matrix[node][2] * (-5);
		transform->matrix[node][0] = transform_x(transform, p_x, p_y, p_z);
		transform->matrix[node][1] = transform_y(transform, p_x, p_y, p_z);
		transform->matrix[node][2] = transform_z(transform, p_x, p_y, p_z);
		calculate_xy(transform, node);
		transform->map_data->values_matrix[node][0] = p_x;
		transform->map_data->values_matrix[node][1] = p_y;
		transform->map_data->values_matrix[node][2] = p_z / (-5);
		node ++;
	}
}

int	transform_x(t_trans *trans, int p_x, int p_y, int p_z)
{
	int		x;
	double	rad;

	rad = ((M_PI / 180));
	x = cos(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) + \
	cos(trans->gamma * rad) * (p_x - trans->cx)) - sin(trans->beta * rad) * \
	(p_z - trans->cz);
	return (x);
}

int	transform_y(t_trans *trans, int p_x, int p_y, int p_z)
{
	int		y;
	double	rad;

	rad = ((M_PI / 180));
	y = sin(trans->alpha * rad) * (cos(trans->beta * rad) * (p_z - trans->cz) + \
	sin(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) + \
	cos(trans->gamma * rad) * (p_x - trans->cx))) + cos(trans->alpha * rad) * \
	(cos(trans->gamma * rad) * (p_y - trans->cy) - sin(trans->gamma * rad) * \
	(p_x - trans->cx));
	return (y);
}

int	transform_z(t_trans *trans, int p_x, int p_y, int p_z)
{
	int		z;
	double	rad;

	rad = ((M_PI / 180));
	z = cos(trans->alpha * rad) * (cos(trans->beta * rad) * (p_z - trans->cz) + \
	sin(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) + \
	cos(trans->gamma * rad) * (p_x - trans->cx))) - \
	sin(trans->alpha * rad) * (cos(trans->gamma * rad) * (p_y - trans->cy) - \
	sin(trans->gamma * rad) * (p_x - trans->cx));
	return (z);
}

void	calculate_xy(t_trans *transform, size_t node)
{
	if (transform->perspective_projection == 0)
	{
		transform->b_x[node] = transform->matrix[node][0] / transform->zoom + \
		transform->ex;
		transform->b_y[node] = transform->matrix[node][2] / transform->zoom + \
		transform->ey;
	}
	else if (transform->perspective_projection == 1)
	{
		transform->b_x[node] = transform->matrix[node][0] * transform->ez / \
		(transform->matrix[node][2] * transform->zoom) + transform->ex;
		transform->b_y[node] = transform->matrix[node][1] * transform->ez / \
		(transform->matrix[node][2] * transform->zoom) + transform->ey;
	}
}
