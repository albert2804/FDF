/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len_str;
	char			*str;

	if ((!s) || (!f))
		return (NULL);
	len_str = ft_strlen(s);
	str = malloc(len_str * sizeof(char) + 1);
	if (!str)
		return (NULL);
	if ((!s) || (!f))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{	
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
