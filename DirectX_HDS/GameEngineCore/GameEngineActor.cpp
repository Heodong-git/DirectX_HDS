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

// 
void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Update(_DeltaTime);
	}
}

void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Render(_DeltaTime);
	}
}


void GameEngineActor::AccLiveTime(float _LiveTime)
{
	GameEngineUpdateObject::AccLiveTime(_LiveTime);

	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->AccLiveTime(_LiveTime);
	}
}

// 컴포넌트 릴리즈
// 현재 구조상의 문제, 렌더러를 만들고, 그 렌더러의 자식을 추가하게 되면 문제. 
void GameEngineActor::ComponentsRelease()
{
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComStartIter = ComponentsList.begin();
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComEndIter = ComponentsList.end();

	for (; ComStartIter != ComEndIter; )
	{
		std::shared_ptr<class GameEngineComponent>& ComPtr = *ComStartIter;

		if (false == ComPtr->IsDeath())
		{
			++ComStartIter;
			continue;
		}

		ComStartIter = ComponentsList.erase(ComStartIter);
	}
}