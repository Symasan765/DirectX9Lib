/*=========================================================//
//		�T�v	:	X�t�@�C���������N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//=========================================================*/
#include "XfileDX9.h"
#include "GameManager.h"


xFileClass::xFileClass(){
	pd3dxMesh = nullptr;		// ���b�V���f�[�^�ւ̃|�C���^��ێ�
	pd3dxBuffer = nullptr;	// �}�e���A���f�[�^�ւ̃|�C���g��ێ�
	pTex = nullptr;
	numMatModel = NULL;		// �}�e���A���̐���ێ�
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

	numMatModel = numMaterials;	//�f�[�^��ǂݍ����G�ϐ��֓ǂݍ���


	D3DXMATERIAL *pD3DXMat;
	// �}�e���A���f�[�^�z��ւ̃|�C���^���擾
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

	// Todo: �����e�N�X�`���L��̃��f�����g���ꍇ�̓R�����g�A�E�g
	//GetD3DDevice->SetTexture(0, NULL);

	// ���݂̃}�e���A���ݒ���ꎞ�ۑ�
	GetD3DDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�z��ւ̃|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)pd3dxBuffer->GetBufferPointer();

	// �R�����g�L�q
	for (int nCntMat = 0; nCntMat < numMatModel; nCntMat++)
	{
		GetD3DDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// Todo: �����e�N�X�`���L��̃��f�����g���ꍇ��SetTexture�ďo����������
		GetD3DDevice->SetTexture(0, pTex[nCntMat]);

		pd3dxMesh->DrawSubset(nCntMat);
	}

	// �ȑO�̃}�e���A���ݒ�ɖ߂�
	GetD3DDevice->SetMaterial(&matDef);
}