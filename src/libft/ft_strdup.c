/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	int		n;
	int		i;
	char	*s_cpy;

	i = 0;
	n = ft_strlen((char *)s);
	s_cpy = malloc(n * sizeof(char) + 1);
	if (!s_cpy)
		return (NULL);
	while (i <= n)
	{
		s_cpy[i] = s[i];
		i++;
	}
	return (s_cpy);
}
