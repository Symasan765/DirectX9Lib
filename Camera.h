/**
* @file Camera.h
* @brief �J�����N���X�̒�`
* @author ���{�Y�V��
* @date 2016/12/26
*/
#ifndef INC_CAMERA_H
#define INC_CAMERA_H
#include "MatrixCoord.h"
#include <d3dx9.h>

/**
* @def MAXIMUM_MAGNIFICATION
* @brief �ő�B�e�{��
*/
#define MAXIMUM_MAGNIFICATION (90)

/**
* @def MINIMUM_MAGNIFICATION
* @brief �ŒZ�B�e�{��
*/
#define MINIMUM_MAGNIFICATION (1)


/**
*	�J�����N���X
*	���W�ʒu�͍s��N���X���Ǘ�����
*/
class cCamera : public cMatrix{
public:
	cCamera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	~cCamera();
	void Projection(const LPDIRECT3DDEVICE9);
	virtual void Scaling(const float);
	virtual void Rotation(const float, const float, const float);		//FPS��]
	void SetLookPos(D3DXVECTOR3);		//���_�ʒu�Z�b�g
	void PointRotatMove(const float, const float, const float);					//�����_�𒆐S�ɂ�����]�ړ�	TPS��]
	void PointRotatMove(const float, const float, const float, D3DXVECTOR3);	//�w��̋N�_�𒆐S�ɂ�����]�ړ�
	D3DXVECTOR3 GetLookPos()const;
	D3DXVECTOR3 GetUpVect()const;
	D3DXVECTOR3 GetCameraPos()const;
	D3DXMATRIX* GetWorldMatrix();
private:
	void RotationAxisX(const D3DXVECTOR3&, const float);
	void RotationAxisY(const D3DXVECTOR3&, const float);
	void RotationAxisZ(const D3DXVECTOR3&, const float);
	D3DXVECTOR3 LookPt;		//!<�@@brief �����_
	D3DXVECTOR3 UpVect;		//!<�@@brief �J���������
	float AngleOfView;		//!<�@@brief ��p
	float ViewScopeMax;		//!<�@@brief ����ő�
	float ViewScopeMin;		//!<�@@brief ����ŏ�
};



#endif