/*
 *
 * This program will start the camera, data logging, and data transmission.
 *
 */

#include <stdlib.h>

int main(int argc, char** argv) {

	execvp("readBMP.py", NULL);
	execvp("camera.py", NULL);

}
