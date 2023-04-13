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

#include "GameEngineVertexShader.h"

void GameEngineCore::CoreResourcesInit()
{
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
	}


	{
		{
			// 파이프라인 세팅
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			// 코어리소스 초기화에서 생성한 리소스 중에서 어떤종류를 사용할지 세팅
			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
		}
	}
}

// 
void GameEngineCore::CoreResourcesEnd()
{
	// 생성한 리소스들을 모두 제거해준다. 
	// shard ptr 사용으로 인해 레퍼런스카운트가 0 이되면 자동으로 제거되지만
	// 원하는시점에 제거하기 위해서. 
	GameEngineResource<GameEngineVertexShader>::ResourcesClear();
	GameEngineResource<GameEngineVertexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
	GameEngineResource<GameEngineRenderTarget>::ResourcesClear();
}