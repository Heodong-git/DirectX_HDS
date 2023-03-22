#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineMesh : public GameEngineResource
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

protected:

private:
	// 소프트웨어 렌더링
	// Vertexs <-- 정점, 또는 위치를 의미하는 개념 
	// 사각형을 그린다고 치면 4개의 점을 표현한다고 볼 수 있..나? 
	std::vector<float4> Vertexs;
};

