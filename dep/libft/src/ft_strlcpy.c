/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:50:20 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/07 19:56:33 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[i]));
}


size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < ft_strlen(src))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[i]));
}
/*int	main(void)
{
    char src[] = "hello";
    char dest[10];

    size_t len = ft_strlcpy(dest, src, 13);

    printf("Chaîne copiée : %s\n", dest);
    printf("Longueur de la chaîne copiée : %zu\n", len);
    return 0;
}*/
