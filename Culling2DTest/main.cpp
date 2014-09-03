#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"
#include <random>
#include <chrono>
#include <memory>
#include <vector>
using namespace culling2d;

const int OBJECTNUM = 100;

int main(void)
{
	std::vector<Object*> objects;
	World* world = new World(5, RectF(-100, -100, 200, 200));

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// ��l�������z
	// [-1.0, 1.0)�̒l�͈̔͂ŁA���m���Ɏ����𐶐�����
	std::uniform_real_distribution<> dist1(0, 1.0);

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		objects.push_back(new Object(Circle(Vector2DF(-90 + 180 * dist1(engine), -90 + 180 * dist1(engine)), 10), nullptr, world));
	}

	const auto startTime = std::chrono::system_clock::now();

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		if (world->AddObject(objects[i]) == nullptr)
		{
			exit(-1);
		}
	}

	const auto endTime = std::chrono::system_clock::now();

	const auto timeSpan = endTime - startTime;

	std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		world->RemoveObject(objects[i]);
	}

	SafeRelease(world);

	system("pause");
}