Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_input
{
    float4 inputPosition : SV_Position;
    float2 inputTexCoord : TEXCOORD;
};

float4 main(PS_input input) : SV_Target
{
    float4 color = myTexture.Sample(mySampler, input.inputTexCoord);
    return color;
}