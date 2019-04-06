#define MAX_LIGHTS 16

Texture2D diffuseMap  : register( t0 );
Texture2D normalMap   : register( t1 );
Texture2D specularMap : register( t2 );

Texture2D noiseMap  : register( t3 );
texture2D lavaMap	: register( t4 );
SamplerState filter	: register( s0 );

struct TPointLight
{
	float4 vLightDesc;
	float4 vColor;
};

cbuffer LightsBuffer : register( b0 )
{
	float3	vBufferData;
	float	fDissolve;
	float3	vCameraPos;
	TPointLight	tLights[MAX_LIGHTS];
}

cbuffer TextureBuffer : register ( b1 )
{
	float2 vScreenResolution;
	bool bHasTexture;
	bool bHasNormalMap;
	bool BHasSpecular;
	float3 vPadding;
}

struct INPUT
{
	float4 vPosition : SV_POSITION;
	float3 vWorldPos : WPOSITION;
	float3 vNormal : NORMAL;
	float2 vUV : TEXTURECOORD;
	float2 vNDC : NDCPOS;
};

float4 CalculatePointLight(float3 vSurfacePos, float3 vSurfaceNormal, int nIndex)
{
	float3 vPixelToLight = tLights[nIndex].vLightDesc.xyz - vSurfacePos;

	float fDistanceToLight = length(vPixelToLight);

	float fAngularAttenuation = saturate(dot(vPixelToLight / fDistanceToLight, vSurfaceNormal));

	float fRangeAttenuation = 1 - saturate(fDistanceToLight / tLights[nIndex].vLightDesc.w);

	return fAngularAttenuation * tLights[nIndex].vColor * fRangeAttenuation * fRangeAttenuation;
}

float4 main(INPUT input) : SV_TARGET
{
	float4 vBaseColor;

	if(bHasTexture)
		vBaseColor = diffuseMap.Sample(filter, input.vUV);
	

	float4 vLightsColor = float4( 0, 0, 0, 1 );

	float fSpecularFactor = 0;
	float3 vCamToObj = normalize(input.vWorldPos - vCameraPos);

	for(int i = 0; i < vBufferData.x; i++)
	{
		vLightsColor += CalculatePointLight(input.vWorldPos, input.vNormal, i);

		float3 vLightToObj = normalize(input.vWorldPos - tLights[i].vLightDesc.xyz);
		float3 vReflection = reflect(vLightToObj, input.vNormal);

		if(BHasSpecular)
			fSpecularFactor += pow(saturate(dot(vCamToObj, vReflection)), 200);
	}

	if(BHasSpecular)
		float4 vSpecularValue = specularMap.Sample(filter, input.vUV) * fSpecularFactor;

	if(fDissolve)
	{
		float fMaskingValue = 0.5113f;
		float fOutlineValue = 0.0301f;

		if(length(input.vNDC) < 4.0f)
		{
			float4 vNoiseValue = noiseMap.Sample(filter, input.vUV);

			if(vNoiseValue.x > fMaskingValue)
			{
				return ( vBaseColor * saturate(vLightsColor) ) + vBaseColor * vBufferData.y;

			}
			else if(vNoiseValue.x > fMaskingValue - fOutlineValue)
			{
				return lavaMap.Sample(filter, vNoiseValue.xy);
			}
			else
			{
				discard;
			}
		}
	}

	return ( vBaseColor * saturate(vLightsColor) ) + vBaseColor * vBufferData.y;
}