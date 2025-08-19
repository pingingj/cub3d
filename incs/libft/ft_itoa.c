/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:30:08 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 11:11:42 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intsize(int num)
{
	int			i;
	long int	n;

	n = num;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*result;
	long int	num;

	num = n;
	size = intsize(n);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	result[size--] = '\0';
	while (size >= 0 && num > 0)
	{
		result[size] = (num % 10) + '0';
		size--;
		num = num / 10;
	}
	return (result);
}

/*int main()
{
	int n =-12345;
	char *res = ft_itoa(n);
	printf("%s",res);
}*/