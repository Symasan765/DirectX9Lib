// -------------------------------------------------------------
// 拡散光
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// グローバル変数
// -------------------------------------------------------------

float4x4 mWVP;
float4x4 mWIT;

float4 vLightDir;							// ライトの方向
float4 vColor;
float3 vEyePos;		//カメラの位置

// 光の強さ
float4 I_a = { 0.3f, 0.3f, 0.3f, 0.0f };    // ambient
float4 I_d = { 0.7f, 0.7f, 0.7f, 0.0f };    // diffuse

// 反射率
float4 k_a = { 1.0f, 1.0f, 1.0f, 1.0f };    // ambient
float4 k_d = { 0.5f, 0.5f, 0.5f, 1.0f };    // diffuse

// -------------------------------------------------------------
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;
	float3 N			: TEXCOORD0;
	float3 Eye		: TEXCOORD1;
};
// -------------------------------------------------------------
// シーンの描画
// -------------------------------------------------------------
VS_OUTPUT VS(
	float4 Pos    : POSITION,          // ローカル位置座標
	float4 Normal : NORMAL            // 法線ベクトル
	) {
	VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ

	// 座標変換
	Out.Pos = mul(Pos, mWVP);

	// 頂点色
	float tmp = vColor.w;
	float amb = -vLightDir.w;
	float3 L = -vLightDir;
		Out.Color = vColor * max(amb, dot(Normal, -vLightDir));

	Out.N = Normal.xyz;
	Out.Eye = vEyePos - Pos.xyz;

	Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 L = -vLightDir.xyz;
	float3 H = normalize(L + normalize(In.Eye));
	float3 N = normalize(In.N);


	float4 color = In.Color + pow(max(0, dot(N, H)), 100);
	return color;
}

// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
