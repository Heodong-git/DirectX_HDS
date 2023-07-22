struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut OldTV_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // 화면 전체 범위
    return OutPutValue;
}

cbuffer RenderBaseValue : register(b11)
{
    // 상수버퍼는 
    float4 Time;
    float4 ScreenSize;
    float4 Mouse;
}


Texture2D DiffuseTex : register(t0);
SamplerState WRAP : register(s0);

float2 getDistortion(float2 uv, float d, float t)
{
    uv.x += cos(d) + t * 0.9;
    uv.y += sin(d + t * 0.75);
   
    return uv;
}

float4 getDistortedTexture(SamplerState iChannel, float2 uv)
{
    float4 rgb = DiffuseTex.Sample(iChannel, uv);
    return rgb;
}

void mainImage(out float4 fragColor, in float2 fragCoord)
{
    // float2 uv = fragCoord.xy / ScreenSize.xy;
    float2 uv = fragCoord.xy;
    float t = Time.x;
    float2 mid = float2(0.5, 0.5);
    // float2 focus = Mouse.xy / ScreenSize.xy;
    float2 focus = Mouse.xy;
    float d1 = distance(focus + sin(t * 0.2) * 0.5, uv);
    float d2 = distance(focus + cos(t), uv);
    float4 rgb = (getDistortedTexture(WRAP, getDistortion(uv, d1, t)) + getDistortedTexture(WRAP, getDistortion(uv, -d2, t))) * 0.5f;
    rgb.r /= d2;
    rgb.g += -0.5 + d1;
    rgb.b = -0.5 + (d1 + d2) / 2.0;
    fragColor = rgb;
}

float4 OldTV_PS(OutPut _Value) : SV_Target0
{
    // float2 ScreenSize1 = {1280.0f, 720.0f};
    
    float2 uv = _Value.UV.xy;
    //// uv.y = 1.0 - uv.y;
    //               원래 10.0f               원래 50.0 >>> 
    uv.x += sin(uv.y * 35.0f + Time.x * 15.0f) / 60.0;
    
    //// uv.x += Time.x * 0.1f;
    float4 Color = DiffuseTex.Sample(WRAP, uv.xy);
    
    //float4 Color;
    // mainImage(Color, _Value.UV.xy);
    return Color;
}
