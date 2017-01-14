/*=========================================================//
//		概要	:	3D空間上で使用する画像クラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/10
//					  更新日
//
//=========================================================*/
#ifndef INC_IMAGE_3D_H
#define INC_IMAGE_3D_H

#include <Windows.h>
#include <d3dx9.h>
#include "MatrixCoord.h"

//頂点座標構造体
typedef struct{
	float x, y, z;
	D3DCOLOR diffuse;	//カラー
	float tu, tv;			//テクスチャ位置
}VERTEX3D;

/**
*	テクスチャの読み取りと描画を行うクラス
*	単体で使用する事は想定しておらず
*	行列クラスなどのメンバに入れて使用する(cImage3Dクラス等)
*/
class Texture3D{
public:
	Texture3D(const char*, const short = 0, const unsigned char = 1, const unsigned char = 1);
	virtual ~Texture3D();
	virtual void Draw(D3DXMATRIX*,bool = true);		//引数にfalseをわたすとセットテクスチャをスルー出来る
	void Scale(const float);
	void SetSize(const float, const float);
	void SetTextureUV(short, const unsigned char, const unsigned char);
	void SetColor(D3DCOLOR);
	void ScrollUV(const float, const float);
	void AlphaBlendStart();
	void AlphaBlendEnd();
	void SetNotColor();
	COORD GetCenter() const;
private:
	VERTEX3D vx[4];				//頂点情報
	LPDIRECT3DTEXTURE9 pTex;	//テクスチャポインタ変数
	bool colorFlag;				//カラーを入れるか？
};

/**
*	画像クラス
*	3D空間上にテクスチャを表示させる
*/
class cImage3D : public cMatrix{
public:
	cImage3D(Texture3D*);
	virtual ~cImage3D();
	/**
	*	@brief テクスチャポインタを取得する
	*	@return テクスチャポインタ
	*/
	Texture3D* GetTexture();
	/**
	*	@brief テクスチャサイズを設定する
	*	@param  sizeX-横方向,sizeY-縦方向
	*/
	void SetTexSize(const float sizeX, const float sizeY);
	virtual void Draw();
	void VectMove(const float speed);
	void AlphaBlendStart();
	void AlphaBlendEnd();
	void SetColor(D3DCOLOR);
	void SetTextureUV(short, const unsigned char, const unsigned char);
	void SetNotColor();
	void ScrollUV(const float, const float);
protected:
	Texture3D* pTex;		//!<　@brief テクスチャポインタ
};

#endif