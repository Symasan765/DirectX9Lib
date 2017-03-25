/*=========================================================//
//		�T�v	:	X�t�@�C���������N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
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
	LPD3DXMESH pd3dxMesh;				// ���b�V���f�[�^�ւ̃|�C���^��ێ�
	LPD3DXBUFFER pd3dxBuffer;			// �}�e���A���f�[�^�ւ̃|�C���g��ێ�
	LPDIRECT3DTEXTURE9* pTex;
	D3DXMATERIAL* pD3DXMat;
	int numMatModel;						// �}�e���A���̐���ێ�
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
	LPD3DXEFFECT              m_pEffect;        // �G�t�F�N�g
	D3DXHANDLE                m_hTechnique;    // �e�N�j�b�N
	D3DXHANDLE                m_hmWVP;        // ���[�J��-�ˉe�ϊ��s��
	D3DXHANDLE                m_hmWIT;        // ���[�J��-���[���h�ϊ��s��
	D3DXHANDLE                m_hvLightDir;    // ���C�g�̕���
	D3DXHANDLE                m_hvCol;        // ���_�F
	D3DXHANDLE                m_hvEyePos;        // �J�����ʒu
};

#endif