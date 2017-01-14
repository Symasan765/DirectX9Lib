/*=========================================================//
//		�T�v	:	�s��v�Z�������N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//=========================================================*/
#ifndef INC_MATRIX_COORD_H
#define INC_MATRIX_COORD_H
#include <d3dx9.h>

//�ϊ��p�s��
typedef struct{
	D3DXMATRIX mtxWorld;	//���[���h�s��
	D3DXMATRIX mtxScale;	//�g��k���s��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrans;	//�ړ��s��
}MATRIX3D;


class cMatrix{
public:
	cMatrix();
	virtual ~cMatrix() = default;
	/*===�g��k���E�ړ��E��]===*/
	virtual void Scaling(const float);
	virtual void Translation(const D3DXVECTOR3);
	virtual void Rotation(const float, const float, const float);
	/*===�g��k���E�ړ��E��]�̏�����===*/
	virtual void SetScaling(const float);
	void SetRotate(const float, const float, const float);
	void SetTrans(const D3DXVECTOR3);
	/*===���[���h�s��֌v�Z���s��(����c�����낤���c)===*/
	void MatrixCalculation();
	/*===�����Ă�������ւ̈ړ�===*/
	virtual void VectMove(const float);
	/*===�e�s��̃|�C���^�擾===*/
	virtual D3DXMATRIX* GetWorldMatrix();
	D3DXMATRIX* GetScaleMatrix();
	D3DXMATRIX* GetRotatMatrix();
	D3DXMATRIX* GetTransMatrix();
	D3DXVECTOR3 GetPosition()const;
protected:
	void OwnAxisRotateX(const float);			//�C�ӎ���]X
	void OwnAxisRotateY(const float);			//�C�ӎ���]Y
	void OwnAxisRotateZ(const float);			//�C�ӎ���]Z

	MATRIX3D mtxDate;	//�\���̌Q
};

#endif