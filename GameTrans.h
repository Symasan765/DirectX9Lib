/*=========================================================//
//		�T�v	:	�Q�[���J�ڂ��Ǘ�����N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//			�Q�[���J�ڃN���X���L�q����
//=========================================================*/
#ifndef INC_GAME_TRANS_H
#define INC_GAME_TRANS_H

//��ԑJ�ڃN���X�̒��ۃN���X
class cGameTrans{
public:
	cGameTrans(){};
	virtual ~cGameTrans(){};
	virtual cGameTrans* update(cGameTrans*) = 0;
	void DrawBegine();	//�`��X�^�[�g
	void DrawEnd();		//�`��G���h
private:
	virtual void draw() = 0;
};


#endif