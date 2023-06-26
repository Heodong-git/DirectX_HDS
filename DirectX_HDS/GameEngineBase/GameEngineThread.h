#pragma once

// Ό³Έν :
class GameEngineThread
{
public:
	// constrcuter destructer
	GameEngineThread();
	~GameEngineThread();

	// delete Function
	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(GameEngineThread&& _Other) noexcept = delete;

protected:

private:

};

