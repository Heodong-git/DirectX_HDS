
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

struct Input
{
   
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;
	
    _Value.Pos.w = 1.0f;
    // 월드뷰프로젝션 곱 : mul 함수 사용
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutputValue.UV = _Value.UV;

    return OutputValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
} 

Texture2D BlinkTex : register(t2);

SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(Output _Value) : SV_Target0
{
    float4 Color = BlinkTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
 
    // 지정된 값이 0보다 작으면 현재 픽셀을 삭제한다.
    // 알파값이 0.1보다 작다면 -1, 크다면 
  
    Color.a = 0.4f;
    //if (0.3f <= Color.a)
    //{
    //    clip(-1);
    //}

    return Color;
}
