///*=========================================================//
////		概要	:	カメラクラスの処理を記述する
////					作成者　松本 雄之介 (AT12A606)
////						作成日　2016/10/20
////					  更新日
////=========================================================*/
//#include "CameraClass.h"
//#include "System.h"
//#include <crtdbg.h>
//#include <math.h>
//
//
//#define PI (3.14159)
//
//cCameraP::cCameraP() : cP(0,0,0){
//	ellor = false;		//初期化フラグ
//}
//
//cCameraP::~cCameraP(){
//}
//
//void cCameraP::Set(const float bX, const float bY, const float bZ){
//	ellor = true;	//エラー解除
//
//	D3DXVECTOR3 buf(bX, bY, bZ);
//	cP = buf;
//}
//
//void cCameraP::Move(const float bX, const float bY, const float bZ){
//	_ASSERT_EXPR(ellor, "カメラ座標が初期化されないままMOVE()が呼ばれました");
//
//	D3DXVECTOR3 buf(bX, bY, bZ);
//	cP += buf;
//}
//
//cCameraR::cCameraR() : cR(0,0,0){
//	ellor = false;		//初期化フラグ
//}
//
//cCameraR::~cCameraR(){
//
//}
//
//void cCameraR::Set(const float bX, const float bY, const float bZ){
//	ellor = true;	//エラー解除
//
//	D3DXVECTOR3 buf(bX, bY, bZ);
//	cR = buf;
//}
//
//void cCameraR::Move(const float bX, const float bY, const float bZ){
//	_ASSERT_EXPR(ellor, "カメラ視認座標が初期化されないままMOVE()が呼ばれました");
//
//	D3DXVECTOR3 buf(bX, bY, bZ);
//	cR += buf;
//}
//
//cCameraU::cCameraU() : cU(0,0,0){
//	ellor = false;
//}
//
//cCameraU::~cCameraU(){
//
//}
//
//void cCameraU::Set(const float bX, const float bY, const float bZ){
//	ellor = true;	//エラー解除
//
//	D3DXVECTOR3 buf(bX, bY, bZ);
//	cU = buf;
//}
//
//cCamera::cCamera(){
//	machine.AngleOfView = MAXIMUM_MAGNIFICATION / 2.0f;
//	machine.ViewScopeMax = 20000;
//	machine.ViewScopeMin = 1;
//	ellor = false;	//エラー判定
//	MtxInit(&mtxCamera.mtxRot);
//	MtxInit(&mtxCamera.mtxScale);
//	MtxInit(&mtxCamera.mtxTrans);
//	MtxInit(&mtxCamera.mtxWorld);
//}
//
//cCamera::~cCamera(){
//
//}
//
//void cCamera::SetCamera(COORD3D bP, COORD3D bR, COORD3D bU){
//	ellor = true;
//	machine.cameraP.Set(bP.x,bP.y,bP.z);
//	machine.cameraR.Set(bR.x, bR.y, bR.z);
//	machine.cameraU.Set(bU.x, bU.y, bU.z);
//}
//
//void cCamera::Projection(const LPDIRECT3DDEVICE9 pD3dDevice){
//	_ASSERT_EXPR(ellor, "カメラが初期化されないまま描画が呼ばれました");
//
//	D3DXVECTOR3 cU;
//	D3DXVec3TransformCoord(&cU, &machine.cameraU.cU, &mtxCamera.mtxRot);
//
//	WorldMatrixCalcu();	//行列を作成する
//	D3DXVec3TransformCoord(&machine.cameraP.cP, &machine.cameraP.cP, &mtxCamera.mtxWorld);	//元座標自体を変更してる
//	
//	D3DXMATRIX mxView;
//	D3DXMatrixLookAtLH(&mxView, &machine.cameraP.cP, &machine.cameraR.cR, &cU);
//	pD3dDevice->SetTransform(D3DTS_VIEW, &mxView);
//
//	D3DXMATRIX mxPrj;
//
//	//カメラの構図変換
//	D3DXMatrixPerspectiveFovLH(&mxPrj, D3DXToRadian(machine.AngleOfView), (float)WINDOW_SCREEN_X / (float)WINDOW_SCREEN_Y, machine.ViewScopeMin, machine.ViewScopeMax);
//	pD3dDevice->SetTransform(D3DTS_PROJECTION, &mxPrj);
//
//
//	pD3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//
//	pD3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //=================================================
//	pD3dDevice->SetRenderState(D3DRS_LIGHTING, false);		//明かり===============================
//}
//
//void cCamera::scaling(const float rate){
//	//translation(0.0f, rate * -4.0f, rate * 3.0f);
//	machine.AngleOfView -= (rate / 10);
//	if (machine.AngleOfView > MAXIMUM_MAGNIFICATION)
//		machine.AngleOfView = MAXIMUM_MAGNIFICATION;
//	if (machine.AngleOfView < MINIMUM_MAGNIFICATION)
//		machine.AngleOfView = MINIMUM_MAGNIFICATION;
//}
//
//void cCamera::translation(const float bX, const float bY, const float bZ){
//	D3DXVECTOR3 pos(bX, bY, bZ);
//	D3DXMatrixTranslation(&mtxCamera.mtxTrans, pos.x, pos.y, pos.z);
//}
//
//void cCamera::rotation(const float bX, const float bY, const float bZ){
//	D3DXVECTOR3 rot(D3DXToRadian(bX), D3DXToRadian(bY), D3DXToRadian(bZ));
//	D3DXMATRIX tmp(rot);
//	D3DXMatrixRotationYawPitchRoll(&tmp, rot.y, rot.x, rot.z);
//	mtxCamera.mtxRot = tmp;
//}
//
//void cCamera::rotation(D3DXMATRIX wMtx){
//	D3DXVec3TransformCoord(&machine.cameraP.cP, &machine.cameraP.cP, &wMtx);	//元座標自体を変更してる
//}
//
//void cCamera::PovUpVectorRotat(D3DXMATRIX rotMtx){
//	D3DXVec3TransformCoord(&machine.cameraU.cU, &machine.cameraU.cU, &rotMtx);	//元座標自体を変更してる
//}
//
//void cCamera::WorldMatrixCalcu(){
//	D3DXMatrixIdentity(&mtxCamera.mtxWorld);
//	mtxCamera.mtxWorld = mtxCamera.mtxScale * mtxCamera.mtxRot * mtxCamera.mtxTrans;
//
//	MtxInit(&mtxCamera.mtxRot);
//	MtxInit(&mtxCamera.mtxScale);
//	MtxInit(&mtxCamera.mtxTrans);
//}
//
//void cCamera::MtxInit(D3DXMATRIX* buf){
//	D3DXMatrixIdentity(buf);
//}
//
//void cCamera::PovBaseXRotation(const float bX){
//	//カメラ位置の角度を求め直角位置を求める
//	float dgr = (double)atan2(machine.cameraP.cP.z, machine.cameraP.cP.x) * 180 / PI;
//	dgr += 90;
//
//
//	//原点を中心にX方向へ向けたベクトルを作りそれを回転させる
//	const float len = 10.0f;
//	const float bufX = len;
//	const float bufZ = 0.0f;
//
//	float pX = bufX * cosf(D3DXToRadian(dgr)) - sinf(D3DXToRadian(dgr));
//	float pZ = bufX * sinf(D3DXToRadian(dgr)) + cosf(D3DXToRadian(dgr));
//
//	D3DXVECTOR3 pos(pX, machine.cameraR.cR.y, pZ);		//原点からの軸位置
//	D3DXMatrixRotationAxis(&mtxCamera.mtxRot, &pos, D3DXToRadian(bX));
//}
//
//void cCamera::SetLookPos(D3DXMATRIX wMtx){
//	D3DXVec3TransformCoord(&machine.cameraR.cR, &machine.cameraR.cR, &wMtx);
//}
//
//void cCamera::SetLookPos(const float bX, const float bY, const float bZ){
//	machine.cameraR.Set(bX, bY, bZ);
//}
//
//D3DXVECTOR3 cCamera::GetLookVector()const{
//	return machine.cameraR.cR;
//}
//
//D3DXVECTOR3 cCamera::GetpUpVector()const{
//	return machine.cameraU.cU;
//}
//
//D3DXMATRIX* cCamera::GetWorldMtx(){
//	return &mtxCamera.mtxWorld;
//}