#pragma once
#include <string>
#include <list>
#include <memory>

class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// 업데이트 On , Off 
	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	// 동적할당을 한번 줄이기 위해서 string_view 사용
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; 
	bool IsDeath = false;

	// shared ptr 의 순환참조를 방지하기 위해 부모의 주소값은 shared ptr X
	GameEngineObject* Parent = nullptr;
	std::list<std::shared_ptr<GameEngineObject>> Childs;
};