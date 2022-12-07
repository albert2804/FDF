/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:07:47 by aestraic          #+#    #+#             */
/*   Updated: 2022/07/08 12:20:22 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_conv_int(va_list arg_list)
{
	char			*str;
	unsigned int	ret;

	str = ft_itoa(va_arg(arg_list, int));
	ret = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (ret);
}
//$