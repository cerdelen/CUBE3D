/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cerdelen < cerdelen@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:25:13 by Cerdelen          #+#    #+#             */
/*   Updated: 2021/11/20 01:25:13 by Cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Locates the first occurrence of c (converted to a char) in the string pointed
*	to by s.  The terminating null character is considered to be part of the
*	string; therefore if c is \\0, the functions locate the terminating \\0.
*
* Return Values
*	A pointer to the located character,
*	or NULL if the character does not appear in the string.
*/

char	*ft_strchr(const char *s, int c)
{	
	while (*s != (unsigned char) c)
		if (!*s++)
			return (0);
	return ((char *)s);
}
