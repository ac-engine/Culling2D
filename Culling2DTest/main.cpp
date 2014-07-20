#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"

using namespace culling2d;

int main(void)
{
	std::cout << "Hello World." << std::endl;

	World *world = new World(5, RectF(-100, -100, 200, 200));

	world->AddObject(new Object(Circle(Vector2DF(0, 0), 10), nullptr, world));

	auto objects = world->GetCullingObjects(RectF(-10, -10, 10, 10));

	std::cout << "culled size = " << objects.size() << std::endl;

	delete world;
	system("pause");
}