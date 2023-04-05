#pragma once
#include "GameEngineActor.h"

// 설명 :
class GameEngineComponent : public GameEngineUpdateObject
{
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	class GameEngineActor* GetActor()
	{
		return Actor;
	}

	class GameEngineLevel* GetLevel()
	{
		// 예외처리?? 
		return Actor->GetLevel();
	}
protected:

private:
	class GameEngineActor* Actor = nullptr;
	void SetActor(class GameEngineActor* _Actor);
};

