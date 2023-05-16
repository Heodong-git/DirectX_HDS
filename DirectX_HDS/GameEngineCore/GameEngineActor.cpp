#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component, int _Order)
{
	_Component->Actor = this;
	_Component->Level = GetLevel();
	// 컴포넌트 생성 후 최초 초기화시에는 월드부모가 없는 상태 false 
	_Component->GetTransform()->SetParent(GetTransform(), false);
	_Component->SetOrder(_Order);
	_Component->Start();

	// PushChild(_Component);
}

void GameEngineActor::SetOrder(int _Order)
{
	std::shared_ptr<GameEngineActor> ConThis = DynamicThis<GameEngineActor>();

	// 기존의 그룹에서 나를 지우고
	std::list<std::shared_ptr<GameEngineActor>>& Group = GetLevel()->Actors[GetOrder()];
	Group.remove(ConThis);

	GameEngineObjectBase::SetOrder(_Order);

	// 새로운 그룹에 나를 추가한다.
	GetLevel()->Actors[GetOrder()].push_back(ConThis);

}