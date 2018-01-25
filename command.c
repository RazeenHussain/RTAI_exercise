#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#include <fcntl.h>
#include <signal.h>

static int end;
static void endme(int dummy)
{
	end=1;
}

int main(int argc, char * argv[])
{
	int fifo_out, data_out;
	
	if ((fifo_out = open("/dev/rtf1", O_WRONLY)) < 0) {
		fprintf(stderr, "Error opening /dev/rtf1\n");
		exit(1);
	}

	while (1) 
	{
		printf("\n Insert the width of the sine \n");
		scanf("%d",&data_out);
		write(fifo_out, &data_out, sizeof(data_out));
	}
	return 0;
}
