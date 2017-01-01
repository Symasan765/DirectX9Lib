/**
* @file Camera.cpp
* @brief カメラクラスの処理を記述
* @author 松本雄之介
* @date 2017/01/01
*/

#include "Camera.h"
#include "System.h"

/**
*	@brief コンストラクタ。座標、注視点、上方向を設定する
*	@param cameraPos カメラの座標
*	@param look 注視点座標
*	@param up 上方向ベクトル
*/
cCamera::cCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 look, D3DXVECTOR3 up){
	//各種初期化
	Pos = cameraPos;
	LookPt = look;
	UpVect = up;

	AngleOfView = MAXIMUM_MAGNIFICATION / 2.0f;		//画角平均値に設定
	ViewScopeMax = 2000;
	ViewScopeMin = 1;
}

/**
*	@brief デストラクタ。今のところ空関数
*/
cCamera::~cCamera(){};

/**
*	@brief プロジェクション変換を行い描画する
*	@param device D3D9デバイスポインタ
*/
void cCamera::Projection(const LPDIRECT3DDEVICE9 device){
	//座標計算
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

	//行列初期化
	D3DXMatrixIdentity(&mtxDate.mtxTrans);
	D3DXMatrixIdentity(&mtxDate.mtxRot);
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
	//注視点回転
	D3DXVec3TransformCoord(&LookPt, &LookPt, &mtxDate.mtxRot);
}

/**
*	@brief 視点中心に回転する。最後に座標を渡せばそこを起点に回転する
*	@param rotX 回転率(デグリー)
*	@param rotY 回転率(デグリー)
*	@param rotZ 回転率(デグリー)
*	@param Pt 回転の起点になる座標(なしにすれば見ている位置を中心に回る)
*/
void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ){
	//行列を回転させたあと、上ベクトルも回転させる
	cMatrix::Rotation(rotX, rotY, rotZ);

	//座標を原点に移動して計算後、元の位置に戻す
	Pos.x -= LookPt.x;
	Pos.y -= LookPt.y;
	Pos.z -= LookPt.z;
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxRot);
	Pos.x += LookPt.x;
	Pos.y += LookPt.y;
	Pos.z += LookPt.z;
}


void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ,D3DXVECTOR3 Pt){
	//行列を回転させたあと、上ベクトルも回転させる
	cMatrix::Rotation(rotX, rotY, rotZ);

	//座標を原点に移動して計算後、元の位置に戻す
	Pos.x -= Pt.x;
	Pos.y -= Pt.y;
	Pos.z -= Pt.z;
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxRot);
	Pos.x += Pt.x;
	Pos.y += Pt.y;
	Pos.z += Pt.z;
}

/**
*	@brief 注視点を返す
*	@return 注視点座標
*/
D3DXVECTOR3 cCamera::GetLookPos()const{
	return LookPt;
}