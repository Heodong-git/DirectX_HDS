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

// ShowCursor(false); 마우스 off 
// ShowCursor(ture); 마우스 on
// 특정한 상황에서 액터 업데이트 on off 와 동시에 수행 ㄱㄱ 마우스가 보이면 actor off, 마우스가 안보이면 actor on 
// 주의점 2번 false 호출했으면 ture 두번 호출해야 보임. 이거만 유의 

void Cursor::Start()
{
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Cursor");

		// 파일 전체로드 
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

	// 화면의 깊이가 0 인 점을 구하기 위해 projection matrix 와 view matrix 를 곱한 뒤,
	// 그 결과에 inverse matrix 를 곱해줍니다.
	float4 cursorPos3D = DirectX::XMVectorSet(x, y, 0.0f, 1.0f);
	float4x4 invViewProj = DirectX::XMMatrixInverse(nullptr, ViewProjection);
	cursorPos3D = DirectX::XMVector4Transform(cursorPos3D, invViewProj);

	// 마우스 위치에 해당하는 점을 카메라가 바라보는 방향으로 끌어당기기 위해
	// 카메라의 위치에서 마우스 위치에 해당하는 점을 지나는 직선의 방향벡터를 구합니다.
	float4 cameraPos = DirectX::XMVectorSet(CameraPos.x, CameraPos.y, CameraPos.z, CameraPos.w);
	float4 rayDir = static_cast<float4>(DirectX::XMVector3Normalize(cursorPos3D - cameraPos));

	// 마우스 위치에 해당하는 점이 바닥면과 교차하는 지점을 계산합니다.
	// 이 지점은 카메라에서 바닥면을 향해 쏜 광선과 바닥면의 교점이기 때문에,
	// 카메라에서 이 교점까지의 거리를 계산하여 이를 이용해 카메라가 바라보는
	// 지점을 이동시킬 수 있습니다.
	float distanceToGround = DirectX::XMVectorGetY(cameraPos) / DirectX::XMVectorGetY(rayDir);
	float4 groundPos = cameraPos + (rayDir * distanceToGround);

	m_GameCursorPos = groundPos;

	GetTransform()->SetLocalPosition(m_GameCursorPos);
};
