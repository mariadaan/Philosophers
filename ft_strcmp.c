/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 13:01:35 by mdaan         #+#    #+#                 */
/*   Updated: 2022/05/05 16:45:37 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/*
**	Description:
**	The strncmp() function compares null-terminated strings s1 and s2 up to
**	the nth character or to the NULL terminator if n is larger than the strings
**
**	Returns:
**	0 if s1 == s2
**	>0 if s1 > s2
**	<0 if s1 < s2
**	(s1[char] - s2[char] on the first char that is different)
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] - (unsigned char)s2[i] != 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
