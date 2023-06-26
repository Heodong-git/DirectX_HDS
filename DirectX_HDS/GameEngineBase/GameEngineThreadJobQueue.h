#pragma once
#include <functional>
#include <Windows.h>

// Ό³Έν :
class GameEngineThreadJobQueue
{
public:
	// constrcuter destructer
	GameEngineThreadJobQueue(int _ThreadCount);
	~GameEngineThreadJobQueue();

	// delete Function
	GameEngineThreadJobQueue(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue(GameEngineThreadJobQueue&& _Other) noexcept = delete;
	GameEngineThreadJobQueue& operator=(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue& operator=(GameEngineThreadJobQueue&& _Other) noexcept = delete;

	void Work(std::function<void()> _Work);

protected:

private:

};

