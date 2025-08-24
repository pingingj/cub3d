/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:38:09 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/24 02:35:38 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

/*int main()
{
	char c = 'a';
	int n = 7;
	int res = ft_isascii(c);
	int res2 =ft_isascii(n);
	printf("n->%d\n",res2);
	printf("c->%d\n",res);
}*/