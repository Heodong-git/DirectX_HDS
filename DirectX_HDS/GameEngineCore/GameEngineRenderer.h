#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// ���� :
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
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

	inline GameEngineShaderResHelper& GetShaderResHelper()
	{
		return ShaderResHelper;
	}

protected:
	void Start();
	void Render(float _Delta) override;

private:
	// ���������ΰ� ���̴����ҽ����۰� �������� �������� �Ǵ� ������� ����
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe = nullptr;
	GameEngineShaderResHelper ShaderResHelper;

	void RenderTransformUpdate(GameEngineCamera* _Camera);
};
