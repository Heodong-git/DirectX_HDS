#pragma once
#include <GameEngineContents/CKatanaZero_Actor.h>

// 설명 : 타이틀에서만씀 
class CBackGround : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CBackGround();
	~CBackGround();

	// delete Function
	CBackGround(const CBackGround& _Other) = delete;
	CBackGround(CBackGround&& _Other) noexcept = delete;
	CBackGround& operator=(const CBackGround& _Other) = delete;
	CBackGround& operator=(CBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


private:
	void CreateRender();

	float4 m_StartPoint = { 0 , 350 , 0};
	float  m_MoveSpeed = 370.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGroundRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGroundBlackRender = nullptr;
};
