#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// ���� :
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

// 1. ��������Ʈ ������ Ŭ������ ��ӹ��� ��������Ʈ ���� Ŭ���� ����
// 2. Start �Լ��� �������̵� �ؼ� ���� ���� ������������ ����
// 3. Start �Լ� ���ο��� ������۸�ũ 