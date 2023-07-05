/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:17:50 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/09 14:54:36 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*ft_isspace(const char *s)
{
	while (*s == '\t' || *s == '\n' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == ' ')
		s++;
	return (s);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	str = ft_isspace(str);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
