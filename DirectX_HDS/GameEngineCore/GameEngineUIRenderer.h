#pragma once
#include "GameEngineSpriteRenderer.h"

// ���� :
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

	// UI�� ���, �������� UIRenderer Ŭ������ �����ϰ� �Ǹ� 
	// UIRender�� Start �Լ����� �ڵ����� UI ī�޶�� ���õǰ�, ���������� ����
	void Start() override;

private:

};

