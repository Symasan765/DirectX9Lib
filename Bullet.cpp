#include "Bullet.h"
#include <Windows.h>
#include <d3dx9.h>

cBalloon::cBalloon(float bX, float bY, float bZ){
	pModel = nullptr; 
	pos.x = bX;
	pos.y = bY;
	pos.z = bZ;
	balloonR = 1000.0f;
	flag = false;
	timeCnt = 10000;
}

void cBalloon::SetModel(xFileClass* pBuf,char* fileName){
	if (pModel != pBuf){
		delete pModel;
		pModel = nullptr;
	}

	pModel = pBuf;
	pModel->LoadFile(fileName);
	pModel->WorldScaling(50.0f);
}

bool cBalloon::isHit(D3DXVECTOR3 target, float R){
	//(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2

	float bX, bY, bZ,add,calc;
	bX = (target.x - pos.x) * (target.x - pos.x);
	bY = (target.y - pos.y) * (target.y - pos.y);
	bZ = (target.z - pos.z) * (target.z - pos.z);

	add = bX + bY + bZ;
	calc = (balloonR + R) * (balloonR + R);

	//当たっているか？
	if (add <= calc)
		return true;
	else
		return false;
}

void cBalloon::DrawB(){
	if (flag == true){
		pModel->WorldScaling(10.0f);
		pModel->SetPos(pos.x, pos.y, pos.z);
		pModel->Draw();
	}
	else if (timeCnt == 10000){
		pModel->WorldScaling(50.0f);
		pModel->SetPos(pos.x, pos.y, pos.z);
		pModel->Draw();
	}
}

void cBalloon::update(){
	if (flag){
		pos += vec;
		timeCnt--;
		if (timeCnt <= 0){
			flag = false;
			timeCnt = 180;
		}
	}
}

void WorldTranslation(const float bX, const float bY, const float bZ,D3DXMATRIX* mtxTrans){
	D3DXVECTOR3 pos(bX, bY, bZ);
	D3DXMATRIX mtxBuf;
	D3DXMatrixTranslation(&mtxBuf, pos.x, pos.y, pos.z);
	*mtxTrans *= mtxBuf;
}

void cBalloon::SetVec(D3DXMATRIX bVect){
	timeCnt = 180.0f;
	D3DXVECTOR3 vect(0.0f, 0.0f, 20.0f);					//スピードを方向の基準を作成
	D3DXVec3TransformCoord(&vect, &vect, &bVect);	//移動方向を回転

	vec.x = vect.x;
	vec.y = vect.y;
	vec.z = vect.z;
}

void cBalloon::BulletStart(D3DXMATRIX bVect, D3DXMATRIX rVect){
	if (flag == false){
		SetPos(bVect._41, bVect._42, bVect._43);
		balloonR = 100.0f;
		timeCnt = 180;
		flag = true;
		SetVec(rVect);
	}
}

void cBalloon::SetPos(float bX, float bY, float bZ){
	pos.x = bX;
	pos.y = bY;
	pos.z = bZ;
}

void cBalloon::FlagDelete(){
	flag = false;
	timeCnt = 180;
}

D3DXVECTOR3 cBalloon::GetVect(){
	return vec;
}