#pragma once
#include <list>
#include <memory>
#include <string_view>

// 설명 :
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	// 얘도 순수가상함수처리 해주어야할 것 같음
	~GameEngineObjectBase();

	// delete Function
	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void On()
	{
		UpdateValue = true;
	}

	void Off()
	{
		UpdateValue = false;
	}

	void Death()
	{
		DeathValue = true;
	}

	// ㅇㅇㅇ 
	virtual bool IsDeath()
	{
		return DeathValue;
	}

	virtual bool IsUpdate()
	{
		return UpdateValue;
	}


	void DebugOn()
	{
		DebugValue = true;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool UpdateValue = true;
	bool DeathValue = false; 
	bool DebugValue = false;
	int Order = 0;
};

//                                                         GameEngineNameObject <-- 얘는 그냥 따로 다중상속 
//                               GameEngineObjectBase      -  GameEngineTransform
//                                 GameEngineObject    
//								GameEngineUpdateObject
//			      Actor					Level              Component 
//                                                                 Renderer