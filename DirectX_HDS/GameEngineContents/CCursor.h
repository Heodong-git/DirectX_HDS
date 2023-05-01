#pragma once
#include <GameEngineContents/CKatanaZero_Actor.h>

// 설명 :
class CCursor : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CCursor();
	~CCursor();

	// delete Function
	CCursor(const CCursor& _Other) = delete;
	CCursor(CCursor&& _Other) noexcept = delete;
	CCursor& operator=(const CCursor& _Other) = delete;
	CCursor& operator=(CCursor&& _Other) noexcept = delete;

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
