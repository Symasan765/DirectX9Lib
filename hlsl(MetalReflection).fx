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

// -------------------------------------------------------------
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;
	float3 N			: TEXCOORD0;
	float3 X		: TEXCOORD1;
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

	// 拡散光＋環境光
	float tmp = vColor.w;
	float amb = -vLightDir.w;	// 環境光の強さ
	float3 L = -vLightDir; // ローカル座標系でのライトベクトル
		Out.Color = vColor * max(amb, dot(Normal, -vLightDir));

	// 鏡面反射用のベクトル
	Out.N = Normal.xyz;
	Out.X = Pos.xyz;

	Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 L = -vLightDir.xyz;				// ライトベクトル
	float3 N = normalize(In.N);				// 法線ベクトル
	float3 V = normalize(vEyePos - In.X);	// 視線ベクトル
	float3 H = normalize(L + V);			// ハーフベクトル

	// 計算に使うそれぞれの角度
	float NV = dot(N, V);
	float NH = dot(N, H);
	float VH = dot(V, H);
	float NL = dot(N, L);
	float LH = dot(L, H);

	// Beckmann 分布関数
	const float m = 0.3f;// 荒さ
	float NH2 = NH*NH;
	float D = exp(-(1 - NH2) / (NH2*m*m)) / (4 * m*m*NH2*NH2);

	// 幾何減衰率
	float G = min(1, min(2 * NH*NV / VH, 2 * NH*NL / VH));

	// フレネル
	float n = 6.5f;//						 反射する光の量的な感じ
	float g = sqrt(n*n + LH*LH - 1);
	float gpc = g + LH;
	float gnc = g - LH;
	float cgpc = LH*gpc - 1;
	float cgnc = LH*gnc + 1;
	float F = 0.5f*gnc*gnc*(1 + cgpc*cgpc / (cgnc*cgnc)) / (gpc*gpc);	//この先頭の定数で反射の大きさ変わる

	// 金属の色
	float4 ks = { 2.0f*0.45f, 2.0f*0.45f, 2.0f*0.45f, 1.0f };		//ここで色変わる

		return In.Color						// 拡散光＋環境光
		+ ks * max(0, F*D*G / NV);	// 鏡面反射光
}

// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}