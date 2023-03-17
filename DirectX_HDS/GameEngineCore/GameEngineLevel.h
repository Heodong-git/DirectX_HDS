#pragma once
#include <GameEngineBase\GameEngineTimeEvent.h>

// Ό³Έν :
class GameEngineLevel
{
	friend class GameEngineCore;

public:
	GameEngineTimeEvent TimeEvent;

	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;

private:

};

