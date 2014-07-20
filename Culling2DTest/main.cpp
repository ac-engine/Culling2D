#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"

using namespace culling2d;

int main(void)
{
	std::cout << "Hello World." << std::endl;

	World *world = new World(5, RectF(-100, -100, 200, 200));

	world->AddObject(new Object(Circle(Vector2DF(0, 0), 10), nullptr, world));

	delete world;
	system("pause");
}