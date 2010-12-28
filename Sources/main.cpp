#include "InternalLoader.h"

int main (int argc, const char ** argv)
{
	InternalLoader private_loader("link.tmx");
	TMXMap* m_map = private_loader.m_map;
	return 1;
}
