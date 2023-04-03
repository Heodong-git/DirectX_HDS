#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"


GameEngineLevel::GameEngineLevel()
{
	// ������ ������ �� �ݵ�� ī�޶� ����
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
	// �ʿ� ����Ǿ� �ֱ� ������ 2�� for������ ó��
	// �� Ž�� �� ����ƮŽ�� 
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
		}
	}	

	/*std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator StartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>> Actorlist = (*StartIter).second;
		
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStartIter = Actorlist.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEndIter = Actorlist.end();

		for (; ActorStartIter != ActorEndIter; ++ActorStartIter)
		{
			if (nullptr != ActorStartIter->get())
			{
				ActorStartIter->get()->Update(_DeltaTime);
			}
		}
	}*/
}

void GameEngineLevel::Render(float _DeltaTime)
{
	// �̰� ���߿� ������� �������� ������ �� ������ �Ǵ� ������ �ɰ̴ϴ�.
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
		}
	}

	//std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator StartIter = Actors.begin();
	//std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator EndIter = Actors.end();

	//for (; StartIter != EndIter; ++StartIter)
	//{
	//	std::list<std::shared_ptr<GameEngineActor>> Actorlist = (*StartIter).second;
	//	std::list<std::shared_ptr<GameEngineActor>>::iterator ListStartIter = Actorlist.begin();
	//	std::list<std::shared_ptr<GameEngineActor>>::iterator ListEndIter = Actorlist.end();

	//	for (; ListStartIter != ListEndIter; ++ListStartIter)
	//	{
	//		if (nullptr != ListStartIter->get())
	//		{
	//			ListStartIter->get()->Render(_DeltaTime);
	//		}
	//	}
	//}
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Parent)
{
	_Actor->Level = this;
	_Actor->SetParent(_Parent);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}