#include "mywindow.h"

int main(int argc, char *argv[])
{
	MyWindow win(argc, argv);
	win.InitComponents();
	win.RunLoop();
	return 0;
}