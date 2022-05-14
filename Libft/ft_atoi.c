/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cerdelen < cerdelen@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 23:37:31 by Cerdelen          #+#    #+#             */
/*   Updated: 2021/11/22 23:37:31 by Cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Converts the string into an integer representation.
*
*	The string may begin with an arbitrary amount of white space (as determined
*	by isspace) followed by a single optional `+' or `-' sign. It is assumed
*	that the number is in base 10. The conversion stops at the first character
*	that is not a valid digit.
*
* Return Values
*	the resulting int from the conversion
*/

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	out;

	i = 0;
	sign = 1;
	out = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		sign = (nptr[i++] - 44) * -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		out = (out * 10) + (nptr[i++] - '0');
	return (out * sign);
}
