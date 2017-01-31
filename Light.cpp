/*=========================================================//
//		概要	:	ライト処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#include "Light.h"
#include "GameManager.h"
#include "System.h"
#include "Debug.h"
#include <d3dx9.h>


cLight::cLight(){
	time = MORNINNG;
	//R = 255, G = 255, B = 255;
	R = 184, G = 141, B = 194;
	//R = 255, G = 42, B = 0;
	//R = 25, G = 0, B = 120;
	FpsCnt = 0;
	vect = { 0, -0.8f, -0.4f };
}

cLight::~cLight(){

}

void cLight::InitLight(){
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&aLight[0], sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライト0の拡散光の設定
	aLight[0].Diffuse = D3DXCOLOR(R / 255.0f, G / 255.0f, B / 255.0f, 1.0f);		//光源の色

	aLight[0].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//反射光の色

	// ライト0の環境光の設定
	aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の方向の設定
	//vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	vecDir = vect;
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);
	vecDir *= 200.0f;
	aLight[0].Direction = vecDir;

	// ライト0をレンダリングパイプラインに設定
	GetD3DDevice->SetLight(0, &aLight[0]);

	// ライト0を使用使用状態に
	GetD3DDevice->LightEnable(0, TRUE);

	// ライティングモードをON
	GetD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/**
*	@brief ライトの色を朝 → 夜風に変更していく
*/
void cLight::DayNightUpdate(const float Second){
	GetConsole->SetPos(0, 1);
	const float frame = (Second * (float)FRAME_RATE) / 10;

	switch (time)
	{
	case MORNINNG:
		printf("朝");
		if (NoonChange(frame * 4.0f))
			time = NOON;
		break;
	case NOON:
		printf("昼");
		if (EveningChange(frame * 1.0f))
			time = EVENING;
		break;
	case EVENING:
		printf("夕");
		if (NightChange(frame * 4.0f))
			time = NIGHT;
		break;
	case NIGHT:
		printf("夜");
		if (MorningChange(frame * 1.0f))
			time = MORNINNG;
		break;
	default:
		break;
	}
}

/**
*	@brief 朝状態から昼状態への変更
*	@param 変数名 説明文
*/
bool cLight::NoonChange(const float Second){
	const float tB = NOON_B, tG = NOON_G, tR = NOON_R;
	float BlueMove = (MORNINNG_B - tB) / Second;
	float GreenMove = (MORNINNG_G - tG) / Second;
	float RedMove = (MORNINNG_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

/**
*	@brief 昼状態から夕方状態への変更
*	@param 変数名 説明文
*/
bool cLight::EveningChange(const float Second){
	const float tB = EVENING_B, tG = EVENING_G, tR = EVENING_R;
	float BlueMove = (NOON_B - tB) / Second;
	float GreenMove = (NOON_G - tG) / Second;
	float RedMove = (NOON_R - tR) / Second;

	if (B > tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B <= tB)
		return true;
	return false;
}

/**
*	@brief 夕方状態から夜状態への変更
*	@param 変数名 説明文
*/
bool cLight::NightChange(const float Second){
	const float tB = NIGHT_B, tG = NIGHT_G, tR = NIGHT_R;
	float BlueMove = (EVENING_B - tB) / Second;
	float GreenMove = (EVENING_G - tG) / Second;
	float RedMove = (EVENING_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

/**
*	@brief 夜状態から朝状態への変更
*	@param 変数名 説明文
*/
bool cLight::MorningChange(const float Second){
	const float tB = MORNINNG_B, tG = MORNINNG_G, tR = MORNINNG_R;
	float BlueMove = (NIGHT_B - tB) / Second;
	float GreenMove = (NIGHT_G - tG) / Second;
	float RedMove = (NIGHT_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

D3DCOLOR cLight::GetLightColor(){
	return D3DCOLOR_XRGB((int)R, (int)G, (int)B);
}