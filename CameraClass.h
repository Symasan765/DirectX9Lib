///*=========================================================//
////		�T�v	:	�J�����N���X�p�w�b�_�[
////					�쐬�ҁ@���{ �Y�V�� (AT12A606)
////						�쐬���@2016/10/20
////					  �X�V��
////
////			�J�������`����w�b�_�[�t�@�C��
////=========================================================*/
//#ifndef INC_CAMERA_CLASS_H
//#define INC_CAMERA_CLASS_H
//
//#define MAXIMUM_MAGNIFICATION (90)		//�ő�B�e�{��
//#define MINIMUM_MAGNIFICATION (1)			//�ŒZ�B�e�{��
//
//
//#include <d3dx9.h>
////���W3D�p
//typedef struct{
//	float x, y, z;
//}COORD3D;
//
//
////�J�����ʒu�N���X
////	�J�������W�Z�b�g
////	�J�����ړ����[�u
//class cCameraP{
//public:
//	cCameraP();
//	~cCameraP();
//	void Set(const float,const float,const float);
//	void Move(const float,const float,const float);
//	D3DXVECTOR3 cP;
//private:
//	bool ellor;
//};
//
////�J����
////	�J�������F�ʒu�N���X
////	���F�ʒu�Z�b�g
////	���F�ʒu���[�u
//class cCameraR{
//public:
//	cCameraR();
//	~cCameraR();
//	void Set(const float, const float, const float);
//	void Move(const float, const float, const float);
//	D3DXVECTOR3 cR;	//���Ă���ʒu
//private:
//	bool ellor;
//};
//
////�J�����X�΃N���X
////	���Z�b�g
////	�J�����X��
//class cCameraU{
//public:
//	cCameraU();
//	~cCameraU();
//	void Set(const float, const float, const float);
//	D3DXVECTOR3 cU;
//private:
//	bool ellor;
//};
//
////�J�����\����
//typedef struct{
//	cCameraP cameraP;
//	cCameraR cameraR;
//	cCameraU cameraU;
//	float AngleOfView;		//��p
//	float ViewScopeMax;		//����ő�
//	float ViewScopeMin;		//����ŏ�
//}CameraMnj;
//
//typedef struct{
//	D3DXMATRIX mtxWorld;
//	D3DXMATRIX mtxScale;
//	D3DXMATRIX mtxRot;
//	D3DXMATRIX mtxTrans;
//}CAMERA_MATRIX;
//
////�J�����p�\���̂��`
//class cCamera{
//public:
//	cCamera();
//	~cCamera();
//	//�Z�b�g�n�֐�
//	void SetCamera(COORD3D, COORD3D, COORD3D);						//�J���������ݒ�
//	void Projection(const LPDIRECT3DDEVICE9);						//�J�����ݒ�
//	void scaling(const float);
//	void translation(const float, const float, const float);		//���s�ړ�
//	void rotation(const float, const float, const float);			//���_���N�_�ɂ�����]
//	void rotation(D3DXMATRIX);											//��]
//	void PovUpVectorRotat(D3DXMATRIX);								//�J�����̏��������]
//	void PovBaseXRotation(const float);
//	void SetLookPos(D3DXMATRIX);										//���_�ʒu�Z�b�g
//	void SetLookPos(const float, const float, const float);		//���_�ʒu�Z�b�g
//	D3DXVECTOR3 GetLookVector()const;								//���_�ʒu�擾
//	D3DXVECTOR3 GetpUpVector()const;									//�J����������擾
//	D3DXMATRIX* GetWorldMtx();
//private:
//	void WorldMatrixCalcu();
//	void MtxInit(D3DXMATRIX*);
//	CAMERA_MATRIX mtxCamera;
//	CameraMnj machine;
//	bool ellor;
//};
//
//
//
//
//
//#endif