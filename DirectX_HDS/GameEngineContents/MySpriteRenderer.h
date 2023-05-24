#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// 설명 :
class MySpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	MySpriteRenderer();
	~MySpriteRenderer();

	// delete Function
	MySpriteRenderer(const MySpriteRenderer& _Other) = delete;
	MySpriteRenderer(MySpriteRenderer&& _Other) noexcept = delete;
	MySpriteRenderer& operator=(const MySpriteRenderer& _Other) = delete;
	MySpriteRenderer& operator=(MySpriteRenderer&& _Other) noexcept = delete;

	void Start() override;

	float4 AColor;
protected:

private:

};

// 1. 스프라이트 렌더러 클래스를 상속받은 내프로젝트 전용 클래스 생성
// 2. Start 함수를 오버라이드 해서 내가 만든 파이프라인을 세팅
// 3. Start 함수 내부에서 상수버퍼링크 