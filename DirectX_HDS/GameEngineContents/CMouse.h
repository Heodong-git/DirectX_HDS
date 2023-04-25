#pragma once
#include <GameEngineContents/CKatanaZero_Actor.h>

// 설명 :
class CMouse : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CMouse();
	~CMouse();

	// delete Function
	CMouse(const CMouse& _Other) = delete;
	CMouse(CMouse&& _Other) noexcept = delete;
	CMouse& operator=(const CMouse& _Other) = delete;
	CMouse& operator=(CMouse&& _Other) noexcept = delete;

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
