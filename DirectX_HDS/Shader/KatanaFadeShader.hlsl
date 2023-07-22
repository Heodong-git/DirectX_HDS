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


float DiamondMask(float2 p, float zoom)
{
    p.x += sin(p.y + Time.x) * 0.2f;
    float2 q = abs((float2) zoom) - (float2) zoom * p;
    return max(-q.x, q.y) - 0.25f * zoom;
}


void mainImage(out float4 fragColor, in float4 fragCoord, in float2 iResolution, in float iTime)
{
    // Normalized pixel coordinates (from 0 to 1)
    float2 uv = fragCoord.xy / iResolution.xy;
    uv = fragCoord.xy / iResolution.y;

    // Time varying pixel color
    float3 col = 0.5 + 0.5 * cos(iTime + float3(uv.x, uv.y, uv.x + 2.0f));

    float2 uv2 = frac(20.0f * uv);
    float t = frac(0.8 * iTime);
    float zoom = lerp(2.0, -2.0, t) + lerp(1.0f, -1.0f, uv.x);
    
    if (DiamondMask(uv2, zoom) < 0.5f)
    {
        col *= 0.0f;
    }

    // Output to screen
    fragColor = float4(col, 1.0f);
}



float4 OldTV_PS(OutPut _Value) : SV_Target0
{
    // float2 ScreenSize1 = {1280.0f, 720.0f};
    
    float4 uv = _Value.UV;
    //// uv.y = 1.0 - uv.y;
    //               원래 10.0f               원래 50.0 >>> 
    uv.x += sin(uv.y * 35.0f + Time.x * 15.0f) / 60.0;
    
    //// uv.x += Time.x * 0.1f;
    float4 Color = DiffuseTex.Sample(WRAP, uv.xy);
    
    //float4 Color;
    //mainImage(Color, _Value.UV.xy);
    return Color;
}
