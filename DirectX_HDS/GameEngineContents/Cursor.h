#pragma once
#include <GameEngineContents/CKatanaZero_Actor.h>

// 설명 :
class Cursor : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	Cursor();
	~Cursor();

	// delete Function
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;

	float4 TestColor;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 마우스커서 쫓아가기
	void FollowCursor();
	std::shared_ptr<class GameEngineRenderer> m_Renderer = nullptr;
	float4 m_Scale = { 50.0f, 50.0f, 50.0f };
};
