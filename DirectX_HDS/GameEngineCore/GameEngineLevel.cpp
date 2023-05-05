#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"


GameEngineLevel::GameEngineLevel()
{
	// ������ ������ �� �ݵ�� ī�޶� ����
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{
}

void GameEngineLevel::Start()
{
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	// ���� update �� false �� ���, live Ÿ�� ���� ������ ���� �ʴ´�.
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}
			Actor->AccLiveTime(_DeltaTime);
		}
	}

	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}

	// �ʿ� ����Ǿ� �ֱ� ������ 2�� for������ ó��
	// �� Ž�� �� ����ƮŽ�� 
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}
			
			Actor->Update(_DeltaTime);
			Actor->ComponentsUpdate(_DeltaTime);
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

void GameEngineLevel::ActorRender(float _DeltaTime)
{
	GetMainCamera()->Setting();

	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
			Actor->ComponentsRender(_DeltaTime);
		}
	}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);

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

void GameEngineLevel::ActorRelease()
{
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator Start = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator End = ActorList.end();

		for (; Start != End; )
		{
			std::shared_ptr<GameEngineActor> RelaseActor = (*Start);

			if (nullptr != RelaseActor && false == RelaseActor->IsDeath())
			{
				++Start;
				continue;
			}

			RelaseActor->Release();
			Start = ActorList.erase(Start);
		}
	}
}


void GameEngineLevel::Update(float _DeltaTime)
{

}

void GameEngineLevel::Render(float _DeltaTime)
{
	
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Parent)
{
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();

	// ����Ʈ�� �߰�
	Actors[_Order].push_back(_Actor);
}

void GameEngineLevel::LevelChangeStart()
{

}
void GameEngineLevel::LevelChangeEnd()
{

}