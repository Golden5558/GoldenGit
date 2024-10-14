#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(void)
{
	int	i;
	char c;

	c = 48;
	i = 0;
	while (i <= 9)
	{
		ft_putchar(c + i++);
	}
	write(1, "\n", 1); 
}
