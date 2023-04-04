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
	// �Ҹ��� virtual �� �ϴ� ����
	// - ��ӹ��� �ڽ� Ŭ������ �Ҹ��ڸ� ����� ȣ���ϱ� ���ؼ�
	// �Ҹ��ڸ� ���� �����Լ��� ������ ����
	// 1. ������ ���������Լ��� ������ �Լ��� ���. 
	// ���� �����Լ��� ����� ����
	// 1. �ڽĿ��� �������̽��� �����ϱ� ���ؼ�
	// 2. �� Ŭ������ ��ü�� ������ ���ϰ� �ϱ� ���ؼ�
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// ������Ʈ ���� ���� , ��ȯ
	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// ������Ʈ On , Off 
	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	// ����, �ٷ� �״� �� �ƴ�
	void Death()
	{
		IsDeath = true;
	}

	// �����Ҵ��� �ѹ� ���̱� ���ؼ� string_view ���
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	// Ʈ������ ��ȯ 
	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; 
	bool IsDeath = false;	
	// ������Ʈ ����
	int Order = 0;

	////////////////////////////////////////////////////////////// Transform ���ϱ���
private:
	GameEngineTransform Transform;
};