#include "PrecompileHeader.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineMesh.h"
#include "GameEngineInputLayOut.h"

#include "GameEngineSpriteRenderer.h"

// ------------------------- 렌더유닛 -----------------------------
GameEngineRenderUnit::GameEngineRenderUnit()
{
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>();
}

void GameEngineRenderUnit::SetMesh(const std::string_view& _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (false == InputLayOutPtr->IsCreate() && nullptr != Pipe)
	{
		InputLayOutPtr->ResCreate(Mesh->GetVertexBuffer(), Pipe->GetVertexShader());
	}
}
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

	if (false == InputLayOutPtr->IsCreate() && nullptr != Mesh)
	{
		InputLayOutPtr->ResCreate(Mesh->GetVertexBuffer(), Pipe->GetVertexShader());
	}
}

void GameEngineRenderUnit::Render(float _DeltaTime)
{
	if (nullptr == Mesh)
	{
		MsgAssert("매쉬가 존재하지 않는 유니트 입니다");
	}

	if (nullptr == Pipe)
	{
		MsgAssert("파이프라인이 존재하지 않는 유니트 입니다");
	}

	InputLayOutPtr->Setting();

	Mesh->Setting();

	Pipe->RenderingPipeLineSetting();
	ShaderResHelper.Setting();

	UINT IndexCount = Mesh->IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
}

// ------------------------------ 렌더러 ------------------------------------------

GameEngineRenderer::GameEngineRenderer()
{
	BaseValue.ScreenScale = GameEngineWindow::GetScreenSize();
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	// 기본적으로는 메인카메라에 세팅
	PushCameraRender(0);


	HBSCControl(DynamicThis<GameEngineSpriteRenderer>(), 0.7f, 0.52f, 0.4f);
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

void GameEngineRenderer::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSColor = ControlColor;
}

void GameEngineRenderer::Render(float _Delta)
{
	BaseValue.Time.x += _Delta;
	BaseValue.Time.y = _Delta;

	// GameEngineDevice::GetContext()->VSSetConstantBuffers();
	// GameEngineDevice::GetContext()->PSSetConstantBuffers();

	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->Render(_Delta);
	}
}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLine(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	return Units[_index]->Pipe;
}

// 이걸 사용하게되면 이 랜더러의 유니트는 자신만의 클론 파이프라인을 가지게 된다.
std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLineClone(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	if (false == Units[_index]->Pipe->IsClone())
	{
		Units[_index]->Pipe = Units[_index]->Pipe->Clone();
	}

	return Units[_index]->Pipe;
}

void GameEngineRenderer::SetMesh(const std::string_view& _Name, int _index /*= 0*/)
{
	if (Units.size() + 1 <= _index)
	{
		MsgAssert("너무큰 랜더유니트 확장을 하려고 했습니다");
	}

	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];

	if (nullptr == Unit)
	{
		MsgAssert("존재하지 않는 랜더유니트를 사용하려고 했습니다.");
	}


	Unit->Mesh = GameEngineMesh::Find(_Name);
}

void GameEngineRenderer::SetPipeLine(const std::string_view& _Name, int _index)
{
	//if (0 >= Units.size())
	//{
	//	MsgAssert("랜더 유니트가 존재하지 않습니다.");
	//}

	if (Units.size() + 1 <= _index)
	{
		MsgAssert("너무큰 랜더유니트 확장을 하려고 했습니다");
	}

	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];

	if (nullptr == Unit)
	{
		MsgAssert("존재하지 않는 랜더유니트를 사용하려고 했습니다.");
	}


	Unit->SetPipeLine(_Name);

	if (true == Unit->ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = GetTransform()->GetTransDataRef();
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}

	if (true == Unit->ShaderResHelper.IsConstantBuffer("RenderBaseValue"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("RenderBaseValue", BaseValue);
	}

	GetTransform()->GetWorldMatrix();
}

void GameEngineRenderer::PushCameraRender(int _CameraOrder)
{
	GetLevel()->PushCameraRenderer(DynamicThis<GameEngineRenderer>(), _CameraOrder);
}

void GameEngineRenderer::CalSortZ(GameEngineCamera* _Camera)
{
	// View행렬로 해야 카메라가 원점에 오고 그 원점을 기준으로 카메라가 위치한곳의 z로 처리한다.

	switch (_Camera->ProjectionType)
	{
	case CameraType::Orthogonal:
	{
		// 직교 투영이기 때문에 카메라의 View행렬을 곱해서 원점을 기준으로 
	// 위치를 카메라의 원점을 기준으로한 위치로 바꾸고 그 z를 사용하면 확실한
	// 직교에서의 카메라와의 z거리가 된다.
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.z;
		break;
	}
	
	case CameraType::Perspective:
	{
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.Size();
		break;
	}
	default:
		break;
	}

}
