#include "warpper.hpp"

void fcb(const void *buff, int len, void *reserve)
{
	std::cout << len << std::endl;
}

int main(int argc, char *argv[])
{
	RtspClient cli;
	cli.Open("rtsp://10.126.33.13:8554/axstream0", fcb, nullptr);
	getchar();
	cli.Stop();
	return 0;
}