#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ApplicationServices/ApplicationServices.h>
#include <errno.h>

#define die(str, args...) do { \
        perror(str); \
        exit(EXIT_FAILURE); \
    } while(0)

void getCurrentResolution(int *dim)
{
	char bash_cmd[] = "system_profiler SPDisplaysDataType | grep Resolution | sed 's/[^0-9 ]*//g' | sed -e 's/^[ \t]*//' | sed 's/  */x/g'";
	char buffer[100];
	FILE *pipe;
	char xRes[5] = {0}; 
	char yRes[5] = {0};
	char *currentRes = xRes;
	int j = 0, i = 0;
	pipe = popen(bash_cmd, "r");
	if (NULL == pipe) {
		perror("pipe");
		exit(1);
	}

	while (fgets(buffer, 100, pipe) != NULL);

	for (i = 0; i < strlen(buffer) - 1; i++) {
		if (buffer[i] != 'x')
		{
			currentRes[j] = buffer[i];
			j++;
		}
		else {
			currentRes = yRes;
			j = 0;
		}
	}
	dim[0] = atoi(xRes);
	dim[1] = atoi(yRes);
}

int
main(void)
{
	int dim[2] = {0};

	getCurrentResolution(dim);
	if (dim[0] <= 0 || dim[1] <= 0)
		die("wrong resolution");

	while(1)
	{
		double xTmp, yTmp;
		char buffer[255];

		read(STDIN_FILENO, buffer, sizeof(buffer));
		sscanf(buffer, "x:%lf:y:%lf;", &xTmp, &yTmp);
        int x = xTmp * dim[0];
		int y = yTmp * dim[1];

		printf("Got some data, my resolution %d %d, moving to coord x:%d, y:%d \n", dim[0], dim[1], x, y);

		CGEventRef move1 = CGEventCreateMouseEvent(
		    NULL, kCGEventMouseMoved,
			CGPointMake(x, y),
			kCGMouseButtonLeft
		);

		CGEventPost(kCGHIDEventTap, move1);

		CFRelease(move1);

	
	}


	return 0;
}
 

