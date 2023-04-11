#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;
	// 컴포넌트의 트랜스폼 -> 컴포넌트트랜스폼의 부모세팅(인자로 액터의 트랜스폼) 
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	ComponentsList.push_back(_Component);
}

void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->Update(_DeltaTime);
	}
}

void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->Render(_DeltaTime);
	}
}