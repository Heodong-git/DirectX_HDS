#pragma once
#include "BaseActor.h"

// ���� :
class Cursor : public BaseActor
{
public:
	static Cursor* MainCursor;

public:
	// constrcuter destructer
	Cursor();
	~Cursor();

	// delete Function
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;

	float4 GetGameCursorPos()
	{
		return m_GameCursorPos;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender() const
	{
		return m_Render;
	}
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

	void DebugUpdate();

private:
	// ���� ���� �ι�ȣ���� ���¿��� ������ �ѹ� ȣ���ϰ� �Ǹ� 
	// �״�� �� �����̱� ������ Ƚ���� �����ؾ���
	void WindowCursorOn()
	{
		ShowCursor(true);
	}

	void WindowCursorOff()
	{
		ShowCursor(false);
	}


	// ���콺Ŀ�� �Ѿư���
	void FollowCursor();
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	float4 m_Scale = { 50.0f, 50.0f, 1.0f };
	float4 m_GameCursorPos = {};

	// ---------------------------- Debug ---------------------------
};
