/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 06:30:22 by sjossain          #+#    #+#             */
/*   Updated: 2024/05/16 13:00:08 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*int	main(int argc, char **argv)
{
	(void) argc;
	printf("%ld\n", ft_strlen(argv[1]));
	printf("%ld\n", strlen(argv[1]));
}*/
