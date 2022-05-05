#include "philo.h"
#include <stdlib.h>

char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);

/*
	Check whether string contains an integer value
	Returns 1 if num is within integer value boundaries
	else, returns 0
*/
static int	is_int(char *num_str)
{
	int		num_int;
	char	*new_num_str;

	if (!num_str)
		return (0);
	num_int = ft_atoi(num_str);
	new_num_str = ft_itoa(num_int);
	if (ft_strcmp(num_str, new_num_str))
	{
		free(new_num_str);
		return (0);
	}
	free(new_num_str);
	return (1);
}

/*
	Check whether given arguments are an array of integers
	Returns
	- 1 if all ints
	- 0 if not all ints
*/
static int	is_all_ints(int argc, char **input)
{
	int		i;
	char	*num;

	i = 0;
	while (i < argc - 1)
	{
		num = input[i];
		if (!(is_int(num)))
			return (0);
		i++;
	}
	return (1);
}

/*
	Check whether input is integers only
	Returns
	- 1 if input is not valid
	- 0 if input is valid
*/
int	check_input(int argc, char **input)
{
	if (argc < 5)
		return (1);
	if (is_all_ints(argc, input + 1) == 0)
		return (1);
	return (0);
}
