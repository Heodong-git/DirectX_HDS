#pragma once

// 설명 :
class GameEngineShader
{
public:
	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

protected:

private:
	// Hlsl 사람들이 점점 아예 니가쳐

	// 쉐이더 코드를 2진데이터로 변형했을때 그걸 그래픽카드가 내부에 숨기고
	// 우리에게는 
	ID3DBlob* BinaryCode;
	std::string Version;

};

