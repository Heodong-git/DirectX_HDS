#pragma once
#include <random>

// 랜덤한 값을 받아내기 위한 클래스
class GameEngineRandom
{

public:
	static GameEngineRandom MainRandom;

	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		// 이게 Creater
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution <float> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	void SetSeed(__int64 _Seed) 
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:


private:
	// 랜덤 제너레이터 클래스와 => 여러개가 될수 있다.
	// 메르센 트위스터 알고리즘을 사용한 제네러이터
	std::mt19937_64 MtGen = std::mt19937_64();
	
	// 랜덤 크리에이터 클래스 => 1개
};

