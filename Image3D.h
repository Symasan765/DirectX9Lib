/*=========================================================//
//		�T�v	:	3D��ԏ�Ŏg�p����摜�N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/10
//					  �X�V��
//
//=========================================================*/
#ifndef INC_IMAGE_3D_H
#define INC_IMAGE_3D_H

#include <Windows.h>
#include <d3dx9.h>
#include "MatrixCoord.h"

//���_���W�\����
typedef struct{
	float x, y, z;
	D3DCOLOR diffuse;	//�J���[
	float tu, tv;			//�e�N�X�`���ʒu
}VERTEX3D;

/**
*	�e�N�X�`���̓ǂݎ��ƕ`����s���N���X
*	�P�̂Ŏg�p���鎖�͑z�肵�Ă��炸
*	�s��N���X�Ȃǂ̃����o�ɓ���Ďg�p����(cImage3D�N���X��)
*/
class Texture3D{
public:
	Texture3D(const char*, const short = 0, const unsigned char = 1, const unsigned char = 1);
	virtual ~Texture3D();
	virtual void Draw(D3DXMATRIX*,bool = true);		//������false���킽���ƃZ�b�g�e�N�X�`�����X���[�o����
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
	VERTEX3D vx[4];				//���_���
	LPDIRECT3DTEXTURE9 pTex;	//�e�N�X�`���|�C���^�ϐ�
	bool colorFlag;				//�J���[�����邩�H
};

/**
*	�摜�N���X
*	3D��ԏ�Ƀe�N�X�`����\��������
*/
class cImage3D : public cMatrix{
public:
	cImage3D(Texture3D*);
	virtual ~cImage3D();
	/**
	*	@brief �e�N�X�`���|�C���^���擾����
	*	@return �e�N�X�`���|�C���^
	*/
	Texture3D* GetTexture();
	/**
	*	@brief �e�N�X�`���T�C�Y��ݒ肷��
	*	@param  sizeX-������,sizeY-�c����
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
	Texture3D* pTex;		//!<�@@brief �e�N�X�`���|�C���^
};

#endif