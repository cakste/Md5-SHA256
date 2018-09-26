/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:53:54 by acakste           #+#    #+#             */
/*   Updated: 2018/09/24 17:53:55 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*start;

	start = dst;
	while (n > 0)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		n--;
		dst++;
		src++;
	}
	return (start);
}
