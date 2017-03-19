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
	float4 L = -vLightDir; // ローカル座標系でのライトベクトル
		float amb = L.w;

	float tmp = vColor.w;
		Out.Color = vColor * max(amb, dot(Normal, L));
		Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	return In.Color;
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
