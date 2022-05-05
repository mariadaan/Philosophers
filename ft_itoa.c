/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 12:58:03 by mdaan         #+#    #+#                 */
/*   Updated: 2022/05/05 17:47:35 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		if (n > 0)
			n = n / 10;
		else
			n = n / -10;
		len++;
	}
	return (len);
}
/*
**	Description:
**	The strlen() function computes the length of the string s.
**
**	Returns:
**	number of characters in string, excluding the terminating NULL character
*/

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
**	Description:
**	The strlcpy() function copies up to dstsize - 1 characters from the string
**	src to dst, NUL-terminating the result if dstsize is not 0.
**	Room for the NUL-terminator should be included in dstsize.
**
**	Returns:
**	total length of string it tries to create, aka length of src.
*/

static int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		if (dstsize != 0)
			dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/*
**	Description:
**	The strdup() function allocates sufficient memory for a copy of the
**	string s1, does the copy (including NULL-terminator) and returns a
**	pointer to it.
**
**	Returns:
**	a pointer to the (memory allocated) copy of s1
*/

static char	*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	s2 = (char *)malloc(len * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, len);
	return (s2);
}

char	*ft_itoa(int n)
{
	int		num;
	char	*str;
	int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = n;
	len = ft_get_len(n);
	str = (char *)malloc((len + 1)* sizeof(char));
	str[len] = '\0';
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}
