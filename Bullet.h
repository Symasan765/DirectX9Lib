//弾だけでなく風船も記述する

#ifndef INC_BULLET_H
#define INC_BULLET_H

#include "XfileDX9.h"

class cBullet : public xFileClass{
public:
	cBullet();
	~cBullet();
private:
};

class cBalloon{
public:
	cBalloon(float,float,float);
	~cBalloon(){ delete[] pModel; pModel = nullptr; }
	void SetModel(xFileClass*,char*);		//
	void SetVec(D3DXMATRIX);
	void SetPos(float, float, float);
	bool isHit(D3DXVECTOR3, float);	//座標&半径
	void DrawB();
	void update();
	void BulletStart(D3DXMATRIX, D3DXMATRIX);
	void FlagDelete();
	D3DXVECTOR3 cBalloon::GetVect();
	float GetR(){ return balloonR; };
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vec;
	xFileClass* pModel;	//モデルデータを読み込む
	float balloonR;
	int timeCnt;
	bool flag;
};

#endif