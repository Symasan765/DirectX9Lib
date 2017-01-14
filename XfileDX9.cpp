/*=========================================================//
//		概要	:	Xファイルを扱うクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#include "XfileDX9.h"
#include "GameManager.h"


xFileClass::xFileClass(){
	pd3dxMesh = nullptr;		// メッシュデータへのポインタを保持
	pd3dxBuffer = nullptr;	// マテリアルデータへのポイントを保持
	pTex = nullptr;
	numMatModel = NULL;		// マテリアルの数を保持
}

xFileClass::~xFileClass(){
	if (pd3dxMesh){
		pd3dxMesh->Release();
		pd3dxMesh = NULL;
	}

	if (pd3dxBuffer){
		pd3dxBuffer->Release();
		pd3dxBuffer = NULL;
	}

	LPDIRECT3DTEXTURE9* tmp = pTex;
	for (int i = 0; i < numMatModel; ++i){
		if (tmp[i] != nullptr){
			tmp[i]->Release();
			tmp[i] = nullptr;
		}
	}
	delete[] tmp;
}

HRESULT xFileClass::LoadFile(const char* pFileName){
	DWORD numMaterials;
	HRESULT result;


	result = D3DXLoadMeshFromX(pFileName,	// (1)
		D3DXMESH_MANAGED,
		GetD3DDevice,					// (2)
		NULL,
		&pd3dxBuffer,			// (3)
		NULL,
		&numMaterials,					// (4)
		&pd3dxMesh);				// (5)

	numMatModel = numMaterials;	//データを読み込んでG変数へ読み込む


	D3DXMATERIAL *pD3DXMat;
	// マテリアルデータ配列へのポインタを取得
	pD3DXMat = (D3DXMATERIAL*)pd3dxBuffer->GetBufferPointer();
	pTex = new LPDIRECT3DTEXTURE9[numMatModel];

	for (int i = 0; i < numMatModel; ++i){
		pTex[i] = nullptr;
		HRESULT hr = D3DXCreateTextureFromFile(GetD3DDevice,
			pD3DXMat[i].pTextureFilename, &pTex[i]);
		if (FAILED(hr)) pTex[i] = NULL;
	}

	GetD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	return result;
}

void xFileClass::Draw(D3DXMATRIX* wMtx){
	GetD3DDevice->SetTransform(D3DTS_WORLD, wMtx);
	GetD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pD3DXMat;

	// Todo: もしテクスチャ有りのモデルを使う場合はコメントアウト
	//GetD3DDevice->SetTexture(0, NULL);

	// 現在のマテリアル設定を一時保存
	GetD3DDevice->GetMaterial(&matDef);

	// マテリアルデータ配列へのポインタを取得
	pD3DXMat = (D3DXMATERIAL*)pd3dxBuffer->GetBufferPointer();

	// コメント記述
	for (int nCntMat = 0; nCntMat < numMatModel; nCntMat++)
	{
		GetD3DDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// Todo: もしテクスチャ有りのモデルを使う場合はSetTexture呼出を実装する
		GetD3DDevice->SetTexture(0, pTex[nCntMat]);

		pd3dxMesh->DrawSubset(nCntMat);
	}

	// 以前のマテリアル設定に戻す
	GetD3DDevice->SetMaterial(&matDef);
}