#pragma once
#include "BaseActor.h"

// �� Pomp���� �� , ����ĭ�Ǵ�
class Monster_Pomp : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Pomp();
	~Monster_Pomp();

	// delete Function
	Monster_Pomp(const Monster_Pomp& _Other) = delete;
	Monster_Pomp(Monster_Pomp&& _Other) noexcept = delete;
	Monster_Pomp& operator=(const Monster_Pomp& _Other) = delete;
	Monster_Pomp& operator=(Monster_Pomp&& _Other) noexcept = delete;

protected:

private:

};
