#include "PrecompileHeader.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
}

// UI �������� ��ŸƮ���� ī�޶� 100�� ( ������ī�޶� ) ����
void GameEngineUIRenderer::Start()
{
	PushCameraRender(100);
	SpriteRenderInit();
}
