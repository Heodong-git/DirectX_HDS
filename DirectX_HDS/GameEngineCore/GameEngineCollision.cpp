#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineRenderUnit GameEngineCollision::DebugUnit;

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}


void GameEngineCollision::Start()
{
	SetDebugCamera(GetLevel()->GetCamera(0).get());
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	// 만약 충돌체의 업데이트가 false 라면, 충돌을 진행하지 않는다. 
	if (false == this->IsUpdate())
	{
		return nullptr;
	}

	// 만약 this 의 타입이 MAX 라면 ( 인자에 값을 넣어주지 않았다면 ) 
	// 컬리전이 가지고 있는 자신의 타입으로 충돌진행 
	if (_ThisColType == ColType::MAX)
	{
		_ThisColType = Type;
	}

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

		// 만약, 상대의 컬리전타입이 MAX 일 경우 ( 값을 지정하지 않았다면 ) 
		// 컬리전이 가지고 있는 타입으로 충돌진행
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
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

void GameEngineCollision::Update(float _Delta)
{
	if (false == IsDebug())
	{
		return;
	}

	switch (Type)
	{
	case ColType::SPHERE2D:
		GameEngineDebug::DrawSphere(DebugCamera, GetTransform());
		break;
	case ColType::AABBBOX2D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::OBBBOX2D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::SPHERE3D:
		GameEngineDebug::DrawSphere(DebugCamera, GetTransform());
		break;
	case ColType::AABBBOX3D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::OBBBOX3D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::MAX:
		break;
	default:
		break;
	}
}

bool GameEngineCollision::CollisionAll(int _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType, ColType _OtherColtype)
{
	// 만약 충돌체의 업데이트가 false 라면, 충돌을 진행하지 않는다. 
	if (false == this->IsUpdate())
	{
		return false;
	}

	// 벡터초기화
	_Col.clear();

	// 충돌을 진행할 리스트를 받아온다.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	if (0 == Group.size())
	{
		return false;
	}

	// 인자에 타입을 지정해주지 않았다면 컬리전 자신의 타입으로 충돌진행
	if (_ThisColType == ColType::MAX)
	{
		_ThisColType = Type;
	}

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}
		
		// 마찬가지 
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
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