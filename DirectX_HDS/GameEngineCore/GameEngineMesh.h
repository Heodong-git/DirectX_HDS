#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	static void Create(const std::string_view& _Name, const std::vector<float4>& _Vertexs)
	{
		std::shared_ptr<GameEngineMesh> NewMesh = GameEngineResource::Create(_Name);
	}

protected:

private:
	// 소프트웨어 렌더링
	// Vertexs <-- 정점, 또는 위치를 의미하는 개념 
	// 사각형을 그린다고 치면 4개의 점을 표현한다고 볼 수 있..나? 

	// 최초의 버텍스의 위치를 로컬공간이라고 한다. 
	// 대부분의 모든 메쉬는 1크기로 해서 넣을 수 있도록 만든다. 아닌곳도 있음 
	std::vector<float4> Vertexs;
};

// 메쉬 회전시키기
// Angle * 값 <--- 회전속도(?) 
// 준비해야할 것 
// 1. 메쉬의 각 버텍스
// 2. 버텍스를 저장할 POINT 배열 <-- 그리는 함수에 필요, 위치를 형변환하여 넣음
// 3. 크기, 자전, 이동으로 연산 <-- 하기전에 각도를 구해줌
// 4. 포인트배열에 넣어주고 Polygon <--- 함수로 그려준다. 
// 보통 버텍스는 합 1의 크기 (0.5,0.5) 로 설정하고 * Scale 로 크기를 늘려준다. 
// 모든회사 공통은 아니지만 대부분은 그렇다. 
// 크기, 자전, 이동 //////     공전, 부모의 ..? ㅋㅋㅋ
// 메쉬를 이동시키기 전에 존재하는 공간을 로컬공간(로컬스페이스) 
// 이동 시킨 후 출력되어 보여지는 공간을 월드공간(월드스페이스) 라고 합니다. 
