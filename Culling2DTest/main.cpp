#include <iostream>
#include "../Culling2D/Culling/culling2d.World.h"
#include <random>
#include <chrono>
#include <memory>
#include <vector>
using namespace culling2d;

const int OBJECTNUM = 100;
const int TURN = 100;

class ClientCircle
{
	Circle circle;
public:
	ClientCircle(){}

	ClientCircle(Circle circle)
	{
		this->circle = circle;
	}
};

int main(void)
{
	std::vector<Object*> objects;
	World* world = new World(5, RectF(-100, -100, 200, 200));

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 一様実数分布
	// [-1.0, 1.0)の値の範囲で、等確率に実数を生成する
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

	std::cout << "処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	for (int j = 0; j < TURN; ++j)
	{

		for (int i = 0; i < OBJECTNUM; ++i)
		{
			auto circle = objects[i]->GetCircle();
			circle.Position.X += 1;
			if (circle.Position.X >= 90)
			{
				circle.Position.X = -90;
			}
			objects[i]->SetCircle(circle);
		}

		world->Update();
	}

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		world->RemoveObject(objects[i]);
	}

	SafeRelease(world);

	system("pause");
}