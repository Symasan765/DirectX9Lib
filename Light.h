/*=========================================================//
//		�T�v	:	���C�g�������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//	
//=========================================================*/
#ifndef INC_LIGHT_H
#define INC_LIGHT_H

#include <Windows.h>
#include <d3dx9.h>

#define MORNINNG_R 184.0f
#define MORNINNG_G 141.0f
#define MORNINNG_B 194.0f

#define NOON_R 255.0f
#define NOON_G 255.0f
#define NOON_B 255.0f

#define EVENING_R 220.0f
#define EVENING_G 92.0f
#define EVENING_B 10.0f

#define NIGHT_R 85.0f
#define NIGHT_G 35.0f
#define NIGHT_B 95.0f

//���Ԍo��
enum season{
	MORNINNG = 0,		//��
	NOON,				//��
	EVENING,			//�[
	NIGHT				//��
};

class cLight{
public:
	cLight();
	~cLight();
	void InitLight();
	void DayNightUpdate(const float Second);
	D3DCOLOR GetLightColor();
private:
	bool EveningChange(const float Second);
	bool NoonChange(const float Second);
	bool NightChange(const float Second);
	bool MorningChange(const float Second);
	D3DXVECTOR3 vect;
	D3DLIGHT9 aLight[2];
	//�����̈ʒu	(��������Ɍ��̃x�N�g�����v�Z����\��)
	//�����̐F		(���̐F�̐���ɕK�v)
	float R, G, B;
	unsigned int FpsCnt;
	season time;
public:
};


#endif