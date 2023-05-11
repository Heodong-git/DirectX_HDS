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