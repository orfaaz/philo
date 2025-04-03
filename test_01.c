#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	t;
	long int				ut;
	int				i = 100;

	gettimeofday(&t, NULL);
	printf("time=%ld,%ld\n", t.tv_sec, t.tv_usec);
	while (i--)
		usleep(100);
	gettimeofday(&t, NULL);
	ut = t.tv_usec;
	printf("time=%ld,%ld\n", t.tv_sec, ut);
}
