
#include <unistd.c>

void    ft_putlong_fd(long long int n, int fd)
{
        char    c;

        if (n == -9223372036854775807)
                write(fd, "-9223372036854775807", 20);
        else
        {
                if (n < 0)
                {
                        n *= -1;
                        write(fd, "-", 1);
                }
                if (n < 10)
                {
                        c = n + '0';
                        write(fd, &c, 1);
                }
                else
                {
                        ft_putlong_fd(n / 10, fd);
                        ft_putlong_fd(n % 10, fd);
                }
        }
}
