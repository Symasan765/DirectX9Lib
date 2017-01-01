/*=========================================================//
//		概要	:	行列計算を扱うクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#include "MatrixCoord.h"

cMatrix::cMatrix(){
	//各行列を単位行列に変換
	D3DXMatrixIdentity(&mtxDate.mtxRot);
	D3DXMatrixIdentity(&mtxDate.mtxScale);
	D3DXMatrixIdentity(&mtxDate.mtxTrans);
	D3DXMatrixIdentity(&mtxDate.mtxWorld);
}

void cMatrix::MatrixCalculation(){
	mtxDate.mtxWorld = mtxDate.mtxScale * mtxDate.mtxRot * mtxDate.mtxTrans;
}

void cMatrix::Scaling(const float rate){
	D3DXMatrixScaling(&mtxDate.mtxScale,rate, rate, rate);
}

void cMatrix::Translation(const D3DXVECTOR3 pos){
	D3DXMATRIX mtxBuf;
	D3DXMatrixTranslation(&mtxBuf, pos.x, pos.y, pos.z);
	mtxDate.mtxTrans *= mtxBuf;
}

void cMatrix::Rotation(const float bX, const float bY, const float bZ){
	//回転数を確認してそれぞれの関数へ
	if (bX != 0.0f)
		OwnAxisRotateX(bX);
	if (bY != 0.0f)
		OwnAxisRotateY(bY);
	if (bZ != 0.0f)
		OwnAxisRotateZ(bZ);
}

void cMatrix::SetScaling(const float rate){
	D3DXMatrixScaling(&mtxDate.mtxScale, rate, rate, rate);
}

void cMatrix::SetRotate(const float bX, const float bY, const float bZ){
	D3DXVECTOR3 rot(D3DXToRadian(bX), D3DXToRadian(bY), D3DXToRadian(bZ));
	D3DXMATRIX mtxBuf;
	D3DXMatrixRotationYawPitchRoll(&mtxBuf, rot.y, rot.x, rot.z);
	mtxDate.mtxRot = mtxBuf;
}

void cMatrix::OwnAxisRotateX(const float dgr){
	//ベクトルを作成する
	D3DXVECTOR3 vect(1.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxBuf;

	D3DXVec3TransformCoord(&vect, &vect, &mtxDate.mtxRot);	//ベクトルを回転

	D3DXMatrixRotationAxis(&mtxBuf, &vect, D3DXToRadian(dgr));		//好きな回転軸を決められる
	mtxDate.mtxRot *= mtxBuf;
}

void cMatrix::OwnAxisRotateY(const float dgr){
	//ベクトルを作成する
	D3DXVECTOR3 vect(0.0f, 1.0f, 0.0f);
	D3DXMATRIX mtxBuf;

	D3DXVec3TransformCoord(&vect, &vect, &mtxDate.mtxRot);	//ベクトルを回転

	D3DXMatrixRotationAxis(&mtxBuf, &vect, D3DXToRadian(dgr));		//好きな回転軸を決められる
	mtxDate.mtxRot *= mtxBuf;
}

void cMatrix::OwnAxisRotateZ(const float dgr){
	//ベクトルを作成する
	D3DXVECTOR3 vect(0.0f, 0.0f, 1.0f);
	D3DXMATRIX mtxBuf;

	D3DXVec3TransformCoord(&vect, &vect, &mtxDate.mtxRot);	//ベクトルを回転

	D3DXMatrixRotationAxis(&mtxBuf, &vect, D3DXToRadian(dgr));		//好きな回転軸を決められる
	mtxDate.mtxRot *= mtxBuf;
}

void cMatrix::VectMove(const float speed){
	D3DXVECTOR3 vect(0.0f, 0.0f, 1.0f * speed);		//スピード基準
	D3DXVec3TransformCoord(&vect, &vect, &mtxDate.mtxRot);

	Translation(vect);
}

D3DXMATRIX* cMatrix::GetWorldMatrix(){
	//行列計算の後、返却
	MatrixCalculation();
	return &mtxDate.mtxWorld;
}

D3DXMATRIX* cMatrix::GetScaleMatrix(){
	return &mtxDate.mtxScale;
}

D3DXMATRIX* cMatrix::GetRotatMatrix(){
	return &mtxDate.mtxRot;
}

D3DXMATRIX* cMatrix::GetTransMatrix(){
	return &mtxDate.mtxTrans;
}

void cMatrix::SetTrans(const D3DXVECTOR3 pos){
	D3DXMATRIX mtxBuf;
	D3DXMatrixTranslation(&mtxBuf, pos.x, pos.y, pos.z);
	mtxDate.mtxTrans = mtxBuf;
}