#include "PrecompileHeader.h"
#include "GameEngineObject.h"

GameEngineObject::GameEngineObject()
{
	Transform.SetMaster(this);
}

GameEngineObject::~GameEngineObject()
{
}


void GameEngineObject::Release()
{
	Transform.ChildRelease();

	std::list<std::shared_ptr<GameEngineObject>>::iterator ReleaseStartIter = Childs.begin();
	std::list<std::shared_ptr<GameEngineObject>>::iterator ReleaseEndIter = Childs.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		std::shared_ptr<GameEngineObject>& Object = *ReleaseStartIter;

		if (false == Object->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = Childs.erase(ReleaseStartIter);
	}
}

void GameEngineObject::AllAccTime(float _DeltaTime)
{
	if (false == IsUpdate())
	{
		return;
	}

	AccLiveTime(_DeltaTime);

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllAccTime(_DeltaTime);
	}
}

void GameEngineObject::AllUpdate(float _DeltaTime)
{
	if (false == IsUpdate())
	{
		return;
	}

	Update(_DeltaTime);

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllUpdate(_DeltaTime);
	}
}
void GameEngineObject::AllRender(float _DeltaTime)
{
	if (false == IsUpdate())
	{
		return;
	}

	Render(_DeltaTime);

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllRender(_DeltaTime);
	}

}
void GameEngineObject::AllRelease()
{
	if (true == IsDeath())
	{
		return;
	}

	Release();

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllRelease();
	}

}

bool GameEngineObject::IsDeath()
{
	// 트랜스폼의 부모를 받아온다. 
	GameEngineTransform* Trans = GetTransform()->GetParent();

	// 만약 부모가 있다면 
	if (nullptr != Trans)
	{
		// 부모의 액터를 받아오고 
		GameEngineObject* Master = Trans->GetMaster();

		// 나, 또는 부모의 death 밸류가 true 라면 Death 인것으로 처리, true 그게 아니라면 false 
		return GameEngineObjectBase::IsDeath() || Master->IsDeath();
	}


	// 부모가 없다면 나의 데스밸류값만
	return GameEngineObjectBase::IsDeath();
}

// 마찬가지 
bool GameEngineObject::IsUpdate()
{
	GameEngineTransform* Trans = GetTransform()->GetParent();

	if (nullptr != Trans)
	{
		GameEngineObject* Master = Trans->GetMaster();

		return GameEngineObjectBase::IsUpdate() && Master->IsUpdate();
	}

	return GameEngineObjectBase::IsUpdate();
}

void GameEngineObject::AllLevelChangeStart()
{
	LevelChangeStart();

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllLevelChangeStart();
	}
}
void GameEngineObject::AllLevelChangeEnd()
{
	LevelChangeEnd();

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllLevelChangeEnd();
	}
}