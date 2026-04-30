#include "Scout.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../Item/Medkit.h"

C_Scout::C_Scout()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	Init();
}

C_Scout::~C_Scout()
{

}
void C_Scout::Init()
{
	
	m_hpMax = 3;
	m_hp = m_hpMax;

	m_aliveFlg = true;

	m_pos = { 640 + 64, float(rand() % 656 - 328) };
	m_move = { -3, 0 };

	Weaponanim = 0;
	Shieldanim = 0;
	destructionAnim = 0;

	ShieldTime = 0;
	frame = rand() % 200 + 50;
	destructionFlg = false;

	m_rect = { 0,0,64,64 };
	m_Shieldrect = { 0,0,64,64 };
	m_destructionrect = { 0,0,64,64 };
	respawnTimer = rand() % 180 + 120;
	
}

void C_Scout::Action()
{
	C_Player* player = m_gameScene->GetPlayer();
	// 弾発射
	if (!m_aliveFlg) return;
	if (destructionFlg) return;
	if (respawnTimer > 0) return;
	if (shotwait > 0)
	{
		shotwait--;
	}
	else 
	{
		Bullet b;
		b.pos = m_pos;
		Math::Vector2 dir = player->GetPos() - m_pos;
		dir.Normalize();
		b.move = dir * 6.0f;
		b.deg = DirectX::XMConvertToDegrees(atan2(dir.y, dir.x));
		b.Flg = true;
		scoutbullet.push_back(b);
		shotwait = rand()%60+30;
	}
	
}

void C_Scout::Update()
{
	if (!m_aliveFlg && !destructionFlg)
	{
		if (respawnTimer > 0)
		{
			respawnTimer--;
			return;
		}
		else
		{
			m_aliveFlg = true;
			m_hp = m_hpMax;

			// ランダム位置に再出現
			m_pos.x = 640 + 64;
			m_pos.y = float(rand() % 656 - 328);

			ShieldTime = 0;
			Shieldanim = 0;
			Weaponanim = 0;

			frame = rand() % 200 + 50;
			justRespawned = true;
		}

	}
	C_Player* player = m_gameScene->GetPlayer();
	if (!m_aliveFlg)
	{
		// 破壊アニメ
		if (destructionFlg)
		{
			destructionAnim += 0.2f;
			m_destructionrect = { 64 * (int)destructionAnim, 0, 64, 64 };

			if (destructionAnim > 9.0f)
			{
				destructionFlg = false;
				destructionAnim = 0;
			}
		}
		return;
	}

	if(m_aliveFlg==true)
	{ 
	Action();
	// 移動
	m_pos += m_move;
	if (m_pos.x < -640 - 64)
	{
		m_pos.x = 640 + 64;
		m_pos.y = float(rand() % 656 - 328);
	}

	// 武器アニメ
	Weaponanim += 0.2f;
	if (Weaponanim > 6.0f) Weaponanim = 0;
	m_rect = { 64 * (int)Weaponanim, 0, 64, 64 };

	// シールド
	frame--;
	if (frame <= 0)
	{
		frame = rand() % 200 + 50;
		ShieldTime = 120;
	}

	if (ShieldTime > 0)
	{
		ShieldTime--;
		Shieldanim += 0.2f;
		if (Shieldanim > 14.0f) Shieldanim = 0;
		m_Shieldrect = { 64 * (int)Shieldanim, 0, 64, 64 };
	}

	// 弾更新
	for (auto& b : scoutbullet)
	{
		b.pos += b.move;
		if (b.pos.x < -700) b.Flg = false;
	}

	scoutbullet.erase(
		std::remove_if(scoutbullet.begin(), scoutbullet.end(),
			[](const Bullet& b) { return !b.Flg; }),
		scoutbullet.end()
	);
	}
	// 行列
	if (m_aliveFlg)
	{
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
		m_scalemat = Math::Matrix::CreateScale(2, 2, 1);
		m_mat = m_scalemat * m_rotatemat * m_transmat;

		justRespawned = false;
	}
	for (auto& b : scoutbullet)
	{
		b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
		b.rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(b.deg));
		b.scalemat = Math::Matrix::CreateScale(2, 2, 1);
		b.mat = b.scalemat *b.rotatemat* b.transmat;
	}
}

void C_Scout::ScoutBulletHit()
{
	if (!m_aliveFlg) return;

	C_Player* player = m_gameScene->GetPlayer();

	for (auto& b : scoutbullet)
	{
		if (!b.Flg) continue;

		float dx = b.pos.x - player->GetPos().x;
		float dy = b.pos.y - player->GetPos().y;
		float dist = sqrtf(dx * dx + dy * dy);

		if (dist < player->GetHitRadius())
		{
			b.Flg = false;        
			player->Damage(1);    
			break;
		}
	}
}

void C_Scout::PlayerBulletHit()
{
	if (!m_aliveFlg) return;

	C_Player* player = m_gameScene->GetPlayer();
	auto& bullets = player->GetBullets(); 

	for (auto& b : bullets)
	{
		if (!b.Flg) continue;

		float dx = b.pos.x - m_pos.x;
		float dy = b.pos.y - m_pos.y;
		float dist = sqrtf(dx * dx + dy * dy);

		const float hitRadius = 32.0f;

		if (dist < hitRadius)
		{
			b.Flg = false;

			m_hp--;

			if (m_hp <= 0)
			{
				m_hp = 0;
				m_aliveFlg = false;
				destructionFlg = true;  
				destructionAnim = 0;

				respawnTimer = rand() % 180 + 120;
			}

			break;
		}
	}
}


void C_Scout::Draw()
{
	
	if (destructionFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_DestructionTex, m_destructionrect);
	}
	if (justRespawned)return;
	if (!m_aliveFlg)return;
	
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);

	if (ShieldTime > 0)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_ShieldTex, m_Shieldrect);
	}

	// 弾描画
	for (auto& b : scoutbullet)
	{
		SHADER.m_spriteShader.SetMatrix(b.mat);
		SHADER.m_spriteShader.DrawTex(m_bulletTex, Math::Rectangle(0, 0, 16, 4));
	}
}
