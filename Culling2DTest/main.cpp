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

	// ��l�������z
	// [-1.0, 1.0)�̒l�͈̔͂ŁA���m���Ɏ����𐶐�����
	std::uniform_real_distribution<float> dist1(0, 1.0);

	std::cout << "�I�u�W�F�N�g������͂��Ă��������B" << std::endl;
	int OBJECTNUM;
	std::cin >> OBJECTNUM;

	std::cout << "�X�V�񐔂���͂��Ă��������B" << std::endl;
	int TURN;
	std::cin >> TURN;

	for (int i = 0; i < OBJECTNUM; ++i)
	{
		objects.push_back(new Object(Circle(Vector2DF(-90 + 180 * dist1(engine), -90 + 180 * dist1(engine)), 10), nullptr, world, (unsigned int)i));
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

	std::cout << "�ǉ���������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

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
	}

	endTime = std::chrono::system_clock::now();

	timeSpan = endTime - startTime;

	std::cout << "�X�V��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

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

	std::cout << "�폜��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
}