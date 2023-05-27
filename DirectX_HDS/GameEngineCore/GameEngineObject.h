#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// 다중상속 
class GameEngineObject : 
	public GameEngineObjectBase, 
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject>
{
	// 
	friend class GameEngineComponent;
	friend class GameEngineActor;
	friend class GameEngineCore;
	friend class GameEngineTransform;
	friend class GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineObject();
	// 소멸자 virtual 로 하는 이유
	// - 상속받은 자식 클래스의 소멸자를 제대로 호출하기 위해서
	// 소멸자를 순수 가상함수로 선언한 이유
	// 1. 마땅히 순수가상함수로 선언할 함수가 없어서. 
	// 순수 가상함수를 만드는 이유
	// 1. 자식에게 인터페이스를 강요하기 위해서
	// 2. 이 클래스의 객체를 만들지 못하게 하기 위해서
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}

	// 게임엔진오브젝트를 상속받은 클래스가 shared ptr을 사용하려고 할 때 
	// 객체에서 호출하게 되면 shared ptr 을 dynamic cast 로 해당하는 클래스로 형변환 하여 반환
	template<typename PtrType>
	std::shared_ptr<PtrType> DynamicThis()
	{
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}

	virtual void AccLiveTime(float _LiveTime)
	{
		LiveTime += _LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	bool IsDeath() override;
	bool IsUpdate() override;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Release();
	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	void PushChild(std::shared_ptr<GameEngineObject> _Child)
	{
		Childs.push_back(_Child);
	}


private:
	float LiveTime = 0.0f;
	GameEngineTransform Transform;

	std::list<std::shared_ptr<GameEngineObject>> Childs;
	class GameEngineLevel* Level = nullptr;

	// 재귀함수로 구현하여 자식이 있다면 자식들의 업데이트,렌더 등을 진행해준다. 
	void AllAccTime(float _DeltaTime);
	void AllUpdate(float _DeltaTime);
	void AllRender(float _DeltaTime);
	void AllRelease();
	void AllLevelChangeStart();
	void AllLevelChangeEnd();
};