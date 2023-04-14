#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"

#include "GameEngineVertexShader.h"

void GameEngineCore::CoreResourcesInit()
{
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);

	//typedef struct D3D11_INPUT_ELEMENT_DESC
	//{
	//	LPCSTR SemanticName; = "POSITION"
	//	UINT SemanticIndex; = 0
	//	DXGI_FORMAT Format; 
	//	UINT InputSlot;
	//	UINT AlignedByteOffset;
	//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	//	UINT InstanceDataStepRate; 
	//} 	


	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	//UINT NumElements, // 
	//const void* pShaderBytecodeWithInputSignature,  // 쉐이더의 바이너리 코드를 내놔
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout // 만들어져 나오는 포인터

	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f,0.0f }, float4::Red };
		ArrVertex[2] = { { 0.5f, -0.5f,0.0f }, float4::Red };
		ArrVertex[3] = { { -0.5f, -0.5f,0.0f }, float4::Red };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 3, 2 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);


		// GameEngineMesh::Create("Rect", ArrVertex);
		// GameEngineMesh::Create("Rect");
		//GameEngineMesh::Create("Box");
	}

	{
		// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// 앞면
		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		// 뒷면
		ArrVertex[4] = ArrVertex[0].RotationXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotationXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotationXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotationXDegReturn(180.0f);

		// 왼쪽면
		ArrVertex[8] = ArrVertex[0].RotationYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotationYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotationYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotationYDegReturn(90.0f);

		// 오른쪽
		ArrVertex[12] = ArrVertex[0].RotationYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotationYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotationYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotationYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotationXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotationXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotationXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotationXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotationXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotationXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotationXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotationXDegReturn(-90.0f);

	}

	// 버텍스쉐이더 컴파일
	{
		GameEngineDirectory NewDir;
		// 인자로 입력한 폴더가 존재하는 디렉터리로 이동
		NewDir.MoveParentToDirectory("Shader");
		// 이동
		NewDir.Move("Shader");
		// 해당하는 파일을 받아온다. 
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		// 일단 현시점에서는 이렇게. 
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};

		//D3D11_FILL_MODE FillMode;
		// 렌더링할 때 사용할 채우기 모드를 결정합니다( D3D11_FILL_MODE 참조 ).
		//D3D11_CULL_MODE CullMode;
		// 지정된 방향을 향하는 삼각형이 그려지지 않음을 나타냅니다( D3D11_CULL_MODE 참조 ).
		//BOOL FrontCounterClockwise;
		// 삼각형이 앞면인지 뒷면인지 결정합니다. 
		// 이 매개변수가 TRUE 이면 정점 이 렌더 대상에서 
		// 시계 반대 방향이면 삼각형이 전면을 향하는 것으로 
		// 간주되고 시계 방향이면 후면을 향하는 것으로 간주됩니다. 
		// 이 매개변수가 FALSE 이면 그 반대입니다.
		//INT DepthBias;
		// 지정된 픽셀에 추가된 깊이 값입니다. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//FLOAT DepthBiasClamp;
		// 픽셀의 최대 깊이 편향. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//FLOAT SlopeScaledDepthBias;
		// 주어진 픽셀의 기울기에 대한 스칼라. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//BOOL DepthClipEnable;
		// 거리에 따라 클리핑을 활성화합니다.
		// 하드웨어는 항상 래스터화된 좌표의 x 및 y 클리핑을 수행합니다.
		// DepthClipEnable이 기본값인 TRUE 로 설정 되면 하드웨어도 z 
		// 값을 자릅니다(즉, 하드웨어는 다음 알고리즘의 마지막 단계를 수행합니다).
		//BOOL ScissorEnable;
		// 가위 사각형 컬링을 활성화합니다. 활성 가위 사각형 외부의 모든 픽셀이 추려집니다.
		//BOOL MultisampleEnable;
		// 다중 샘플 앤티앨리어싱(MSAA) 렌더 대상에서 사변형 또는 알파 라인 앤티앨리어싱 
		// 알고리즘을 사용할지 여부를 지정합니다. 사변형 라인 앤티 앨리어싱 알고리즘을 
		// 사용하려면 TRUE 로 설정 하고 알파 라인 앤티 앨리어싱 알고리즘을 사용하려면 
		// FALSE 로 설정합니다. 이 멤버에 대한 자세한 내용은 비고를 참조하세요.
		//BOOL AntialiasedLineEnable;
		// 선 앤티앨리어싱을 활성화할지 여부를 지정합니다. 선 그리기를 수행하고 MultisampleEnable이 
		// FALSE 인 경우에만 적용됩니다 . 이 멤버에 대한 자세한 내용은 비고를 참조하세요.

		// 와이어 프레임은 선으로 표현하는 겁니다. 
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		Desc.FrontCounterClockwise = TRUE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("EngineBase", Desc);
	}
	
	{
		{
			// 파이프라인 세팅
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			// 코어리소스 초기화에서 생성한 리소스 중에서 어떤종류를 사용할지 세팅
			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("EngineBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
		}
	}
}

// 
void GameEngineCore::CoreResourcesEnd()
{
	// 생성한 리소스들을 모두 제거해준다. 
	// shard ptr 사용으로 인해 레퍼런스카운트가 0 이되면 자동으로 제거되지만
	// 원하는시점에 삭제되는 것을 확실히 하기 위해서
	GameEngineResource<GameEnginePixelShader>::ResourcesClear();
	GameEngineResource<GameEngineRasterizer>::ResourcesClear();
	GameEngineResource<GameEngineVertexShader>::ResourcesClear();
	GameEngineResource<GameEngineIndexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineVertexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
	GameEngineResource<GameEngineRenderTarget>::ResourcesClear();
}