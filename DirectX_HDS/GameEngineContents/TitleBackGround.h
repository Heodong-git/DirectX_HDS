#pragma once
#include "BaseActor.h"

// 설명 : 타이틀에서만씀 
class TitleBackGround : public BaseActor
{
public:
	// constrcuter destructer
	TitleBackGround();
	~TitleBackGround();

	// delete Function
	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(TitleBackGround&& _Other) noexcept = delete;


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
