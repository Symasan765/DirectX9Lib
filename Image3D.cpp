/*=========================================================//
//		�T�v	:	3D��ԏ�Ŏg�p����摜�N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/10
//					  �X�V��
//
//=========================================================*/
#include "Image3D.h"
#include "GameManager.h"

#define PI (3.14159)
void RotatePrimitive(VERTEX3D&, const COORD, const float);
void ScalePrimitive(VERTEX3D&, const COORD, const float);
void MovePrimitive(VERTEX3D&, const float, const float);

/*===================================================
//	�֐�	:	�e�N�X�`���t�@�C����ǂݍ��ރR���X�g���N�^
//	����	:	fileNmae - �ǂݍ��ރe�N�X�`���t�@�C����
//				anmNo - �A�j���[�V�����ԍ�
//				widthNo - �������A�j���[�V������
//				heightNo - �c�����A�j���[�V������
//	���l	:	anmeNo�ȍ~�ȗ��B�ȗ������ꍇ�̓e�N�X�`���ꖇ�S�̂��w�肳���
//				���W�͐ݒ肳��Ă��Ȃ��̂ł܂��K���ݒ肷��
===================================================*/
Texture3D::Texture3D(const char* fileName, const short anmNo, const unsigned char widthNo, const unsigned char heightNo)
{
	bool result = true;	//�e�N�X�`����ǂ߂����i�[����
	pTex = nullptr;		//�e�N�X�`���͏����ł͎g�p���Ȃ�

	//�e�N�X�`����ǂݍ��ݐ^�U���i�[
	if (fileName)
		result = SUCCEEDED(D3DXCreateTextureFromFile(GetD3DDevice, fileName, &pTex));

	//����ɓǂ߂���UV�l�ݒ�
	if (result)
	{
		//�e�N�X�`���ԍ��A�e�N�X�`����(�c��)����`��ʒu������o��
		const float offset_tu = (float)1 / widthNo;			//tu�T�C�Y
		const float offset_tv = (float)1 / heightNo;		//tv�T�C�Y
		const unsigned char xNo = anmNo % widthNo;
		const unsigned char yNo = anmNo / widthNo;

		//���ۂ�UV�֊i�[
		vx[0].tu = xNo * offset_tu;
		vx[0].tv = yNo * offset_tv;

		vx[1].tu = xNo * offset_tu + offset_tu;
		vx[1].tv = yNo * offset_tv;

		vx[2].tu = xNo * offset_tu + offset_tu;
		vx[2].tv = yNo * offset_tv + offset_tv;

		vx[3].tu = xNo * offset_tu;
		vx[3].tv = yNo * offset_tv + offset_tv;
	}
	else
		result = false;


	//Z���W�N���A
	vx[0].z = vx[1].z = vx[2].z = vx[3].z = NULL;

	//�J���[��񏉊��l
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);

	//���W�ݒ�(�Ƃ肠�����S��NULL)
	vx[0].x = NULL;
	vx[0].y = NULL;

	vx[1].x = NULL;
	vx[1].y = NULL;

	vx[2].x = NULL;
	vx[2].y = NULL;

	vx[3].x = NULL;
	vx[3].y = NULL;
}

/*===================================================
//	�֐�	:	�m�ۂ��Ă����e�N�X�`�����������f�X�g���N�^		//
===================================================*/
Texture3D::~Texture3D()
{
	pTex->Release();	//���
	pTex = nullptr;	//���S�̂��߂�
}

/*===================================================
//	�֐�	:	�e�N�X�`����`�悷��֐�						//
===================================================*/
void Texture3D::Draw(D3DXMATRIX* mtx){
	GetD3DDevice->SetTransform(D3DTS_WORLD, mtx);
	// ���C�e�B���O���[�h��OFF
	GetD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//�e�N�X�`���̗L���ŏ����𕪂���
	if (pTex)
	{
		GetD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		GetD3DDevice->SetTexture(0, pTex);
		GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX3D));
	}
	else
	{
		//GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);		//�e�N�X�`���Ȃ�
		//GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX3D));
	}
}


/*===================================================
//	�֐�	:	���W��ݒ肷��֐�
//	����	:	baseX - ������WX
//				baseY - ������WY
//				sizeX - �傫��(������)
//				sizeY - �傫���i�c�����j
//	���l	:	���_�ԍ���0������X�^�[�g�Ŏ��v����ݒ�(�����I�ɕύX)
===================================================*/
void Texture3D::SetSize(const float sizeX, const float sizeY){

	//���W�ݒ�
	vx[0].x = -sizeX / 2;
	vx[0].y = sizeY / 2;

	vx[1].x = sizeX / 2;
	vx[1].y = sizeY / 2;

	vx[2].x = sizeX / 2;
	vx[2].y = -sizeY / 2;

	vx[3].x = -sizeX / 2;
	vx[3].y = -sizeY / 2;
}

/*===================================================
//	�֐�	:	�e�N�X�`���t�@�C����ǂݍ��ފ֐�
//	����	:	anmNo - �A�j���[�V�����ԍ�
//				widthNo - �������A�j���[�V������
//				heightNo - �c�����A�j���[�V������
//	���l	:	anmeNo�ȍ~�ȗ��B�ȗ������ꍇ�̓e�N�X�`���ꖇ�S�̂��w�肳���
===================================================*/
void Texture3D::SetTextureUV(short anmNo, const unsigned char widthNo, const unsigned char heightNo){
	anmNo %= widthNo * heightNo;

	//�e�N�X�`���ԍ��A�e�N�X�`����(�c��)����`��ʒu������o��
	const float offset_tu_size = (float)1 / widthNo;			//tu�T�C�Y
	const float offset_tv_size = (float)1 / heightNo;			//tv�T�C�Y
	const unsigned char xNo = anmNo % widthNo;
	const unsigned char yNo = anmNo / widthNo;

	//���ۂ�UV�֊i�[
	vx[0].tu = xNo * offset_tu_size;
	vx[0].tv = yNo * offset_tv_size;

	vx[1].tu = xNo * offset_tu_size + offset_tu_size;
	vx[1].tv = yNo * offset_tv_size;

	vx[2].tu = xNo * offset_tu_size + offset_tu_size;
	vx[2].tv = yNo * offset_tv_size + offset_tv_size;

	vx[3].tu = xNo * offset_tu_size;
	vx[3].tv = yNo * offset_tv_size + offset_tv_size;
}

/*===================================================
//	�֐�	:	�|���S���̐F��ύX����֐�
//	����	:	DIF - �\������F(RGB 0 ~ 255)
//	���l	:	�S�Ă̒��_�������F�ɂȂ�
===================================================*/
void Texture3D::SetColor(D3DCOLOR DIF)
{
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = DIF;
}


/*============================================�ʏ�֐�==========================================================*/

/*===================================================
//	�֐�	:	�n���ꂽ���W���N�_�����]����֐�
//	����	:	src - ��]������W
base - ��]�̋N�_(��)
rad - ���W�A��
===================================================*/
void RotatePrimitive(VERTEX3D& src, const COORD base, const float rad)
{
	VERTEX3D buf = src;		//�o�b�t�@

	//��]����
	src.x = ((buf.x - base.X) * cosf(rad) - (buf.y - base.Y) * sinf(rad)) + base.X;
	src.y = ((buf.x - base.X) * sinf(rad) + (buf.y - base.Y) * cosf(rad)) + base.Y;
}


/*===================================================
//	�֐�	:	�n���ꂽ���W���N�_�𒆐S�Ɋg�k����֐�
//	����	:	src - �ύX���钸�_���
//				base - �N�_(���S)
rate - �g��E�k����(0.0 == 0%,1.0 == 100%)
===================================================*/
void ScalePrimitive(VERTEX3D& src, const COORD base, const float rate)
{
	VERTEX3D buf = src;

	//�g��E�k������
	src.x = (buf.x - base.X) * rate + base.X;
	src.y = (buf.y - base.Y) * rate + base.Y;
}

/*===================================================
//	�֐�	:	���_�̈ړ����s���֐�
//	����	:	src - �ύX���钸�_
//				moveX - ���ړ���
//				moveY - �c�ړ���
===================================================*/
void MovePrimitive(VERTEX3D& src, const float moveX, const float moveY)
{
	src.x += moveX;
	src.y += moveY;
}

void Texture3D::ScrollUV(const float moveU, const float moveV){
	vx[0].tu += moveU;
	vx[0].tv += moveV;

	vx[1].tu += moveU;
	vx[1].tv += moveV;

	vx[2].tu += moveU;
	vx[2].tv += moveV;

	vx[3].tu += moveU;
	vx[3].tv += moveV;
}

Texture3D* cImage3D::GetTexture(){
	return pTex;
}

void cImage3D::SetTexSize(const float sizeX, const float sizeY){
	if (pTex)
		pTex->SetSize(sizeX, sizeY);
}

void cImage3D::Draw(){
	if (pTex){
		MatrixCalculation();
		pTex->Draw(GetWorldMatrix());
	}
}

cImage3D::cImage3D(Texture3D* texture){
	if (!pTex)
		delete pTex;

	pTex = texture;
}
cImage3D::~cImage3D(){
	if (pTex){
		delete pTex;
		pTex = nullptr;
	}
}

//void Texture3D::SetBillboard(D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct){
//	D3DXMatrixIdentity(&Inv);
//	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0, 0, 0), &LookVct, &UpVct);
//	D3DXMatrixInverse(&Inv, NULL, &Inv);
//
//	if (BillBoardFlg == false){
//		for (int i = 0; i < 4; i++){
//			vx[i].y = vx[i].z;	//�c�����ɗ�������
//			vx[i].z = 0;
//		}
//		BillBoardFlg = true;
//	}
//}