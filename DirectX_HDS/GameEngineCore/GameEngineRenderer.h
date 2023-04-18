#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// 설명 :
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

	// 파이프라인 세팅
	// 사용할 쉐이더, 쉐이더에서 어떤 텍스쳐를 사용할지, 샘플러, 상수버퍼는 어떤것을 사용했는지 알아야한다. 
	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _Delta) override;

private:
	// 파이프라인과 쉐이더리소스헬퍼가 합쳐져야 렌더링이 되는 방식으로 구현
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe;
	GameEngineShaderResHelper ShaderResHelper;
};
