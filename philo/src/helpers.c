/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:45:17 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 09:26:43 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isspace(char *c)
{
	if (!c)
		return (-1);
	if (*c == 32 || (*c > 6 && *c < 14))
		return (1);
	return (0);
}

int ft_isnum(char *c)
{
	if (!c)
		return (-1);
	if (*c > 47 && *c < 58)
		return (1);
	return (0);
}

int ft_sign(char *c)
{
	if (!c)
		return (0);
	if (*c == 43)
		return (1);
	if (*c == 45)
		return (-1);
	return (0);
}

unsigned int ft_atoui(char *str)
{
	unsigned int num;

	num = 0;
	if (!str)
		return (-1);
	while (ft_isspace(str))
		str++;	
	if (ft_sign(str) == 1)
		str++;
	while (*str)
	{
		if (!ft_isnum(str))
			return (-1);
		num = num * 10 + (*str - 48);
		str++;
	}
	return (num);
}
