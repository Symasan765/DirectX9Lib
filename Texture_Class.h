/*=========================================================//
//		�T�v	:
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��
//					  �X�V��
//=========================================================*/
#ifndef _INC_TEXTURE_CLASS_H_
#define _INC_TEXTURE_CLASS_H_

/*=======================#include========================*/
#include <Windows.h>
#include <d3dx9.h>

/*=========================��`==========================*/
//float X,Y���W
typedef struct _pos2d{
	float x;
	float y;
}POS2D;

//float U,V
typedef struct _uv2d{
	float u;
	float v;
}UV2D;

//���_���W�\����
typedef struct{
	float x, y, z;			//z�͎g���Ȃ�
	float rhw;				//2D�p�t���O�̂悤�Ȃ���
	D3DCOLOR diffuse;	//�J���[
	float tu, tv;			//�e�N�X�`���ʒu
}VERTEX2D;

/*===================================================
//	�N���X	:	�}�`�v�Z�n�̏����𑼂̃N���X�֒񋟂��钊�ۃN���X
===================================================*/
class Texture2D{
public:
	Texture2D(const char*, const short = 0, const unsigned char = 1, const unsigned char = 1);
	~Texture2D();
	void Draw() const;
	void Rotat(const float);
	void Move(const float, const float);
	void Scale(const float);
	void SetPosition(const float,const float,const float,const float);
	void SetTextureUV(short, const unsigned char, const unsigned char);
	void SetColor(D3DCOLOR);
	POS2D GetCenter() const;
	void reversal(bool);
	void TexUVScroll(const float, const float);
protected:
	VERTEX2D vx[4];				//���_���
	LPDIRECT3DTEXTURE9 pTex;	//�e�N�X�`���|�C���^�ϐ�
	POS2D center;					//�}�`�̒��S���W
private:
	void RotatePrimitive(VERTEX2D&, const POS2D, const float);
	void ScalePrimitive(VERTEX2D&, const POS2D, const float);
	void MovePrimitive(VERTEX2D&, const float, const float);
	bool uvReversFlag;		//UV�̔��](�^�Œʏ� : �U�Ŕ��])
};

#endif