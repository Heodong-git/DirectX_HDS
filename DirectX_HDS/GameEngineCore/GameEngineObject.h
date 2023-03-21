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

	// ������Ʈ On , Off 
	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	// �����Ҵ��� �ѹ� ���̱� ���ؼ� string_view ���
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; 
	bool IsDeath = false;

	// shared ptr �� ��ȯ������ �����ϱ� ���� �θ��� �ּҰ��� shared ptr X
	GameEngineObject* Parent = nullptr;
	std::list<std::shared_ptr<GameEngineObject>> Childs;
};