#pragma once
#include "BaseActor.h"

// 설명 :
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
	// 만약 온을 두번호출한 상태에서 오프를 한번 호출하게 되면 
	// 그대로 온 상태이기 때문에 횟수를 주의해야함
	void WindowCursorOn()
	{
		ShowCursor(true);
	}

	void WindowCursorOff()
	{
		ShowCursor(false);
	}


	// 마우스커서 쫓아가기
	void FollowCursor();
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	float4 m_Scale = { 50.0f, 50.0f, 1.0f };
	float4 m_GameCursorPos = {};

	// ---------------------------- Debug ---------------------------
};
