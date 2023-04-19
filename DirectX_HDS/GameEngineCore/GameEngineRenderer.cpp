#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>


#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}


void GameEngineRenderer::Render(float _Delta)
{
	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	// GameEngineDevice::GetContext()->VSSetConstantBuffers();
	// GameEngineDevice::GetContext()->PSSetConstantBuffers();

	// 쉐이더가 어떤 텍스쳐, 어떤 상수버퍼를 사용할 것인지 여기서 세팅한다.
	ShaderResHelper.Setting();

	Pipe->Render();
}

void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	if (true == ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		// 여기서 월드뷰프로젝션 * 수행
		const float4x4& World = GetTransform()->GetWorldViewProjectionMatrixRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", World);
	}

	GetTransform()->GetWorldMatrix();
}