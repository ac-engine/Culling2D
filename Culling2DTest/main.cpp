#include <iostream>
#include "../Culling2D/Culling2D.h"
#include <random>
#include <chrono>
#include <memory>
#include <vector>

using namespace culling2d;

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

int main(int argc, char *argv[])
{
	std::vector<Object*> objects;
	World* world = new World(5, RectF(-100, -100, 200, 200));

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 一様実数分布
	// [-1.0, 1.0)の値の範囲で、等確率に実数を生成する
	std::uniform_real_distribution<float> dist1(0, 1.0);

	std::cout << "オブジェクト数を入力してください。" << std::endl;
	int OBJECTNUM;
	std::cin >> OBJECTNUM;

	std::cout << "更新回数を入力してください。" << std::endl;
	int TURN;
	std::cin >> TURN;

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		auto object = Object::Create(nullptr, world);
		object->SetCircle(Circle(Vector2DF(-90 + 180 * dist1(engine), -90 + 180 * dist1(engine)), 5));
		objects.push_back(object);
	}

	auto startTime = std::chrono::system_clock::now();

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		if (world->AddObject(objects[i]) == nullptr)
		{
			exit(-1);
		}
	}

	auto endTime = std::chrono::system_clock::now();

	auto timeSpan = endTime - startTime;

	std::cout << "追加処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	startTime = std::chrono::system_clock::now();

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

		
		if (j == TURN / 2)
		{
			world->ResetWorld(6, RectF(-150, -150, 300, 300));
		}

	}

	endTime = std::chrono::system_clock::now();

	timeSpan = endTime - startTime;

	std::cout << "更新処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	startTime = std::chrono::system_clock::now();

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		world->RemoveObject(objects[i]);
	}

	SafeRelease(world);


	for (int i = 0; i < OBJECTNUM; ++i)
	{
		SafeRelease(objects[i]);
	}

	endTime = std::chrono::system_clock::now();

	timeSpan = endTime - startTime;

	std::cout << "削除処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

	system("pause");
}