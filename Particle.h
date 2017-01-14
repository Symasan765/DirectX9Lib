/**
* @file Particle.h
* @brief パーティクルクラス集合
* @author 松本雄之介
* @date 2017/1/3
*/
#ifndef INC_PARTICLE_H
#define INC_PARTICLE_H

#include "BillBoard.h"

float frand(unsigned v);

/**
*	@brief　粒子一つ分のデータ
*	[例]最低限のメソッドが揃っています。
*/
class cParticle : public cBillboard{
public:
	cParticle(Texture3D*);
	cParticle() :cBillboard(nullptr){};
	void SetParticle(const D3DXVECTOR3,const D3DXVECTOR3,const int);
	void Draw(D3DXMATRIX*,bool = true);
	void SetColor(D3DCOLOR DIF);
	//virtual void Update();
	D3DXVECTOR3 moveVct;	//!<　@brief 移動方向
	int life;		//!<　@brief 生存期間
	bool flag;		//!<　@brief 生存フラグ
	D3DCOLOR diffuse;	//カラー
};

class cFlame{
public:
	cFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move, Texture3D* bTex, const int num, const float SetR, const float SetHei,const int life,const float setSize);
	~cFlame();
	void Draw(D3DXVECTOR3 Pos, D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct);
	void SetPos(D3DXVECTOR3);
	void SetMoveVect(D3DXVECTOR3);
	void Update();
private:
	cParticle* pParticle;	//!<　@brief 粒子群を格納
	Texture3D* pParticleTex;	//!<　@brief テクスチャポインタ
	D3DXVECTOR3 orginPos;		//!<　@brief 発生源
	D3DXVECTOR3 moveVector;	//!<　@brief 移動方向
	float radius;			//!<　@brief 半径
	float height;			//!<　@brief 高さ
	float size;			//!<　@brief サイズ
	int maxLife;			//!<　@brief 最大生存期間
	int createNum;		//!<　@brief フレーム間の発生数
	int particleNo;		//!<　@brief 総パーティクル数
};



#endif