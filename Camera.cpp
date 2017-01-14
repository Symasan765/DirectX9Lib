/**
* @file Camera.cpp
* @brief カメラクラスの処理を記述
* @author 松本雄之介
* @date 2017/01/01
*/

#include "Camera.h"
#include "System.h"
#include <math.h>

/**
* @def PI
* @brief 円周率
*/
#define PI (3.14159)

/**
*	@brief コンストラクタ。座標、注視点、上方向を設定する
*	@param cameraPos カメラの座標
*	@param look 注視点座標
*	@param up 上方向ベクトル
*/
cCamera::cCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 look, D3DXVECTOR3 up){
	//各種初期化
	Translation(cameraPos);
	LookPt = look;
	UpVect = up;

	AngleOfView = MAXIMUM_MAGNIFICATION / 2.0f;		//画角平均値に設定
	ViewScopeMax = 10000;
	ViewScopeMin = 5;
}

/**
*	@brief プロジェクション変換を行い描画する
*	@param device D3D9デバイスポインタ
*/
void cCamera::Projection(const LPDIRECT3DDEVICE9 device){
	//座標計算
	D3DXVECTOR3 Pos(0.0f,0.0f,0.0f);
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxTrans);		//座標位置を算出

	D3DXMatrixIdentity(&mtxDate.mtxWorld);
	D3DXMatrixLookAtLH(&mtxDate.mtxWorld, &Pos, &LookPt, &UpVect);
	device->SetTransform(D3DTS_VIEW, &mtxDate.mtxWorld);

	D3DXMATRIX mxPrj;

	//カメラの構図変換
	D3DXMatrixPerspectiveFovLH(&mxPrj, D3DXToRadian(AngleOfView), (float)WINDOW_SCREEN_X / (float)WINDOW_SCREEN_Y, ViewScopeMin, ViewScopeMax);
	device->SetTransform(D3DTS_PROJECTION, &mxPrj);


	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //=================================================
	device->SetRenderState(D3DRS_LIGHTING, false);		//明かり===============================
}

/**
*	@brief 行列クラスをオーバーライド。ズーム処理に相当
*	@param rate 拡大率
*/
void cCamera::Scaling(const float rate){
	AngleOfView -= (rate / 10);
	if (AngleOfView > MAXIMUM_MAGNIFICATION)
		AngleOfView = MAXIMUM_MAGNIFICATION;
	if (AngleOfView < MINIMUM_MAGNIFICATION)
		AngleOfView = MINIMUM_MAGNIFICATION;
}

/**
*	@brief 注視点を設定する関数
*	@param look 注視点座標
*/
void cCamera::SetLookPos(D3DXVECTOR3 look){
	LookPt = look;
}

/**
*	@brief 回転処理。上ベクトルの回転も含む。FPS視点向き
*	@param rotX X方向回転率(デグリー)
*	@param rotY Y方向回転率(デグリー)
*	@param rotZ Z方向回転率(デグリー)
*/
void cCamera::Rotation(const float rotX, const float rotY, const float rotZ){
	//行列を回転させたあと、上ベクトルも回転させる
	cMatrix::Rotation(rotX, rotY, rotZ);
	//上方向回転
	D3DXVec3TransformCoord(&UpVect, &UpVect, &mtxDate.mtxRot);
	//注視点回転。注視点を原点に移動させたあとで元の位置に戻す
	//LookPt -= Pos;
	D3DXVec3TransformCoord(&LookPt, &LookPt, &mtxDate.mtxRot);
	//LookPt += Pos;
}

/**
*	@brief 視点中心に回転する。最後に座標を渡せばそこを起点に回転する(TPS向け)
*	@param rotX 回転率(デグリー)
*	@param rotY 回転率(デグリー)
*	@param rotZ 回転率(デグリー)
*	@param Pt 回転の起点になる座標(なしにすれば見ている位置を中心に回る)
*/
void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ){
	
	cMatrix::Rotation(rotX, rotY, rotZ);	//回転
	UpVect = { 0, 1, 0 };
	D3DXVec3TransformCoord(&UpVect, &UpVect, &mtxDate.mtxRot);
	//それぞれに応じて任意回転
	if (rotX)
		RotationAxisX(LookPt, rotX);
	if (rotY)
		RotationAxisY(LookPt, rotY);
	if (rotZ)
		RotationAxisZ(LookPt, rotZ);
}


void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ, D3DXVECTOR3 Pt){
	cMatrix::Rotation(rotX, rotY, rotZ);	//回転

	//それぞれに応じて任意回転
	if (rotX)
		RotationAxisX(Pt, rotX);
	if (rotY)
		RotationAxisY(Pt, rotY);
	if (rotZ)
		RotationAxisZ(Pt, rotZ);
}

/**
*	@brief 注視点を返す
*	@return 注視点座標
*/
D3DXVECTOR3 cCamera::GetLookPos()const{
	return LookPt;
}

/**
*	@brief 上方向を返す
*	@return 注視点座標
*/
D3DXVECTOR3 cCamera::GetUpVect()const{
	return UpVect;
}

/**
*	@brief カメラ座標を返す
*	@return カメラ座標
*/
D3DXVECTOR3 cCamera::GetCameraPos()const{
	D3DXVECTOR3 Pos(0,0,0);
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxTrans);
	return Pos;
}

/**
*	@brief 任意軸回転移動
*	@param tag 回転中心
*	@param dgr 回転角
*/
void cCamera::RotationAxisX(const D3DXVECTOR3& tag, const float dgr){
	//任意軸作成
	D3DXVECTOR3 rot(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//注視点を原点にカメラを移動
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}

/**
*	@brief 任意軸回転移動
*	@param tag 回転中心
*	@param dgr 回転角
*/
void cCamera::RotationAxisY(const D3DXVECTOR3& tag, const float dgr){
	//任意軸作成
	D3DXVECTOR3 rot(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//注視点を原点にカメラを移動
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}

/**
*	@brief 任意軸回転移動
*	@param tag 回転中心
*	@param dgr 回転角
*/
void cCamera::RotationAxisZ(const D3DXVECTOR3& tag, const float dgr){
	//任意軸作成
	D3DXVECTOR3 rot(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//注視点を原点にカメラを移動
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}


D3DXMATRIX* cCamera::GetWorldMatrix(){
	return &mtxDate.mtxWorld;
}