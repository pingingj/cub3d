/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:37:44 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 11:09:39 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

/*int main()
{
	char c = 'a';
	int n = 7;
	int res = ft_isprint(c);
	int res2 =ft_isprint(n);
	printf("n->%d\n",res2);
	printf("c->%d\n",res);
}*/