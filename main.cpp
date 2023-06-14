#include "warpper.h"
#include "iostream"

void fcb(const void *buff, int len, void *reserve)
{
	std::cout << len << std::endl;
}

int main(int argc, char *argv[])
{
	auto cli = rtspcli_start("rtsp://10.126.33.13:8554/axstream0", fcb, nullptr);
	getchar();
	rtspcli_stop(&cli);
	return 0;
}