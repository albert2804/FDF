/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = (char *) dest;
	if (dest == src)
		return (dest);
	else if (dest < src)
	{
		while (i < n)
		{
			tmp[i] = ((char *)src)[i];
			i ++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i --;
			tmp[i] = ((char *)src)[i];
		}
	}
	return (tmp);
}
