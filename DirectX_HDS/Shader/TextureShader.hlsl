
// 1. 어떤 정보가 들어올지 구조체로 만들어야 함
// 2. 어디가 포지션, 어디가 컬러인지
// 3. 이름은 내가 정하면 된다.

struct Input
{
	// 시맨틱 : 인풋 구조체의 변수들이 어떤 자료와 연결될 지 알려주는 것
    
    //           각각의 변수가 어떤 역할인지
    float4 Pos : POSITIONT0;
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
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // _Value.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}