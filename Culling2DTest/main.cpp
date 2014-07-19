#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"
int main(void)
{
	std::cout << "Hello World." << std::endl;

	culling2d::World world = culling2d::World(10, culling2d::RectF());

	system("pause");
}