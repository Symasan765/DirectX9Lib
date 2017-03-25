/*=========================================================//
//		概要	:	Xファイルを扱うクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#ifndef INC_X_FILE_H
#define INC_X_FILE_H

#include <Windows.h>
#include <d3dx9.h>
#include "MatrixCoord.h"

class xFileClass{
public:
	xFileClass();
	virtual ~xFileClass();
	HRESULT LoadFile(const char*);
	virtual void Draw(D3DXMATRIX*);
protected:
	LPD3DXMESH pd3dxMesh;				// メッシュデータへのポインタを保持
	LPD3DXBUFFER pd3dxBuffer;			// マテリアルデータへのポイントを保持
	LPDIRECT3DTEXTURE9* pTex;
	D3DXMATERIAL* pD3DXMat;
	int numMatModel;						// マテリアルの数を保持
};

class cModel3D : public xFileClass, public cMatrix{
public:
	cModel3D() = default;
	virtual ~cModel3D() = default;
};

class cMetalReflection : public xFileClass{
public:
	cMetalReflection();
	~cMetalReflection();
	void Draw(D3DXMATRIX*, D3DXMATRIX*, D3DXMATRIX*);
private:
	LPD3DXEFFECT              m_pEffect;        // エフェクト
	D3DXHANDLE                m_hTechnique;    // テクニック
	D3DXHANDLE                m_hmWVP;        // ローカル-射影変換行列
	D3DXHANDLE                m_hmWIT;        // ローカル-ワールド変換行列
	D3DXHANDLE                m_hvLightDir;    // ライトの方向
	D3DXHANDLE                m_hvCol;        // 頂点色
	D3DXHANDLE                m_hvEyePos;        // カメラ位置
};

#endif