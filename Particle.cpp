#include "Particle.h"

/**
*	@brief 粒子の初期化をする
*	@param tex テクスチャポインタ
*/
cParticle::cParticle(Texture3D* tex) : cBillboard(tex){
	moveVct = { 0, 0, 0 };
	life = 0;
	flag = false;
}

/**
*	@brief パーティクルの各設定を行う
*	@param pos 粒子初期位置
*	@param vct 移動方向
*	@param setLife 生存期間(フレーム)
*/
void cParticle::SetParticle(const D3DXVECTOR3 pos, const D3DXVECTOR3 vct, const int setLife){
	SetTrans(pos);	//座標セット
	SetScaling(1.0f);
	moveVct = vct;	//移動方向
	life = setLife;	//生存期間
	flag = true;		//生存してるぞ！
}

/**
*	@brief 描画を行う関数
*	@param InvMtx カメラ逆行列
*/
void cParticle::Draw(D3DXMATRIX* InvMtx,bool SetFlag){
	mtxDate.mtxWorld = *InvMtx * mtxDate.mtxScale * mtxDate.mtxRot * mtxDate.mtxTrans;	//位置
	pTex->SetColor(diffuse);
	pTex->Draw(&mtxDate.mtxWorld,SetFlag);
}

void cParticle::SetColor(D3DCOLOR DIF){
	diffuse = DIF;
}

/**
*	@brief パーティクル更新処理
*	@param 変数名 説明文
*/
//void cParticle::Update(){
//	if (life > 0){
//		--life;
//		Translation(moveVct);	//移動
//	}
//	else{
//		flag = false;
//	}
//}