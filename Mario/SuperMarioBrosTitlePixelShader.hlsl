Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_input
{
    float4 inputPosition : SV_Position;
    float2 inputTexCoord : COLOR;
};

float4 main(PS_input input) : SV_Target
{
    float4 color = myTexture.Sample(mySampler, input.inputTexCoord);
    
    if (color.r >= 0.7f && color.g >= 0.7f && color.b >= 0.7f)
    {
        clip(-1.0f);
    }
    
    return color;
}