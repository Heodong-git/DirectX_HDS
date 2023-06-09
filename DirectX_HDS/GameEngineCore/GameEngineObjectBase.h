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

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// 자식에서 해당 함수 호출시, 수행할 작업이 있다면
	// 오버라이드하여 사용하기 위해 virtual  
	virtual void On()
	{
		UpdateValue = true;
	}

	virtual void Off()
	{
		UpdateValue = false;
	}

	virtual void Death()
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
		return UpdateValue && (false == DeathValue);
	}


	void DebugOn()
	{
		DebugValue = true;
	}

	void DebugOff()
	{
		DebugValue = false;
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