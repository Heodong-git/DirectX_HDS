#pragma once
#include <list>
#include <memory>
#include <string_view>

// ���� :
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	// �굵 ���������Լ�ó�� ���־���� �� ����
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

	// ������ 
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

//                                                         GameEngineNameObject <-- ��� �׳� ���� ���߻�� 
//                               GameEngineObjectBase      -  GameEngineTransform
//                                 GameEngineObject    
//								GameEngineUpdateObject
//			      Actor					Level              Component 
//                                                                 Renderer