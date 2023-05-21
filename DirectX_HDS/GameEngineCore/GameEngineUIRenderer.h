#pragma once
#include "GameEngineSpriteRenderer.h"

// 설명 :
class GameEngineUIRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	// delete Function
	GameEngineUIRenderer(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _Other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer& operator=(GameEngineUIRenderer&& _Other) noexcept = delete;

protected:

	// UI의 경우, 렌더러를 UIRenderer 클래스로 생성하게 되면 
	// UIRender의 Start 함수에서 자동으로 UI 카메라로 세팅되고, 파이프라인 세팅
	void Start() override;

private:

};

