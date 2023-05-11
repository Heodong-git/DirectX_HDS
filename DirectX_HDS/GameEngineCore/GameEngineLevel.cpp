#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

GameEngineLevel::GameEngineLevel()
{
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
	{
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; )
			{
				std::shared_ptr<GameEngineActor> CheckActor = (*ActorStart);
				GameEngineTransform* ParentTransform = CheckActor->GetTransform()->Parent;

				if (ParentTransform != nullptr)
				{
					GameEngineObject* Object = ParentTransform->GetMaster();

					if (nullptr == Object)
					{
						MsgAssert("부모가 없는 트랜스폼을 Level에서 사용할수는 없습니다.");
					}

					// 자식을 이제부터 부모가 책임진다는 의미.
					Object->Childs.push_back(CheckActor);
					ActorStart = ActorList.erase(ActorStart);
					continue;
				}

				++ActorStart;
			}
		}
	}

	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}

	{
		// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

				Actor->AllAccTime(_DeltaTime);
				Actor->AllUpdate(_DeltaTime);

				//if (false == Actor->IsUpdate())
				//{
				//	continue;
				//}

				//GameEngineTransform* Transform = Actor->GetTransform();
				//Transform->AllAccTime(_DeltaTime);
				//Transform->AllUpdate(_DeltaTime);
			}
		}
	}
}

void GameEngineLevel::ActorRender(float _DeltaTime)
{
	GetMainCamera()->Setting();

	// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

			Actor->AllRender(_DeltaTime);


			/*if (false == Actor->IsUpdate())
			{
				continue;
			}

			GameEngineTransform* Transform = Actor->GetTransform();
			Transform->AllRender(_DeltaTime);*/
		}
	}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);

}

void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; )
		{
			std::shared_ptr<GameEngineActor> RelaseActor = (*ActorStart);

			if (nullptr != RelaseActor && false == RelaseActor->IsDeath())
			{
				RelaseActor->AllRelease();
				//GameEngineTransform* Transform = RelaseActor->GetTransform();
				//Transform->AllRelease();
				++ActorStart;
				continue;
			}

			RelaseActor->Release();
			ActorStart = ActorList.erase(ActorStart);
		}
	}

}

void GameEngineLevel::Update(float _DeltaTime)
{

}

void GameEngineLevel::Render(float _DeltaTime)
{
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();

	// Level이 관리하고 있는 액터를 관리하는 리스트에 들어간다.
	Actors[_Order].push_back(_Actor);
}

void GameEngineLevel::LevelChangeStart()
{

}
void GameEngineLevel::LevelChangeEnd()
{

}