#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/System/Spotlight.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Effect/Effect.h"
#include "src/System/UIBar.h"
#include "src/Sound/Sound.h"
#include "src/Camera.h"


#include "src/Action/Combo.h"
#include "src/System/TargetMove.h"
#include "src/Character/MonsterBase.h"
#include "Monster.h"

namespace
{
	// プレイヤーのとのあたり判定で使うboxのあたり判定のサイズ
	const Vector3 M_MOVE_SIZE{ 15.0f,0,15.0f };
	// 上記で作成したサイズの半分のサイズ
	const Vector3 M_MOVE_SIZE_HALF{ M_MOVE_SIZE / 2 };
}


//-----------------------------------------------
// コンストラクタ
//-----------------------------------------------
Monster::Monster()
{
	// 最初はアイドル状態にしておく
	m_idle_flag = true;
	// 最初はアイドル状態にしておく
	m_monster_mode = IDLE;

	// 初期座標の設定
	m_transform.pos.set(50.0f, 0.0f, 50.0f);
	// モデルのスケールの設定
	m_transform.scale.set(0.2f, 0.2f, 0.2f);
}


//-----------------------------------------------
// デストラクタ
//-----------------------------------------------
Monster::~Monster()
{
	Exit();
}

//-----------------------------------------------
// 初期化処理
//-----------------------------------------------
void Monster::Init()
{
	// モデル画像の読み込み
	m_model.LoadModel("Data/Model/Monster/Monster.mv1");
	// アニメーションの初期設定
	Anima_Load_Init();

	// ステータスバーの設定
	StatusBarInit();

	// モンスターのステータス部分の設定
	MonsterBase::BaseInit(HP_MAX);
}

//-----------------------------------------------
// 更新処理
//-----------------------------------------------
void Monster::Update(Transform* traget_pos, float target_r,CapsuleCollision body, Camera* camera)
{
	clsDx();
	BaseSetTarget(traget_pos, target_r,body);

	// 待機状態または走りの時だけｗ
	// 移動処理
	if (m_idle_flag == true || m_run_flag == true /*&& m_monster_mode == IDLE*/)
	{
		// モンスターの回転してよいようにする
		m_move.SetCanRotate(true);
		// 移動処理
		Move_Update();
	}

	switch (m_monster_mode)
	{
	case IDLE: // 停止状態 
		if (m_idle_flag)
		{
			//Player_Mode(IDLE);
			// アニメーション変更が可能な時に
			if (m_animation.ChangeFlag(m_idle_flag))
			{
				// アニメーションを停止に変更する
				m_animation.ChangeAnimation(&m_model, idle, true);
			}

			// 移動が止まっていたら
			if (!m_move.m_hit)
			{
				// 最初の攻撃を行う
				// 攻撃フラグを上げる
				m_attack_flag = true;
				Attack_First();
			}
		}
		break;
	case RUN:
		// 待機フラグを毎回リセット
		m_idle_flag = false;
		// run_flagfフラグがさっがたら
		if (m_run_flag == false)
		{
			// 待機フラグを上げる
			m_idle_flag = true;
			// アニメーション変更が行えるようにする
			m_animation.m_anim_change_flag = true;
			m_monster_mode = IDLE;
		}

		// 走っている間に一定以上の距離が空いたら
		// ジャンプ攻撃をする
		Attack_Jump();

		break;
	case ATTACK:

		// 歩いてほしくないのでフラグを
		m_idle_flag = false;
		m_run_flag = false;

		// ジャンプ攻撃時の処理
		if (m_now_attack_anim == jump)
		{
			Jump_Update();
		}
		// 攻撃中(アニメーション中)は回転してほしくない
		m_move.SetCanRotate(false);
		// 歩いていい範囲かをプレイヤーの向きとあっていいるかを調べる
		m_move.m_hit = m_move.TargetHit();
		
		// アニメーションの再生が終わったとき
		if (m_animation.m_contexts[0].play_time >= m_animation.m_contexts[0].animation_total_time)
		{
			// 移動していい状態だったら
			if (m_move.m_hit)
			{
				// 移動フラグを立てる
				m_run_flag = true;
			}
		}
		// 攻撃用の関数
		Attack_Update();

		break;
	}

	// アニメーションの再生
	m_animation.PlayAnimation(&m_model, m_combo_flag);
	// あたり判定の更新処理
	CDUpdate();
}

//-----------------------------------------------
// 描画処理
//-----------------------------------------------
void Monster::Draw()
{
	// カプセルの描画(当たり判定)
	//m_body.Draw();
	//m_left_hand.Draw();
	//m_right_hand.Draw();
	// モデルの描画 (描画を後にしないと当たり判定がちかちかする)
	m_model.DrawModel(&m_transform);
}

//-----------------------------------------------
// 終了処理
//-----------------------------------------------
void Monster::Exit()
{
	m_se.StopSound();
}

//-----------------------------------------------
// あたり判定
//-----------------------------------------------
void Monster::CDUpdate()
{
	// キャラ本体の当たり判定のカプセル（後で消す）


	// この座標をモデルのノードをでとってくるといいかも
	// m_body.CreateCapsule(m_transform.pos);
	// m_body.SetSize({ 0.0f,25.0f, 0.0f }, 12);

	// 左手のあたり判定
	m_left_hand.CreateNodoCapsule(&m_model, 12, 22, 3.0f);
	

	// 右手の当たり判定
	m_right_hand.CreateNodoCapsule(&m_model, 36, 46, 3.0f);
	
}

//-----------------------------------------------
// ステータスバーの設定用関数
//-----------------------------------------------
void Monster::StatusBarInit()
{
	// HPの設定
	m_hp.Set({ 25,25 }, { 1200, 25 }, &m_hp_value, true);
	m_hp.SetColor(255, 100, 50, &m_hp.m_color);
	m_hp.SetColor(128, 128, 128, &m_hp.m_back_color);
	m_hp.SetColor(0, 0, 0, &m_hp.m_line_color);
	m_hp.SetColor(255, 255, 255, &m_hp.m_character_color);
	m_hp.SetName("HP");
}

//-----------------------------------------------
// ステータスバー描画用関数
//-----------------------------------------------
void Monster::StatusBarDraw()
{
	// HPの値が減ったかどうか
	m_hp.Update(m_hp_value);
	//===================
	// UIの描画
	//===================
	m_hp.Draw();
}

//-----------------------------------------------
// アニメーションの初期処理
//-----------------------------------------------
void Monster::Anima_Load_Init()
{
	// アニメーションの初期設定
	m_animation.InitAnimation(anim_max, idle);
	// アニメーションの読み込み
	m_animation.LoadAnimation("Data/Model/Monster/Animation/idle.mv1", idle, 0, 1.0f); //!< アイドル
	m_animation.LoadAnimation("Data/Model/Monster/Animation/Run.mv1", run, 0, 1.0f); //!< ラン

	// もっとモンスターっぽい攻撃を探してこい

	m_animation.LoadAnimation("Data/Model/Monster/Animation/Punch_1.mv1", attack_1, 0, 1.0f); //!< 攻撃１
	m_animation.LoadAnimation("Data/Model/Monster/Animation/rolling.mv1", rolling, 0, 1.0f); //!< ローリング
	m_animation.LoadAnimation("Data/Model/Monster/Animation/jump.mv1", jump, 0, 1.0f); //!< ジャンプ
	// 最初はデフォルトアニメーションをつけておく
	m_animation.InitAttachAnimation(&m_model, idle, true);
}

//-----------------------------------------------
// プレイヤーの移動用関数
//-----------------------------------------------
void Monster::Move_Update()
{
	// 毎回リセット
	m_run_flag = false;

	// 移動前の座標一旦保存しておく
	m_before_pos = m_transform.pos;

	// ベースクラスの更新処理
	// 移動の処理が中に入っている
	MoveUpdate(&m_run_flag);

	// run_flag が上がってるときかつ
	// プレイヤーモードがRUN以外の時
	if (m_run_flag && m_monster_mode != RUN)
	{
		// アニメーションの切り替えフラグを上げる
		m_animation.m_anim_change_flag = true;
	}

	// アニメーション変更が可能な時に
	if (m_animation.ChangeFlag(m_run_flag)) {
		// 走りアニメーションに変更
		m_animation.ChangeAnimation(&m_model, run, true);
		// アニメーションが変わったから
		// プレイヤーモードの切り替えをする
		m_monster_mode = RUN;
	}
}

//-----------------------------------------------
// 最初の攻撃を判断する
//-----------------------------------------------
void Monster::Attack_First()
{

	// attack_flag が上がってるときかつ
	// プレイヤーモードがATTACK以外の時
	if (m_attack_flag && m_monster_mode != ATTACK)
	{
		// アニメーションの切り替えフラグを上げる
		m_animation.m_anim_change_flag = true;
	}

	// 攻撃モードにしておく
	m_monster_mode = ATTACK;
	m_animation.ChangeAnimation(&m_model, attack_1, false);

	// 攻撃アニメーション番号の保存
	m_now_attack_anim = attack_1;
	// 現在の攻撃番号を保存する
	m_now_attack = m_now_attack_anim - ATTACK_ANIM_START;

	m_stop_combo_flag = true;
}

//-----------------------------------------------
// 攻撃に関する更新処理
//-----------------------------------------------
void Monster::Attack_Update()
{
	// コンボをしていいフラグがったている時だけ
	if (m_stop_combo_flag)
	{
		// コンボ関数を呼ぶ
		Combo_Update();
	}
}

//-----------------------------------------------
// ジャンプ攻撃に関する処理
//-----------------------------------------------
void Monster::Attack_Jump()
{
	// ターゲットとの距離
	float distance = m_move.GetTargetDistance();
	// ターゲットとの距離が一定以上になったら
	if (TARGET_DISTANCE <= distance)
	{
		// ジャンプ攻撃をしてほしいのでランフラグを下す
		m_run_flag = false;

		// attack_flag が上がってるときかつ
	   // プレイヤーモードがATTACK以外の時
		if (m_attack_flag && m_monster_mode != ATTACK)
		{
			// アニメーションの切り替えフラグを上げる
			m_animation.m_anim_change_flag = true;
		}
		// 攻撃モードにしておく
		m_monster_mode = ATTACK;

		m_animation.ChangeAnimation(&m_model, jump, false);
		// 攻撃アニメーション番号の保存
		m_now_attack_anim = jump;
		m_stop_combo_flag = true;
		// ジャンプ処理は
		jump_num = STANDBY;
	}
}

//-----------------------------------------------
// ジャンプ攻撃中の処理
//-----------------------------------------------
void Monster::Jump_Update()
{
	if (m_animation.m_contexts[0].play_time >= 110.0f)
	{
		// ジャンプフラグを下げる
		m_jump_flag = false; // 落ちる処理へ
	}
}

//-----------------------------------------------
// コンボの判断をする関数
//-----------------------------------------------
void Monster::Combo_Update()
{
	// コンボを行っていい状態なのはかを保存する変数
	bool combo_jug;
	// TargetMoveがターゲットと接しているそうでないかで変わる
	// 接していず移動可能状態になれば
	if (m_move.m_hit)
	{
		// コンボをできる状態でない
		combo_jug = true;
	}
	// 接していて止まっている場合
	if (!m_move.m_hit)
	{
		// コンボできる状態
		combo_jug = true;
	}

	// コンボ可能か判断用関数
	m_combo.ComboJudgmentCondition
	(
		&m_combo_flag,
		combo_jug,
		m_animation.m_contexts[0].play_time,
		m_animation.m_contexts[0].animation_total_time

	);

	// コンボフラグが上がっているとき
	if (m_combo_flag)
	{
		// 次の攻撃アニメーションをランダムでセット
		m_next_anim = Set_Rand_Attack();

		// コンボ用のアニメーションをつける
		m_animation.ActionComboChangeAnimation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// 現在の攻撃アニメーションを保存
			m_now_attack_anim = m_next_anim;
		}
	}
}


//-----------------------------------------------
// 行いたいアニメーションをランダムで選ぶための関数
//-----------------------------------------------
int Monster::Set_Rand_Attack()
{
	// 次に行ってほしいアニメーションを入れる変数
	int next_anim = 0;

	// アニメーションが決まる名で無限ループ
	while (true)
	{
		// 次のアニメーションをランダムで入れる
		// 攻撃アニメーションスタートから攻撃アニメーションの最大までで
		next_anim = GetRand(ATTACK_ANIM_MAX) + ATTACK_ANIM_START;
		// 次に行いたいアニメーションと今のアニメーションがかぶったら
		if (next_anim == m_now_attack_anim)
		{
			// またランダムで入れなおす
			next_anim = GetRand(ATTACK_ANIM_MAX) + ATTACK_ANIM_START;
		}
		break;
	}

	// 次に行ってほしい攻撃アニメーションを返す
	return next_anim;
}
