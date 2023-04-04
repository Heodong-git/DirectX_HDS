#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

class GameEngineObject
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

	// 업데이트 순서 세팅 , 반환
	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// 업데이트 On , Off 
	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	// 데스, 바로 죽는 게 아님
	void Death()
	{
		IsDeath = true;
	}

	// 동적할당을 한번 줄이기 위해서 string_view 사용
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	// 트랜스폼 반환 
	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; 
	bool IsDeath = false;	
	// 업데이트 오더
	int Order = 0;

	////////////////////////////////////////////////////////////// Transform 기하구조
private:
	GameEngineTransform Transform;
};