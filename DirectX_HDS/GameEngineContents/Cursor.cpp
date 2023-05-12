#include "PrecompileHeader.h"
#include "Cursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BaseLevel.h"
#include "Player.h"
#include "PlayManager.h"

Cursor* Cursor::MainCursor = nullptr;

Cursor::Cursor()
{
	MainCursor = this;
}

Cursor::~Cursor()
{
}

// ShowCursor(false); ���콺 off 
// ShowCursor(ture); ���콺 on
// Ư���� ��Ȳ���� ���� ������Ʈ on off �� ���ÿ� ���� ���� ���콺�� ���̸� actor off, ���콺�� �Ⱥ��̸� actor on 
// ������ 2�� false ȣ�������� ture �ι� ȣ���ؾ� ����. �̰Ÿ� ���� 

void Cursor::Start()
{
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Cursor");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (false == GameEngineInput::IsKey("cursor_DebugSwitch"))
	{
		GameEngineInput::CreateKey("cursor_DebugSwitch", 'Q');
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->GetShaderResHelper().SetTexture("DiffuseTex", "cursor_0.png");
	m_Render->SetAtlasConstantBuffer();
	m_Render->GetTransform()->SetLocalScale(m_Scale);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender->SetPipeLine("2DTexture");
	m_DebugRender->SetAtlasConstantBuffer();
	m_DebugRender->GetTransform()->SetLocalScale( { 2, 2 });
}

void Cursor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("cursor_DebugSwitch"))
	{
		m_Debug = !m_Debug;
	}

	DebugUpdate();
	FollowCursor();
}

void Cursor::Render(float _DeltaTime)
{
}

void Cursor::DebugUpdate()
{
	if (true == m_Debug)
	{
		m_DebugRender->On();
	}
	else if (false == m_Debug)
	{
		m_DebugRender->Off();
	}
}

void Cursor::FollowCursor()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	float4 CursorPos = GameEngineWindow::GetMousePosition();


	float x = static_cast<float>(CursorPos.x) - ScreenSize.hx();
	float y = ScreenSize.hy() - static_cast<float>(CursorPos.y);

	float4x4 ViewProjection = GetTransform()->GetWorldViewProjectionMatrix();

	// ȭ���� ���̰� 0 �� ���� ���ϱ� ���� projection matrix �� view matrix �� ���� ��,
	// �� ����� inverse matrix �� �����ݴϴ�.
	float4 cursorPos3D = DirectX::XMVectorSet(x, y, 0.0f, 1.0f);
	float4x4 invViewProj = DirectX::XMMatrixInverse(nullptr, ViewProjection);
	cursorPos3D = DirectX::XMVector4Transform(cursorPos3D, invViewProj);

	// ���콺 ��ġ�� �ش��ϴ� ���� ī�޶� �ٶ󺸴� �������� ������� ����
	// ī�޶��� ��ġ���� ���콺 ��ġ�� �ش��ϴ� ���� ������ ������ ���⺤�͸� ���մϴ�.
	float4 cameraPos = DirectX::XMVectorSet(CameraPos.x, CameraPos.y, CameraPos.z, CameraPos.w);
	float4 rayDir = static_cast<float4>(DirectX::XMVector3Normalize(cursorPos3D - cameraPos));

	// ���콺 ��ġ�� �ش��ϴ� ���� �ٴڸ�� �����ϴ� ������ ����մϴ�.
	// �� ������ ī�޶󿡼� �ٴڸ��� ���� �� ������ �ٴڸ��� �����̱� ������,
	// ī�޶󿡼� �� ���������� �Ÿ��� ����Ͽ� �̸� �̿��� ī�޶� �ٶ󺸴�
	// ������ �̵���ų �� �ֽ��ϴ�.
	float distanceToGround = DirectX::XMVectorGetY(cameraPos) / DirectX::XMVectorGetY(rayDir);
	float4 groundPos = cameraPos + (rayDir * distanceToGround);

	m_GameCursorPos = groundPos;

	GetTransform()->SetLocalPosition(m_GameCursorPos);
};
