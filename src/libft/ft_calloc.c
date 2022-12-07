/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t n_elem, size_t el_size)
{
	void	*array;

	if (el_size != 0 && 18446744073709551615UL / el_size < n_elem)
		return (NULL);
	array = malloc(n_elem * el_size);
	if (!array)
		return (NULL);
	ft_bzero(array, (n_elem * el_size));
	return (array);
}
