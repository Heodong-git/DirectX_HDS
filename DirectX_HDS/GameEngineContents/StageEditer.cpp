#include "PrecompileHeader.h"
#include "StageEditer.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"

StageEditer::StageEditer()
{
}

StageEditer::~StageEditer()
{
}

void StageEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	// �÷��̾� ����� 
	if (nullptr != Player::MainPlayer)
	{
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		PlayerState CurState = Player::MainPlayer->GetCurState();

		std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
		float4 CameraPos = CurLevel->GetMainCamera()->GetTransform()->GetLocalPosition();
		
        if (ImGui::Begin("Debug"))
        {
            // �÷��̾� ��ġ ����
            ImGui::Text("Player Position:");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);
            ImGui::Text("Camera Position:");
            ImGui::Separator();

            ImGui::Columns(4, nullptr, true);
            ImGui::SetColumnWidth(0, 60);
            ImGui::SetColumnWidth(1, 80);
            ImGui::SetColumnWidth(2, 60);
            ImGui::SetColumnWidth(3, 80);

            ImGui::Text("X:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", PlayerPos.x);
            ImGui::NextColumn();
            ImGui::Text("X:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", CameraPos.x);
            ImGui::NextColumn();

            ImGui::Text("Y:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", PlayerPos.y);
            ImGui::NextColumn();
            ImGui::Text("Y:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", CameraPos.y);
            ImGui::NextColumn();

            ImGui::Text("Z:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", PlayerPos.z);
            ImGui::NextColumn();
            ImGui::Text("Z:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", CameraPos.z);
            ImGui::NextColumn();

            ImGui::Text("W:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", PlayerPos.w);
            ImGui::NextColumn();
            ImGui::Text("W:");
            ImGui::NextColumn();
            ImGui::Text("%.2f", CameraPos.w);
            ImGui::NextColumn();

            ImGui::Columns(1);
            ImGui::Separator();

            // �÷��̾� ����
            ImGui::Text("Player State: ");
            switch (CurState)
            {
            case PlayerState::NONE:
                ImGui::SameLine();
                ImGui::Text("NONE ?");
                break;
            case PlayerState::ILDETORUN:
                ImGui::SameLine();
                ImGui::Text("Idle_to_run");
                break;
            case PlayerState::IDLE:
                ImGui::SameLine();
                ImGui::Text("Idle");
                break;
            case PlayerState::MOVE:
                ImGui::SameLine();
                ImGui::Text("Move");
                break;
            case PlayerState::JUMP:
                ImGui::SameLine();
                ImGui::Text("Jump");
                break;
            case PlayerState::SLASH:
                ImGui::SameLine();
                ImGui::Text("Slash");
                break;
            case PlayerState::CROUCH:
                ImGui::SameLine();
                ImGui::Text("Crouch");
                break;
            case PlayerState::FLIP:
                ImGui::SameLine();
                ImGui::Text("Flip");
                break;
            }
            ImGui::End();
        }

	}

	

	
}
