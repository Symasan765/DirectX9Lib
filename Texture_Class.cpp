#include "Texture_Class.h"
#include "GameManager.h"
#include <cmath>
#define PI (3.14159265)

/*===================================================
//	�֐�	:	�e�N�X�`���t�@�C����ǂݍ��ރR���X�g���N�^
//	����	:	fileNmae - �ǂݍ��ރe�N�X�`���t�@�C����
//				anmNo - �A�j���[�V�����ԍ�
//				widthNo - �������A�j���[�V������
//				heightNo - �c�����A�j���[�V������
//	���l	:	anmeNo�ȍ~�ȗ��B�ȗ������ꍇ�̓e�N�X�`���ꖇ�S�̂��w�肳���
//				���W�͐ݒ肳��Ă��Ȃ��̂ł܂��K���ݒ肷��
===================================================*/
Texture2D::Texture2D(const char* fileName, const short anmNo, const unsigned char widthNo, const unsigned char heightNo){
	bool result = true;	//�e�N�X�`����ǂ߂����i�[����
	pTex = nullptr;		//�e�N�X�`���͏����ł͎g�p���Ȃ�

	//�e�N�X�`����ǂݍ��ݐ^�U���i�[
	if (fileName)
		result = SUCCEEDED(D3DXCreateTextureFromFile(GetD3DDevice, fileName, &pTex));

	//����ɓǂ߂���UV�l�ݒ�
	if (result)
	{
		//�e�N�X�`���ԍ��A�e�N�X�`����(�c��)����`��ʒu������o��
		const float offset_tu = (float)1 / widthNo;		//tu�T�C�Y
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
	vx[0].z = vx[1].z = vx[2].z = vx[3].z = 0;

	//2D�t���O
	vx[0].rhw = vx[1].rhw = vx[2].rhw = vx[3].rhw = 1;

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


	//���S���W�ݒ�(�����ł͍��W�ݒ肳��Ă��Ȃ��̂Œ��S������)
	center.x = NULL;
	center.y = NULL;

	uvReversFlag = true;
}


/*===================================================
//	�֐�	:	�m�ۂ��Ă����e�N�X�`�����������f�X�g���N�^		//
===================================================*/
Texture2D::~Texture2D(){
	pTex->Release();	//���
	pTex = nullptr;	//���S�̂��߂�
}


/*===================================================
//	�֐�	:	�e�N�X�`����`�悷��֐�						//
===================================================*/
void Texture2D::Draw() const{
	//�e�N�X�`���̗L���ŏ����𕪂���
	if (pTex){
		GetD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);	//�F������(�����̓R���X�g���N�^�ɂ�蔒)
		//�e�N�X�`�����]����
		if (uvReversFlag){
			GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			GetD3DDevice->SetTexture(0, pTex);
			GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
		}
		else{
			VERTEX2D buf[4];
			for (int i = 0; i < 4; i++){
				buf[i] = vx[i];
			}

			buf[0].tu = vx[1].tu;
			buf[0].tv = vx[1].tv;
			buf[1].tu = vx[0].tu;
			buf[1].tv = vx[0].tv;

			GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			GetD3DDevice->SetTexture(0, pTex);
			GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
		}
		
	}
	else{
		GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);		//�e�N�X�`���Ȃ�
		GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
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
void Texture2D::SetPosition(const float baseX, const float baseY, const float sizeX, const float sizeY){
	//���W�ݒ�
	vx[0].x = baseX;
	vx[0].y = baseY;

	vx[1].x = baseX + sizeX;
	vx[1].y = baseY;

	vx[2].x = baseX + sizeX;
	vx[2].y = baseY + sizeY;

	vx[3].x = baseX;
	vx[3].y = baseY + sizeY;

	//���S���W�ݒ�
	center.x = (vx[1].x - vx[0].x) / 2 + vx[0].x;
	center.y = (vx[2].y - vx[0].y) / 2 + vx[0].y;
}


/*===================================================
//	�֐�	:	�e�N�X�`���t�@�C����ǂݍ��ފ֐�
//	����	:	anmNo - �A�j���[�V�����ԍ�
//				widthNo - �������A�j���[�V������
//				heightNo - �c�����A�j���[�V������
//	���l	:	anmeNo�ȍ~�ȗ��B�ȗ������ꍇ�̓e�N�X�`���ꖇ�S�̂��w�肳���
===================================================*/
void Texture2D::SetTextureUV(short anmNo, const unsigned char widthNo, const unsigned char heightNo){
		anmNo %= widthNo * heightNo;

		//�e�N�X�`���ԍ��A�e�N�X�`����(�c��)����`��ʒu������o��
		const float offset_tu_size = (float)1 / widthNo;			//tu�T�C�Y
		const float offset_tv_size = (float)1 / heightNo;		//tv�T�C�Y
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
void Texture2D::SetColor(D3DCOLOR DIF){
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = DIF;
}

/*===================================================
//	�֐�	:	�}�`����]������֐�
//	����	:	angle - ��]�p�x(0 ~ 360)
===================================================*/
void Texture2D::Rotat(const float angle){
	//��]�p�x�̃��W�A�����o���Ă���
	const float rad = static_cast<float>(angle * PI / 180.0f);

	//��]����
	for (int i = 0; i < 4; ++i)
		RotatePrimitive(vx[i], center, rad);
}

/*===================================================
//	�֐�	:	�}�`���g��E�k������֐�
//	����	:	rate - �g�k��(1.0 == 100%,0.0 == 0%)
===================================================*/
void Texture2D::Scale(const float rate){
	for (int i = 0; i < 4; ++i)
		ScalePrimitive(vx[i], center, rate);
}

/*===================================================
//	�֐�	:	�ړ��������s���֐�
//	����	:	moveX - ���ړ���,moveY - �c�ړ���
===================================================*/
void Texture2D::Move(const float moveX, const float moveY){
	//�e���_���ړ�
	for (int i = 0; i < 4; ++i)
	{
		MovePrimitive(vx[i], moveX, moveY);
	}

	//�Ō�ɒ��S���W���ړ�
	center.x += moveX;
	center.y += moveY;
}


/*===================================================
//	�֐�	:	�ړ��������s���֐�
//	�ߒl	:	���S���W���ԋp
===================================================*/
POS2D Texture2D::GetCenter() const{
	return center;
}


/*============================================�ʏ�֐�(�O���Ɍ�����K�v�Ȃ�)==========================================================*/

/*===================================================
//	�֐�	:	�n���ꂽ���W���N�_�����]����֐�
//	����	:	src - ��]������W
base - ��]�̋N�_(��)
rad - ���W�A��
===================================================*/
void Texture2D::RotatePrimitive(VERTEX2D& src, const POS2D base, const float rad){
	VERTEX2D buf = src;		//�o�b�t�@

	//��]����
	src.x = ((buf.x - base.x) * cosf(rad) - (buf.y - base.y) * sinf(rad)) + base.x;
	src.y = ((buf.x - base.x) * sinf(rad) + (buf.y - base.y) * cosf(rad)) + base.y;
}


/*===================================================
//	�֐�	:	�n���ꂽ���W���N�_�𒆐S�Ɋg�k����֐�
//	����	:	src - �ύX���钸�_���
//				base - �N�_(���S)
rate - �g��E�k����(0.0 == 0%,1.0 == 100%)
===================================================*/
void Texture2D::ScalePrimitive(VERTEX2D& src, const POS2D base, const float rate){
	VERTEX2D buf = src;

	//�g��E�k������
	src.x = (buf.x - base.x) * rate + base.x;
	src.y = (buf.y - base.y) * rate + base.y;
}

/*===================================================
//	�֐�	:	���_�̈ړ����s���֐�
//	����	:	src - �ύX���钸�_
//				moveX - ���ړ���
//				moveY - �c�ړ���
===================================================*/
void Texture2D::MovePrimitive(VERTEX2D& src, const float moveX, const float moveY){
	src.x += moveX;
	src.y += moveY;
}

/*===================================================
//	�֐�	:	�e�N�X�`�����X�N���[������֐�
//	����	:	moveU - �ړ���U
//				moveV - �ړ���V
===================================================*/
void Texture2D::TexUVScroll(const float moveU, const float moveV){
	for (int i = 0; i < 4; ++i){
		vx[i].tu += moveU;
		vx[i].tv += moveV;
	}
}