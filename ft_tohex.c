

char    ft_tohex(int num)
{
        if (num <= 9)
                return (num + '0');
        else if (num <= 15)
                return ('a' - 10 + num);
	else
		return (NULL);
}
