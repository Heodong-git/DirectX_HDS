
// 0~ 16번 슬롯이 있고
// 선언해 놨다고 사용한다는 의미가 아니다.
// 0번슬롯을 사용하겠다고 하는 의미가 된다. 
// constantbuffer (상수버퍼) : 장면의 물체마다 달라지는 상수 데이터를 담기 위한 저장공간
cbuffer TransformData : register(b0)
{
    float4x4 WorldMatrix;
}

// 1. 어떤 정보가 들어올지 구조체로 만들어야 함
// 2. 어디가 포지션, 어디가 컬러인지
// 3. 이름은 내가 정하면 된다.
struct Input
{
	// 시맨틱 : 인풋 구조체의 변수들이 어떤 자료와 연결될 지 알려주는 것
    
    //           각각의 변수가 어떤 역할인지
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    // 레스터라이저에게 보내는 정보 
    // w 값으로 나눈 후 뷰포트 곱하고 픽셀을 건져낼 때 사용할 포지션 정보를 보낸 거야
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

Output Texture_VS(Input _Value)
{
    Output OutPutValue = (Output)0;
	
    _Value.Pos.w = 1.0f;
    // 월드매트릭스 곱 : mul 함수를 사용하여 가능
    OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // _Value.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// 0번째 타겟에 출력하라는 의미가 된다. 
float4 Texture_PS(Output _Value) : SV_Target0
{
    return OutColor;
}

// 아래 과정을 생략하여 위 코드처럼 작성이 가능하다. 
//struct OutColor
//{
//    // 깔아놓은 도화지중 0번째 도화지에 출력해라.
//    float4 Color : SV_Target0;
//};

//OutColor Texture_PS(Output _Value)
//{
//    OutColor ReturnColor = (OutColor) 0;
//    ReturnColor.Color = _Value.Color;
//    return ReturnColor;
//}
