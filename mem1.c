/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:27:57 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 18:06:33 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	free_map_data(t_trans *transform)
{
	free(transform);
	exit(EXIT_FAILURE);
}

void	free_bx(t_readmap *map_data, t_trans *trans)
{
	free(map_data);
	free(trans);
	exit(EXIT_FAILURE);
}

void	free_by(t_readmap *map_data, t_trans *trans, int *bx)
{
	free_bx(map_data, trans);
	free(bx);
	exit(EXIT_FAILURE);
}

void	free_mlx(t_readmap *map_data, t_trans *trans, int *bx)
{
	free_by(map_data, trans, bx);
	exit(EXIT_FAILURE);
}

void	free_matrix(t_readmap *map_data)
{
	free(map_data);
	exit(EXIT_FAILURE);
}
