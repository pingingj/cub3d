/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:37:58 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/24 02:35:37 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

/*int main()
{
	char c = 'a';
	int n = 7;
	int res = ft_isalpha(c);
	int res2 =ft_isalpha(n);
	printf("n->%d\n",res2);
	printf("c->%d\n",res);
}*/