#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"

class GameEngineObject : public GameEngineObjectBase
{
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
protected:

private:
	
	////////////////////////////////////////////////////////////// Transform 기하구조
private:
	GameEngineTransform Transform;
};