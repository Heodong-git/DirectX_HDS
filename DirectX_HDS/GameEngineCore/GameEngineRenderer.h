#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// ���� :
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// ���������� ����
	// ����� ���̴�, ���̴����� � �ؽ��ĸ� �������, ���÷�, ������۴� ����� ����ߴ��� �˾ƾ��Ѵ�. 
	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _Delta) override;

private:
	// ���������ΰ� ���̴����ҽ����۰� �������� �������� �Ǵ� ������� ����
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe;
	GameEngineShaderResHelper ShaderResHelper;
};
