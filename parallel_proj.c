/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:16:28 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/07 12:14:08 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void transformation(t_readmap *map_data, t_trans *transform)
{	
	double	rad;
	int		c_y;
	int		c_x;
	int		c_z;
	int		e_x = 600;//surface position relative to camera position c_x
	int		e_y = 600;//surface position relative to camera position c_y
	// int		e_z = 600;//needed for perspective projection
	double	zoom = 1.5;
	int		p_x;
	int		p_y;
	int		p_z;
	size_t	node;

	transform->alpha = 55 + 90;
	transform->beta = 0 + 180;
	transform->gamma = -45 + 180;
	c_x = 600; //x-cordiante of camera position
	c_y = 600; //y-cordiante of camera position
	c_z = 0;
	rad = ((M_PI/180));
	transform->matrix = map_data->values_matrix;
	
	ft_printf("\n\n----------Transformation----------\n");
	node = 5;
	ft_printf("Node %dX: %d\n", node, map_data->values_matrix[node][0]);
	ft_printf("Node %dY: %d\n", node, map_data->values_matrix[node][1]);
	ft_printf("Node %dZ: %d\n", node, map_data->values_matrix[node][2]);
	
	node = 0;
	while (node < map_data->total_count)
	{
		p_x = map_data->values_matrix[node][0];
		p_y = map_data->values_matrix[node][1];
		p_z = map_data->values_matrix[node][2] * (-5);
		transform->matrix[node][0] = cos(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
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
																	sin(transform->gamma * rad) * (p_x - c_x));
		transform->b_x[node] = transform->matrix[node][0]/zoom + e_x;
		transform->b_y[node] = transform->matrix[node][2]/zoom + e_y;
		// transform->b_x[node] = e_z * transform->matrix[node][0]/transform->matrix[node][2] + e_x;
		// transform->b_y[node] = e_z * transform->matrix[node][1]/transform->matrix[node][2] + e_y;
		node ++;
	}
ft_printf("\ntransformed: %d\n", node);
}
