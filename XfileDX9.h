/*=========================================================//
//		概要	:	Xファイルを扱うクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#ifndef INC_X_FILE_H
#define INC_X_FILE_H

#include <d3dx9.h>

class xFileClass{
public:
	xFileClass();
	~xFileClass();
	HRESULT LoadFile(const char*);
	void Draw(D3DXMATRIX*);
private:
	LPD3DXMESH pd3dxMesh;				// メッシュデータへのポインタを保持
	LPD3DXBUFFER pd3dxBuffer;			// マテリアルデータへのポイントを保持
	LPDIRECT3DTEXTURE9* pTex;
	int numMatModel;						// マテリアルの数を保持
};

#endif