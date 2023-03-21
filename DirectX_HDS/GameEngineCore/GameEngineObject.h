#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include <memory>

class GameEngineObject
{
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

	// 부모클래스 세팅, 반환
	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	GameEngineObject* GetParent()
	{
		return Parent;
	}

protected:

	// virtual 로 선언함으로써 자식클래스들은 이 함수들을 구현해도 되고, 안해도 된다.
	// 구현한다면 본인의 함수로, 구현하지 않는다면 부모클래스의 함수로 동작한다. 
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	std::string Name = "";
	bool IsActive = true; 
	bool IsDeath = false;

	// shared ptr 의 순환참조를 방지하기 위해 부모의 주소값은 shared ptr X
	// 순환참조 : shared ptr 로 만들어낸 객체가 서로가 서로를 shared_ptr로 가질 경우 발생하는 문제 
	// 카운트가 1 밑으로 떨어지지 않아서 메모리 릭이 남게 된다. 

	// 업데이트 오더
	int Order = 0;
	GameEngineObject* Parent = nullptr;
	std::list<std::shared_ptr<GameEngineObject>> Child;

	////////////////////////////////////////////////////////////// Transform 기하구조
public:
	float4 GetPos()
	{
		return Pos;
	}

private:
	float4 Pos = float4::Zero;
};