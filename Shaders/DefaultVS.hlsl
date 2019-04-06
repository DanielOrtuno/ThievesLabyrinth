#pragma pack_matrix(row_major)

cbuffer Model : register ( b0 )
{
	float4x4 modeling;
};

cbuffer Camera: register( b1 )
{
	float4x4 view;
	float4x4 projection;
}

struct VERTEX
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float2 vUV : TEXTURECOORD;
};

struct OUTPUT
{
	float4 vPosition : SV_POSITION;
	float3 vWorldPos : WPOSITION;
	float3 vNormal : NORMAL;
	float2 vUV : TEXTURECOORD;
	float2 vNDC : NDCPOS;
};


OUTPUT main(VERTEX input)
{
	OUTPUT output = (OUTPUT)0;
	input.vPosition.w = 1;

	output.vPosition = mul(input.vPosition, modeling);
	output.vWorldPos = output.vPosition.xyz;

	output.vPosition = mul(output.vPosition, view);
	output.vNDC.x = output.vPosition.x / output.vPosition.w;
	output.vNDC.y = output.vPosition.y / output.vPosition.w;

	output.vPosition = mul(output.vPosition, projection);

	output.vNormal = normalize(mul(input.vNormal, modeling)).xyz;

	output.vUV = input.vUV;

	return output;
}