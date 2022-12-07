/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*bg;

	i = 0;
	bg = ((char *)big);
	if ((ft_strlen(little)) == 0 || big == little)
		return (bg);
	while (i < len && bg[i] != '\0')
	{
		j = 0;
		while (i + j < len && bg[i + j] != '\0' && little[j] != '\0' \
		&& bg[i + j] == little[j])
			j++;
		if (j == (ft_strlen(little)))
			return (bg + i);
		i++;
	}
	return (0);
}
