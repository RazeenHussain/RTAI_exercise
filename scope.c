#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

static int end;
static void endme(int dummy)
{
	end=1;
}

int main(int argc, char * argv[])
{
	int fifo_in;
	float data_in;

	if ((fifo_in = open("/dev/rtf0", O_RDONLY)) < 0) {
		fprintf(stderr, "Error opening /dev/rtf0\n");
		exit(1);
	}

	while (1) 
	{
		read(fifo_in, &data_in, sizeof(data_in));
		printf("%f \n", data_in);
	}
	return 0;
}
