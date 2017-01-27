#include "Main.h"
#include "Texture_Class.h"

/*===================================================
//	���C������
//	����	��O�̑J�ڃN���X�̃|�C���^���n�����
//	�ߒl	�J�ڂ���ꍇ�A���Ɉڂ�J�ڐ�A�h���X��n��
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================���C��������������============================*/

	draw();
	return this;	//��ԑJ�ڂ��Ȃ���Ύ�����Ԃ�
}

/*===================================================
//	�`�揈��
//	�`��@�\�������ɏ������݁AUpdate�ŌĂяo����OK
===================================================*/
void MainLoop::draw(){
	DrawBegine();	//���炩����Begine�Ɓc

	/*=================�`�揈��===================*/
	//�e�X�`�悷�邺

	int stage[6][10] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 0, 2, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 3, 0, 2, 0, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	Back->Draw();

	for (int height = 0; height < 6; height++){
		for (int width = 0; width < 10; width++){
			switch (stage[height][width])
			{
			case 0:		//�X���[
				break;
			case 1:
				Block->SetPosition(width * 72,height * 72 + 10,72.0f,72.0f);
				Block->Draw();
				break;
			case 2:
				Adhesion->SetPosition(width * 72, height * 72 + 10, 72.0f, 72.0f);
				Adhesion->Draw();
				break;
			case 3:
				Character->SetPosition(width * 72, height * 72 + 10, 72.0f, 72.0f);
				Character->Draw();
				break;
			default:
				break;
			}
		}
	}
	/*===========================================*/

	DrawEnd();		//End�������Ă����Ƃ��̊Ԃɏ����������΍ςނ�I
}

/*===================================================
//	����������
//	�Q�[�����Ŏg�p����ϐ��̓w�b�_�[�Œ�`�������ŏ�����
===================================================*/
MainLoop::MainLoop(){
	Back = new Texture2D("image/back.jpg");
	Back->SetPosition(0.0f, 0.0f, 720.0f, 480.0f);
	Character = new Texture2D("image/character.png");
	Block = new Texture2D("image/block.png");
	Adhesion = new Texture2D("image/special.png");
}

/*===================================================
//	�������
//	�Q�[�����Ŏg�p�����ϐ��͂��������Еt�����܂��傤�ˁI
===================================================*/
MainLoop::~MainLoop(){
	delete Back;
	delete Character;
	delete Block;
	delete Adhesion;
}