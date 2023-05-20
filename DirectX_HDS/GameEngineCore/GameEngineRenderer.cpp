#include "PrecompileHeader.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"

// ------------------------- 렌더유닛 -----------------------------
void GameEngineRenderUnit::SetPipeLine(const std::string_view& _Name)
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
}

void GameEngineRenderUnit::Render(float _DeltaTime)
{
	Pipe->RenderingPipeLineSetting();
	ShaderResHelper.Setting();
	Pipe->Render();
}






// ------------------------------ 렌더러 ------------------------------------------

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(DynamicThis<GameEngineRenderer>());
}

void GameEngineRenderer::RenderTransformUpdate(GameEngineCamera* _Camera)
{
	if (nullptr == _Camera)
	{
		assert(false);
		return;
	}

	GetTransform()->SetCameraMatrix(_Camera->GetView(), _Camera->GetProjection());
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

	Pipe->RenderingPipeLineSetting();


	GameEngineActor* check = GetActor();
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
		const TransformData& Data = GetTransform()->GetTransDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}

	GetTransform()->GetWorldMatrix(); // ? 
}