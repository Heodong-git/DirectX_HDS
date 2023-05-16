#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}


void GameEngineCollision::Start()
{
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	// 레벨이 저장하고 있는 충돌체 리스트를 받아온다.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	// 반복탐색
	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		// 만약 충돌체의 업데이트가 false 라면 continue
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		// 업데이트 중이라면 트랜스폼을 받아와서 충돌수행, 충돌했다면 충돌한 콜리전 반환 
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			return _OtherCol;
		}
	}

	// 충돌하지 않았다면 nullptr 반환
	return nullptr;
}

void GameEngineCollision::SetOrder(int _Order)
{
	std::shared_ptr<GameEngineCollision> ConThis = DynamicThis<GameEngineCollision>();

	// 기존에 내가 저장되어 있던 그룹에서 나를 제거한다.
	// 현시점의 문제점, 많은량의 충돌체가 저장되어 있을 경우, 찾을때 까지 탐색하게 되어 속도가 느려질 수 있다. 
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[GetOrder()];
	Group.remove(ConThis);

	// 오더값을 변경하고
	GameEngineObjectBase::SetOrder(_Order);

	// 새로운 그룹에 나를 추가한다.
	GetLevel()->PushCollision(ConThis);
}

bool GameEngineCollision::CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
{
	// 벡터초기화
	_Col.clear();

	// 충돌을 진행할 리스트를 받아온다.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		// 충돌했다면 벡터에 충돌체를 추가한다. 
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			_Col.push_back(_OtherCol);
		}
	}

	// 충돌여부를 반환한다. true 라면 인자로 넣어준 벡터에 충돌체가 저장되어 있을 것, 활용할 수 있다. 
	return _Col.size() != 0;

}