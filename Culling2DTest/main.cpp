#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"
#include <random>
#include <chrono>
#include <memory>
using namespace culling2d;

int main(void)
{
	World* world = new World(5, RectF(-100, -100, 200, 200));

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// ��l�������z
	// [-1.0, 1.0)�̒l�͈̔͂ŁA���m���Ɏ����𐶐�����
	std::uniform_real_distribution<> dist1(0, 1.0);

	const auto startTime = std::chrono::system_clock::now();

	for (int i = 0; i < 1000000; ++i)
	{
		world->AddObject(new Object(Circle(Vector2DF(-90 + 180 * dist1(engine), -90 + 180 * dist1(engine)), 10), nullptr, world));
	}

	const auto endTime = std::chrono::system_clock::now();

	const auto timeSpan = endTime - startTime;

	std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	SafeRelease(world);
	system("pause");
}