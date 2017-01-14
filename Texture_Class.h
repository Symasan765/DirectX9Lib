/*=========================================================//
//		概要	:
//					作成者　松本 雄之介 (AT12A606)
//						作成日
//					  更新日
//=========================================================*/
#ifndef _INC_TEXTURE_CLASS_H_
#define _INC_TEXTURE_CLASS_H_

/*=======================#include========================*/
#include <Windows.h>
#include <d3dx9.h>

/*=========================定義==========================*/
//float X,Y座標
typedef struct _pos2d{
	float x;
	float y;
}POS2D;

//float U,V
typedef struct _uv2d{
	float u;
	float v;
}UV2D;

//頂点座標構造体
typedef struct{
	float x, y, z;			//zは使われない
	float rhw;				//2D用フラグのようなもの
	D3DCOLOR diffuse;	//カラー
	float tu, tv;			//テクスチャ位置
}VERTEX2D;

/*===================================================
//	クラス	:	図形計算系の処理を他のクラスへ提供する抽象クラス
===================================================*/
class Texture2D{
public:
	Texture2D(const char*, const short = 0, const unsigned char = 1, const unsigned char = 1);
	~Texture2D();
	void Draw() const;
	void Rotat(const float);
	void Move(const float, const float);
	void Scale(const float);
	void SetPosition(const float,const float,const float,const float);
	void SetTextureUV(short, const unsigned char, const unsigned char);
	void SetColor(D3DCOLOR);
	POS2D GetCenter() const;
	void reversal(bool);
	void TexUVScroll(const float, const float);
protected:
	VERTEX2D vx[4];				//頂点情報
	LPDIRECT3DTEXTURE9 pTex;	//テクスチャポインタ変数
	POS2D center;					//図形の中心座標
private:
	void RotatePrimitive(VERTEX2D&, const POS2D, const float);
	void ScalePrimitive(VERTEX2D&, const POS2D, const float);
	void MovePrimitive(VERTEX2D&, const float, const float);
	bool uvReversFlag;		//UVの反転(真で通常 : 偽で反転)
};

#endif