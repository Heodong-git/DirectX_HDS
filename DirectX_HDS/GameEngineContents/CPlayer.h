#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineCore/GameEngineActor.h>

class CPlayer : public GameEngineActor
{
public:
	// constrcuter destructer
	CPlayer();
	~CPlayer();

	// delete Function
	CPlayer(const CPlayer& _Other) = delete;
	CPlayer(CPlayer&& _Other) noexcept = delete;
	CPlayer& operator=(const CPlayer& _Other) = delete;
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;
	
	/*void TestSave(GameEngineSerializer _Ser)
	{
		_Ser.Write(TestName);
		_Ser.Write(TestAtt);
		_Ser.Write(TestDef);
	}

	void TestLoad(GameEngineSerializer _Ser)
	{
		_Ser.Read(TestName);
		_Ser.Read(TestAtt);
		_Ser.Read(TestDef);
	}*/

protected:
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	std::string m_Name = "ZERO";
	float	m_Att = 0.0f;
	float   m_Hp = 0.0f;
	float	m_HpMax = 20.0f;
	
};
