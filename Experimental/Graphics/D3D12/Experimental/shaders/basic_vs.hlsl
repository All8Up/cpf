cbuffer CbViewProj : register(b0)
{
	matrix View;
	matrix InvView;
	matrix Projection;
	float Near;
	float Far;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color: COLOR;

	// Instance data.
	float3 translation : TRANSLATION;
	float3 scale : SCALE;
	float3x3 orientation : ORIENTATION;
};


struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float4 color: COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	float3 position = input.pos;
	float4 model = float4(mul(position * input.scale, input.orientation) + input.translation, 1.0);
	float4 world = mul(model, View);
	float4 projection = mul(world, Projection);
	output.pos = projection;
	output.color = input.color;
	return output;
}
