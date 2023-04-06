#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include <memory>


void GameEngineCore::CoreResourcesInit()
{
	std::vector<float4> ArrVertex;
	ArrVertex.resize(24);
	// ¾Õ¸é
	ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
	ArrVertex[1] = { 0.5f, -0.5f,0.5f };
	ArrVertex[2] = { 0.5f, 0.5f,0.5f };
	ArrVertex[3] = { -0.5f, 0.5f,0.5f };

	// µÞ¸é
	ArrVertex[4] = ArrVertex[0].RotationXDegReturn(180.0f);
	ArrVertex[5] = ArrVertex[1].RotationXDegReturn(180.0f);
	ArrVertex[6] = ArrVertex[2].RotationXDegReturn(180.0f);
	ArrVertex[7] = ArrVertex[3].RotationXDegReturn(180.0f);

	// ¿ÞÂÊ¸é
	ArrVertex[8] = ArrVertex[0].RotationYDegReturn(90.0f);
	ArrVertex[9] = ArrVertex[1].RotationYDegReturn(90.0f);
	ArrVertex[10] = ArrVertex[2].RotationYDegReturn(90.0f);
	ArrVertex[11] = ArrVertex[3].RotationYDegReturn(90.0f);

	// ¿À¸¥ÂÊ
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

	GameEngineMesh::Create("Box", ArrVertex);
	GameEngineTexture::Create("Box", "C:www");

}

void GameEngineCore::CoreResourcesEnd()
{
	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
}