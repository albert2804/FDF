/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:16:28 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/07 17:27:30 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/**
 * transforms the object's original coordinates from map_data
 * into 2D coordinates, which will be displazed on the screen,
 * depending if it will be parallel or perspective projection.
 * 
 * keep this formulas, as plan B		
 * transform->matrix[node][0] = cos(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
											cos(transform->gamma * rad) * (p_x - c_x)) -\
									sin(transform->beta * rad) * (p_z - c_z);
		transform->matrix[node][1] = sin(transform->alpha * rad) * (cos(transform->beta * rad) * (p_z - c_z) +\
																	sin(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
																									cos(transform->gamma * rad) * (p_x - c_x))) +\
									cos(transform->alpha * rad) * (cos(transform->gamma * rad) * (p_y - c_y) -\
																	sin(transform->gamma * rad) * (p_x - c_x));
		transform->matrix[node][2] = cos(transform->alpha * rad) * (cos(transform->beta * rad) * (p_z - c_z) +\
		 															sin(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
		 																							cos(transform->gamma * rad) * (p_x - c_x))) -\
		 							sin(transform->alpha * rad) * (cos(transform->gamma * rad) * (p_y - c_y) -\
 				
*/
void transformation(t_readmap *map_data, t_trans *trans)
{	
	int		p_x;
	int		p_y;
	int		p_z;
	size_t	node;

	node = 0;
	while (node < map_data->total_count)
	{
		p_x = map_data->values_matrix[node][0];
		p_y = map_data->values_matrix[node][1];
		p_z = map_data->values_matrix[node][2] * (-5);
		trans->matrix[node][0] = transform_x(trans, p_x, p_y, p_z);
		trans->matrix[node][1] = transform_y(trans, p_x, p_y, p_z);
		trans->matrix[node][2] = transform_z(trans, p_x, p_y, p_z);
		trans->b_x[node] = trans->matrix[node][0]/trans->zoom + trans->ex;
		trans->b_y[node] = trans->matrix[node][2]/trans->zoom + trans->ey;
		// trans->b_x[node] = e_z * trans->matrix[node][0]/trans->matrix[node][2] + e_x;
		// trans->b_y[node] = e_z * trans->matrix[node][1]/trans->matrix[node][2] + e_y;
		node ++;
	}
}

int transform_x(t_trans *trans, int p_x,  int p_y,  int p_z)
{
	int x;
	double rad;
	
	rad = ((M_PI/180));
	x = cos(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) +\
	cos(trans->gamma * rad) * (p_x - trans->cx)) - sin(trans->beta * rad) * \
	(p_z - trans->cz);
	return (x);
}

int transform_y(t_trans *trans, int p_x,  int p_y,  int p_z)
{
	int y;
	double rad;

	rad = ((M_PI/180));
	y = sin(trans->alpha * rad) * (cos(trans->beta * rad) * (p_z - trans->cz) +\
	sin(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) +\
	cos(trans->gamma * rad) * (p_x - trans->cx))) + cos(trans->alpha * rad) * \
	(cos(trans->gamma * rad) * (p_y - trans->cy) - sin(trans->gamma * rad) * \
	(p_x - trans->cx));
	return (y);
}

int transform_z(t_trans *trans, int p_x,  int p_y,  int p_z)
{
	int z;
	double rad;
	
	rad = ((M_PI/180));
	z = cos(trans->alpha * rad) * (cos(trans->beta * rad) * (p_z - trans->cz) +\
	sin(trans->beta * rad) * (sin(trans->gamma * rad) * (p_y - trans->cy) +\
	cos(trans->gamma * rad) * (p_x - trans->cx))) -\
	sin(trans->alpha * rad) * (cos(trans->gamma * rad) * (p_y - trans->cy) -\
 	sin(trans->gamma * rad) * (p_x - trans->cx));
	return (z);
}