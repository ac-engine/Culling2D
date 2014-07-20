#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"

int main(void)
{
	std::cout << "Hello World." << std::endl;

	culling2d::World *world = new culling2d::World(5, culling2d::RectF());

	delete world;
	system("pause");
}