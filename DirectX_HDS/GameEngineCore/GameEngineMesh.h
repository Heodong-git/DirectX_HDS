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
	// ����Ʈ���� ������
	// Vertexs <-- ����, �Ǵ� ��ġ�� �ǹ��ϴ� ���� 
	// �簢���� �׸��ٰ� ġ�� 4���� ���� ǥ���Ѵٰ� �� �� ��..��? 
	std::vector<float4> Vertexs;
};

