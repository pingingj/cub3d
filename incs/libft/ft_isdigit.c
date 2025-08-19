/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:37:53 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 11:08:57 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
	{
		return (1);
	}
	return (0);
}

/*int main()
{
	char c = '5';
	int n = 7;
	int res = ft_isdigit(c);
	int res2 =ft_isdigit(n);
	printf("n->%d\n",res2);
	printf("c->%d\n",res);
}*/