#pragma once




//! ��������
void GameInit();

//! �X�V����
void GameUpdate();

//! �`�揈��
void GameDraw();

//! �I������
void GameExit();




//
////! �X�e�[�^�X�o�[�`��p�̊֐�
//void StatusDraw();
//
////! �U���Ɋւ���X�V����
//void AttackUpdate();

////! ���_�V�F�[�_�[�p�̕ϐ�
//int vertex_shader;
//
////! �s�N�Z���V�F�[�_�[�p�̕ϐ�
//int pixel_shader;



// �V�[���؂�ւ��p�̊֐�
// ����
// �P�F���̃V�[��
// �Q�F���̃V�[��
void Scene_Change_Judge(int& now_scene, const int& next_scene);
