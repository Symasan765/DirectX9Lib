/*=========================================================//
//		概要	:	ライト処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#include "Light.h"
#include "GameManager.h"


cLight::cLight(){

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
	aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//光源の色

	aLight[0].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//反射光の色

	// ライト0の環境光の設定
	aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
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