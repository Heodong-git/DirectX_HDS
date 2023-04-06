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
	// ����Ʈ���� ������
	// Vertexs <-- ����, �Ǵ� ��ġ�� �ǹ��ϴ� ���� 
	// �簢���� �׸��ٰ� ġ�� 4���� ���� ǥ���Ѵٰ� �� �� ��..��? 

	// ������ ���ؽ��� ��ġ�� ���ð����̶�� �Ѵ�. 
	// ��κ��� ��� �޽��� 1ũ��� �ؼ� ���� �� �ֵ��� �����. �ƴѰ��� ���� 
	std::vector<float4> Vertexs;
};

// �޽� ȸ����Ű��
// Angle * �� <--- ȸ���ӵ�(?) 
// �غ��ؾ��� �� 
// 1. �޽��� �� ���ؽ�
// 2. ���ؽ��� ������ POINT �迭 <-- �׸��� �Լ��� �ʿ�, ��ġ�� ����ȯ�Ͽ� ����
// 3. ũ��, ����, �̵����� ���� <-- �ϱ����� ������ ������
// 4. ����Ʈ�迭�� �־��ְ� Polygon <--- �Լ��� �׷��ش�. 
// ���� ���ؽ��� �� 1�� ũ�� (0.5,0.5) �� �����ϰ� * Scale �� ũ�⸦ �÷��ش�. 
// ���ȸ�� ������ �ƴ����� ��κ��� �׷���. 
// ũ��, ����, �̵� //////     ����, �θ��� ..? ������
// �޽��� �̵���Ű�� ���� �����ϴ� ������ ���ð���(���ý����̽�) 
// �̵� ��Ų �� ��µǾ� �������� ������ �������(���彺���̽�) ��� �մϴ�. 
