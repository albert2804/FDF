/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:07:47 by aestraic          #+#    #+#             */
/*   Updated: 2022/08/02 14:31:14 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	ft_decide_letter_ptr(unsigned long n)
{
	char	c;

	c = 'a';
	if (n == 10)
		c = 'a';
	else if (n == 11)
		c = 'b';
	else if (n == 12)
		c = 'c';
	else if (n == 13)
		c = 'd';
	else if (n == 14)
		c = 'e';
	else if (n == 15)
		c = 'f';
	return (c);
}

static unsigned int	ft_count_strlen_ptr(unsigned long n)
{
	unsigned int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static char	*ft_reverse_string_ptr(char *s)
{
	size_t	len;
	size_t	i;
	char	*rev_str;

	i = 0;
	len = ft_strlen(s);
	rev_str = malloc(len * sizeof(char) + 1);
	while (i < len)
	{
		rev_str[len - 1 - i] = s[i];
		i++;
	}
	rev_str[len] = '\0';
	free(s);
	return (rev_str);
}

/*
used to source code out of the conv_pointer function
*/
char	*build_string(unsigned long ptr, char *s)
{	
	int	i;

	i = 0;
	while (ptr != 0)
	{
		if (ptr % 16 > 9 && ptr % 16 < 16)
			s[i] = ft_decide_letter_ptr((ptr % 16));
		else
			s[i] = (ptr % 16) + '0';
		ptr = ptr / 16;
		i++;
	}
	return (s);
}

int	ft_conv_pointer(va_list arg_list)
{
	unsigned long	ptr;
	char			*s;
	size_t			count;

	ptr = (unsigned long) va_arg(arg_list, void *);
	ft_putstr_fd("0x", 1);
	if (!ptr)
	{
		ft_putchar_fd('0', 1);
		return (3);
	}
	count = ft_count_strlen_ptr(ptr);
	s = malloc(count * sizeof(char) + 1);
	if (!s)
		return (0);
	s = build_string(ptr, s);
	s[count] = '\0';
	s = ft_reverse_string_ptr(s);
	ft_putstr_fd(s, 1);
	free(s);
	return (count + 2);
}
