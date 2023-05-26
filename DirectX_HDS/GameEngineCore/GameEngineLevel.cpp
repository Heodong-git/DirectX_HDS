#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineGUI.h"
#include "GameEngineCollision.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>();

	Cameras.insert(std::make_pair(0, MainCamera));

	std::shared_ptr<GameEngineCamera> UICamera = CreateActor<GameEngineCamera>();
	UICamera->SetProjectionType(CameraType::Orthogonal);

	Cameras.insert(std::make_pair(100, UICamera));
}

GameEngineLevel::~GameEngineLevel()
{
}



void GameEngineLevel::Start()
{
	
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
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

void GameEngineLevel::ActorLevelChangeStart()
{
	{
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

				Actor->AllLevelChangeStart();
			}
		}
	}
}
void GameEngineLevel::ActorLevelChangeEnd()
{
	{
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

				Actor->AllLevelChangeEnd();
			}
		}
	}
}

void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//GetMainCamera()->Setting();
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Setting();
		Cam->CameraTransformUpdate();
		Cam->Render(_DeltaTime);
	}

	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Camera = Pair.second;
		std::shared_ptr<GameEngineRenderTarget> Target = Camera->GetCamTarget();

		GameEngineDevice::GetBackBufferTarget()->Merge(Target);
	}

	//// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.
	//std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	//std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	//for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	//{
	//	std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

	//	std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
	//	std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

	//	for (; ActorStart != ActorEnd; ++ActorStart)
	//	{
	//		std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

	//		Actor->AllRender(_DeltaTime);


	//		/*if (false == Actor->IsUpdate())
	//		{
	//			continue;
	//		}

	//		GameEngineTransform* Transform = Actor->GetTransform();
	//		Transform->AllRender(_DeltaTime);*/
	//	}
	//}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
{
	// 랜더러를 릴리즈
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Release();
	}

	{
		// 콜리전삭제 
		std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineCollision>>& ObjectList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineCollision>>::iterator ObjectStart = ObjectList.begin();
			std::list<std::shared_ptr<GameEngineCollision>>::iterator ObjectEnd = ObjectList.end();

			for (; ObjectStart != ObjectEnd; )
			{
				std::shared_ptr<GameEngineCollision> RelaseObject = (*ObjectStart);

				if (nullptr != RelaseObject && false == RelaseObject->IsDeath())
				{
					++ObjectStart;
					continue;
				}

				ObjectStart = ObjectList.erase(ObjectStart);
			}
		}
	}
	{
		// 액터삭제 
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
	// Actors[_Order].push_back(_Actor);
}

void GameEngineLevel::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}

void GameEngineLevel::LevelChangeStart()
{

}
void GameEngineLevel::LevelChangeEnd()
{

}

void GameEngineLevel::PushCameraRenderer(std::shared_ptr<GameEngineRenderer> _Renderer, int _CameraOrder)
{
	std::shared_ptr<GameEngineCamera> FindCamera = GetCamera(_CameraOrder);

	if (nullptr == FindCamera)
	{
		MsgAssert("존재하지 않는 카메라에 랜더러를 넣을수는 없습니다.");
		return;
	}

	FindCamera->PushRenderer(_Renderer);
}

std::shared_ptr<GameEngineCamera> GameEngineLevel::GetCamera(int _CameraOrder)
{
	std::map<int, std::shared_ptr<GameEngineCamera>>::iterator FindIter = Cameras.find(_CameraOrder);

	if (FindIter == Cameras.end())
	{
		return nullptr;
	}

	std::shared_ptr<GameEngineCamera> Camera = FindIter->second;

	return Camera;
}

void GameEngineLevel::TextureReLoad(GameEngineLevel* _PrevLevel)
{

	for (const std::pair<std::string, std::string>& Pair : TexturePath)
	{
		if (nullptr != _PrevLevel && true == _PrevLevel->TexturePath.contains(Pair.first))
		{
			continue;
		}

		GameEngineTexture::ReLoad(Pair.second, Pair.first);
		LoadEndPath.insert(std::make_pair(Pair.first, Pair.second));
	}

	TexturePath.clear();
}