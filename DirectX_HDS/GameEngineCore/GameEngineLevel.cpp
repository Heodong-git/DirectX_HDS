#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	// 레벨은 생성될 때 반드시 카메라를 생성
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{
}



void GameEngineLevel::Loading()
{


}


void GameEngineLevel::Update(float _DeltaTime)
{
	// 맵에 저장되어 있기 때문에 2중 for문으로 처리
	// 맵 탐색 후 리스트탐색 
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render(float _DeltaTime)
{
	// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
		}
	}
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Parent)
{
	_Actor->Level = this;
	_Actor->SetParent(_Parent);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}