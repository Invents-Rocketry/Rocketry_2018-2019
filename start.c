#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>

int main(int argc, char** argv) {

	if(argc > 0 && !strcmp(argv[1], "sensor")) {
		execvp("readBMP.py", NULL);
	}
	execvp("camera.py", NULL);

}
