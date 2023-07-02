#include "PrecompileHeader.h"
#include "StageEditer.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "BaseLevel.h"
#include "Player.h"
#include "Cursor.h"

#include "PixelCollider.h"

#include "ClubLevel_Boss_01.h"

#include "Boss_HeadHunter.h"

StageEditer::StageEditer()
{
}

StageEditer::~StageEditer()
{
}

void StageEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	// 플레이어 디버그 
	if (nullptr != Player::MainPlayer)
	{
        Player* mainplayer = Player::MainPlayer;
		float4 PlayerPos = mainplayer->GetTransform()->GetLocalPosition();
		PlayerState CurState = Player::MainPlayer->GetCurState();
        bool PlayerDir = Player::MainPlayer->GetDir();

		std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
        if (nullptr == CurLevel)
        {
            MsgAssert("레벨이 nullptr 입니다. ");
            return;
        }

		float4 CameraPos = CurLevel->GetMainCamera()->GetTransform()->GetLocalPosition();

        if (ImGui::Begin("Debug"))
        {
            // 플레이어 위치 정보
            ImGui::Text("Player Position:");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.27f);
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

            // 각 픽셀 컬러 
            // 플레이어 위치 정보
            ImGui::Text("Pixel Color :");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.27f);
            ImGui::Text("Debug Pixel:");
            ImGui::Separator();

            ImGui::Columns(4, nullptr, true);
            ImGui::SetColumnWidth(0, 60);
            ImGui::SetColumnWidth(1, 80);
            ImGui::SetColumnWidth(2, 60);
            ImGui::SetColumnWidth(3, 80);

            const std::vector<std::shared_ptr<GameEngineSpriteRenderer>>& Renders = mainplayer->GetDebugRenders();

            if (0 != Renders.size())
            {
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[0]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Bottom :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if(PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[1]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Top :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[2]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Left :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[3]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Right :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[4]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Wall L :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[5]->GetTransform()->GetWorldPosition());

                    ImGui::Text("Wall R :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text(" ??? ");
                    }
                    ImGui::NextColumn();
                }
                {
                    GameEnginePixelColor Color = PixelCollider::PixelCol->PixelCollision(Renders[6]->GetTransform()->GetWorldPosition());

                    ImGui::Text("B Down :");
                    ImGui::NextColumn();
                    if (PixelCollider::g_BlackPixel == Color)
                    {
                        ImGui::Text("Black");
                    }
                    else if (PixelCollider::g_WhitePixel == Color)
                    {
                        ImGui::Text("White");
                    }
                    else
                    {
                        ImGui::Text("Error");
                    }
                    ImGui::NextColumn();
                }
                ImGui::Columns(1);
                ImGui::Separator();
            }
           

            // 플레이어 상태
            ImGui::Text("Player State: ");
            switch (CurState)
            {
            case PlayerState::NONE:
                ImGui::SameLine();
                ImGui::Text("NONE ?");
                break;
            case PlayerState::IDLETORUN:
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
            case PlayerState::RIGHTFLIP:
                ImGui::SameLine();
                ImGui::Text("RightFlip");
                break;
            case PlayerState::LEFTFLIP:
                ImGui::SameLine();
                ImGui::Text("LeftFlip");
                break;
            case PlayerState::FALL:
                ImGui::SameLine();
                ImGui::Text("Fall");
                break;
            case PlayerState::ROLL:
                ImGui::SameLine();
                ImGui::Text("Roll");
                break;
            case PlayerState::RIGHTWALL:
                ImGui::SameLine();
                ImGui::Text("RightWall");
                break;
            case PlayerState::LEFTWALL:
                ImGui::SameLine();
                ImGui::Text("LeftWall");
                break;
            case PlayerState::DEATH:
                ImGui::SameLine();
                ImGui::Text("Death");
                break;
            case PlayerState::DOORBREAK:
                ImGui::SameLine();
                ImGui::Text("DoorBreak");
                break;
            }

            ImGui::Text("Dir : ");
            ImGui::SameLine();
            ImGui::Text(PlayerDir ? "Right" : "Left");

            if (nullptr != Cursor::MainCursor)
            {
                float4 CursorPos = Cursor::MainCursor->GetGameCursorPos();

                ImGui::Text("Mouse Position:");
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);

                ImGui::Separator();

                ImGui::Columns(4, nullptr, true);
                ImGui::SetColumnWidth(0, 60);
                ImGui::SetColumnWidth(1, 80);
                ImGui::SetColumnWidth(2, 60);
                ImGui::SetColumnWidth(3, 80);

                ImGui::Text("X:");
                ImGui::NextColumn();
                ImGui::Text("%.2f", CursorPos.x);
                ImGui::NextColumn();

                ImGui::Text("Slow :");
                ImGui::NextColumn();
                ImGui::Text("%s", Player::MainPlayer->IsSkill() ? "true" : "false");

              

                ImGui::NextColumn();
                ImGui::Text("Y:");
                ImGui::NextColumn();
                ImGui::Text("%.2f", CursorPos.y);
                ImGui::NextColumn();

                ImGui::Text("SkillTime :");
                ImGui::NextColumn();
                ImGui::Text("%.2f", Player::MainPlayer->GetSkillLimitTime());
                ImGui::NextColumn();


                ImGui::Columns(1);
                ImGui::Separator();
            }


            BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel.get());

            if (nullptr == CastLevel)
            {
                return;
            }

            {
                ImGui::Text("Level LimitTime :");
                ImGui::SameLine();
                ImGui::Text("%.2f", CastLevel->GetLimitTime());

                ImGui::Text("Level State :");
                ImGui::SameLine();
                BaseLevel::LevelState State = CastLevel->GetCurState();
                switch (State)
                {
                case BaseLevel::LevelState::WAIT:
                    ImGui::Text("WAIT");
                    break;
                case BaseLevel::LevelState::PLAY:
                    ImGui::Text("PLAY");
                    break;
                default:
                    break;
                }

                // 레벨 몬스터 카운트
                ImGui::Text("Monster Count :");
                ImGui::SameLine();
                ImGui::Text("%.2d", CastLevel->GetMonsterCount());

                if (LevelType::CLUBBOSS1 == CastLevel->GetLevelType())
                {
                    std::shared_ptr<ClubLevel_Boss_01> BossLevel = CastLevel->DynamicThis<ClubLevel_Boss_01>();
                    
                    std::shared_ptr<Boss_HeadHunter> HeadHunter = BossLevel->GetBossPtr();
                    if (nullptr != HeadHunter)
                    {
                        // 레벨 몬스터 카운트
                        ImGui::Text("Boss Hit Count :");
                        ImGui::SameLine();
                        ImGui::Text("%.2d", BossLevel->GetBossPtr()->GetPhase2_HitCount());
                    }
                   
                }
            }
            
            // 여기서 각 디버그 픽셀의 컬러 

            ImGui::End();
        }

	}

	

	
}
