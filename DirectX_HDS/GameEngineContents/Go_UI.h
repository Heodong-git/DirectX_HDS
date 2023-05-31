#pragma once
#include "BaseActor.h"

// 설명 :
class Go_UI : public BaseActor
{
public:
	// constrcuter destructer
	Go_UI();
	~Go_UI();

	// delete Function
	Go_UI(const Go_UI& _Other) = delete;
	Go_UI(Go_UI&& _Other) noexcept = delete;
	Go_UI& operator=(const Go_UI& _Other) = delete;
	Go_UI& operator=(Go_UI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Move(float _DeltaTime);
	float4 m_StartPos = float4 { 500, 100 };
	float  m_MoveTime = 1.0f;
	float  m_MoveSpeed = 50.0f;

	// 렌더러생성 및 세팅
	void ComponentSetting();
	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_SubRender = nullptr;
};
