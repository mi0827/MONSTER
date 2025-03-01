#pragma once
//! 初期処理
void GameInit();

//! 更新処理
void GameUpdate();

//! 描画処理
void GameDraw();

//! 終了処理
void GameExit();

//! @brief BGMを変更する関数
//! @parma BGMが保存されている番号 
void ChangeBgm(int bgm_num);

//
////! ステータスバー描画用の関数
//void StatusDraw();
//
////! 攻撃に関する更新処理
//void AttackUpdate();

////! 頂点シェーダー用の変数
//int vertex_shader;
//
////! ピクセルシェーダー用の変数
//int pixel_shader;
