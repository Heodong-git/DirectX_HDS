#pragma once
#include "CKatanaZero_Actor.h"

// �� Pomp���� �� 
class CMonster_Pomp : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CMonster_Pomp();
	~CMonster_Pomp();

	// delete Function
	CMonster_Pomp(const CMonster_Pomp& _Other) = delete;
	CMonster_Pomp(CMonster_Pomp&& _Other) noexcept = delete;
	CMonster_Pomp& operator=(const CMonster_Pomp& _Other) = delete;
	CMonster_Pomp& operator=(CMonster_Pomp&& _Other) noexcept = delete;

protected:

private:

};
