/*=========================================================//
//		�T�v	:	X�t�@�C���������N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
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
	LPD3DXMESH pd3dxMesh;				// ���b�V���f�[�^�ւ̃|�C���^��ێ�
	LPD3DXBUFFER pd3dxBuffer;			// �}�e���A���f�[�^�ւ̃|�C���g��ێ�
	LPDIRECT3DTEXTURE9* pTex;
	int numMatModel;						// �}�e���A���̐���ێ�
};

#endif