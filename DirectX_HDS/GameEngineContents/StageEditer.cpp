#include "PrecompileHeader.h"
#include "StageEditer.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTransform.h>
#include "Player.h"

StageEditer::StageEditer()
{
}

StageEditer::~StageEditer()
{
}

void StageEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	//if (ImGui::BeginMenu("PlayerState"))
	//{
	//	std::string Text = GameEngineString::AnsiToUTF8("LevelChange");
	//	ImGui::Text(Text.c_str());

	//	//Text = GameEngineString::AnsiToUTF8("Tutorial_Level");
	//	//if (ImGui::Button(Text.c_str()))
	//	//{
	//	//	// �׳� ȣ���ص� ���� ������
	//	//	GameEngineCore::ChangeLevel("TutorialLevel");
	//	//	ImGui::EndMenu();
	//	//	return;
	//	//}

	//	Text = GameEngineString::AnsiToUTF8("StageLevel_01");
	//	if (ImGui::Button(Text.c_str()))
	//	{
	//		ImGui::EndMenu();
	//		return;
	//	}

	//	Text = GameEngineString::AnsiToUTF8("TitleLevel");
	//	if (ImGui::Button(Text.c_str()))
	//	{
	//		ImGui::EndMenu();
	//		return;
	//	}

	//	ImGui::EndMenu();
	//}

	if (nullptr != Player::MainPlayer)
	{
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		PlayerState CurState = Player::MainPlayer->GetCurState();

		if (ImGui::Begin("Player State"))
		{
			// ���� �߰��ϰ� ���� �ʺ� �����մϴ�.
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100);

			// ù ��° ���� ��ġ ������ ǥ���մϴ�.
			ImGui::Text("Position");
			ImGui::NextColumn();
			ImGui::Text("X: %.2f", PlayerPos.x);
			ImGui::NextColumn();
			ImGui::Text("");
			ImGui::NextColumn();
			ImGui::Text("Y: %.2f", PlayerPos.y);
			ImGui::NextColumn();
			ImGui::Text("");
			ImGui::NextColumn();
			ImGui::Text("Z: %.2f", PlayerPos.z);
			ImGui::NextColumn();

			// �� ��° ���� ȸ�� ������ ǥ���մϴ�.
			
			ImGui::NextColumn();
			ImGui::Text("W: %.2f", PlayerPos.w);
			ImGui::NextColumn();
			ImGui::Text("CurrentState");
			ImGui::NextColumn();
			switch (CurState)
			{
			case PlayerState::NONE:
				ImGui::Text("NONE ?");
				break;
			case PlayerState::ILDETORUN:
				ImGui::Text("Idle_to_run");
				break;
			case PlayerState::IDLE:
				ImGui::Text("Idle");
				break;
			case PlayerState::MOVE:
				ImGui::Text("Move");
				break;
			case PlayerState::JUMP:
				ImGui::Text("Jump");
				break;
			case PlayerState::SLASH:
				ImGui::Text("Slash");
				break;
			case PlayerState::CROUCH:
				ImGui::Text("Crouch");
				break;
			case PlayerState::FLIP:
				ImGui::Text("Flip");
				break;
			}

			ImGui::End();
		}
	}

	

	
}
