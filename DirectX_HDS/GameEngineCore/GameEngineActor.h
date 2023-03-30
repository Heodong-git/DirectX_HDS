#pragma once
#include "GameEngineObject.h"

// 설명 :
class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}
protected:
	// virtual 로 선언함으로써 자식클래스들은 이 함수들을 구현해도 되고, 안해도 된다.
	// 구현한다면 본인의 함수로, 구현하지 않는다면 부모클래스의 함수로 동작한다. 
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	class GameEngineLevel* Level = nullptr;
};

