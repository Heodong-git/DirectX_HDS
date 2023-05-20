#include "PrecompileHeader.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
}

// UI 렌더러는 스타트에서 카메라 100번 ( 유아이카메라 ) 세팅
void GameEngineUIRenderer::Start()
{
	PushCameraRender(100);
	SpriteRenderInit();
}
