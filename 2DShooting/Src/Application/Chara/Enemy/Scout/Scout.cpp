#include "Scout.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../UI/Score/Score.h"
#include"../../../Item/Medkit.h"

C_Scout::C_Scout()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
}

C_Scout::~C_Scout()
{

}
void C_Scout::Init()
{
	
	m_hpMax = 1;
	m_hp = m_hpMax;

	
	m_aliveFlg = true;

	
	destructionFlg = false;

	// m_pos = { 640 + 64, float(rand() % 656 - 328) };

	m_move = { -3, 0 };

	Weaponanim = 0;
	Shieldanim = 0;
	destructionAnim = 0;
	Engineanim = 0;

	m_rect = { 0,0,64,64 };
	m_Shieldrect = { 0,0,64,64 };
	m_destructionrect = { 0,0,64,64 };
	m_enginerect = { 0,0,64,64 };

	respawnTimer = 0;

	m_radius = 64.0f;
	m_scalemat = Math::Matrix::CreateScale(2, 2, 1);
}

void C_Scout::Action()
{
	C_Player* player = m_gameScene->GetPlayer();
	// 弾発射
	if (!m_aliveFlg) return;
	if (destructionFlg) return;
	if (respawnTimer > 0) return;
	if (!player->GetAliveFlg()) return;
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
		b.move = dir * 5.0f;
		b.anim = 0;
		b.deg = DirectX::XMConvertToDegrees(atan2(dir.y, dir.x));
		b.Flg = true;
		scoutbullet.push_back(b);
		shotwait = rand()%60+30;
	}
	
}

void C_Scout::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	// 弾更新
	for (auto& b : scoutbullet)
	{
		b.pos += b.move;
		b.anim += 0.2f;
		if (b.anim > 4.0)b.anim = 0;
		b.rect = { 16 * (int)b.anim,0,16,4 };
		if (b.pos.x < -700||b.pos.x>700||b.pos.y<-360||b.pos.y>400) b.Flg = false;
	}

	scoutbullet.erase(
		std::remove_if(scoutbullet.begin(), scoutbullet.end(),
			[](const Bullet& b) { return !b.Flg; }),
		scoutbullet.end()
	);
	for (auto& b : scoutbullet)
	{
		b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
		b.rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(b.deg));
		b.scalemat = Math::Matrix::CreateScale(2, 2, 1);
		b.mat = b.scalemat * b.rotatemat * b.transmat;
	}
	//if (!m_aliveFlg && !destructionFlg)
	//{
	//	if (respawnTimer > 0)
	//	{
	//		respawnTimer--;
	//		return;
	//	}
	//	else
	//	{
	//		m_aliveFlg = true;
	//		m_hp = m_hpMax;

	//		//// ランダム位置に再出現
	//		//m_pos.x = 640 + 64;
	//		//m_pos.y = (-296 + 65) + (rand() % 296 - (-296 + 65));
	//		float spawnMinY = -360 + 65+64; // UI を除外
	//		float spawnMaxY = 360-64;

	//		float y = spawnMinY + (rand() % (int)(spawnMaxY - spawnMinY));
	//		float x = 700; // 画面右外
	//		m_pos = { x,y };

	//		ShieldTime = 0;
	//		Shieldanim = 0;
	//		Weaponanim = 0;

	//		frame = rand() % 200 + 50;
	//	}

	//}
	
	if (!m_aliveFlg)
	{
		// 破壊アニメ
		if (destructionFlg)
		{
			destructionAnim += 0.2f;
			m_destructionrect = { 0,64 * (int)destructionAnim, 64, 64 };

			if (destructionAnim > 9.0f)
			{
				destructionFlg = false;
				destructionAnim = 0;
			}
		}
		return;
	}

	if (m_aliveFlg == true)
	{
		Action();
	}
	// 移動
	m_pos += m_move;
	if (m_pos.x < -640 - 64)
	{
		m_aliveFlg = false;
		respawnTimer = rand() % 180 + 60; 
		return;
	}

	// 武器アニメ
	Weaponanim += 0.2f;
	if (Weaponanim > 6.0f) Weaponanim = 0;
	m_rect = { 0, 64 * (int)Weaponanim,64, 64 };
	
	Engineanim += 0.2f;
	if (Engineanim > 10.0f)Engineanim = 0;
	m_enginerect = { 0, 64 * (int)Engineanim, 64, 64 };

	
	float x = player->GetPos().x - m_pos.x;
	float y = player->GetPos().y - m_pos.y;
	float deg = DirectX::XMConvertToDegrees(atan2(y, x));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(deg));
	m_mat = m_scalemat * m_rotatemat * m_transmat;

	
	
}

void C_Scout::ScoutBulletHit()
{
	

	C_Player* player = m_gameScene->GetPlayer();

	for (auto& b : scoutbullet)
	{
		if (!b.Flg) continue;

		float dx = b.pos.x - player->GetPos().x;
		float dy = b.pos.y - player->GetPos().y;
		float dist = sqrtf(dx * dx + dy * dy);

		if (dist < player->GetHitRadius())
		{
			if (player->GetShieldTime()<=0)
			{
				b.Flg = false;
				player->Damage(1);
				player->SetShieldTime(180);
				break;
			}
		}
	}
}

void C_Scout::PlayerBulletHit()
{
	if (!m_aliveFlg) return;

	C_Player* player = m_gameScene->GetPlayer();
	C_Score* score = m_gameScene->GetScore();
	auto& bullets = player->GetBullets(); 

	for (auto& b : bullets)
	{
		if (!b.Flg) continue;

		float dx = b.pos.x - m_pos.x;
		float dy = b.pos.y - m_pos.y;
		float dist = sqrtf(dx * dx + dy * dy);

	

		if (dist < 40)
		{
			b.Flg = false;
			
			m_hp--;
			
			if (m_hp <= 0)
			{
				m_hp = 0;
				m_aliveFlg = false;
				destructionFlg = true;  
				destructionAnim = 0;
				int r = rand() % 100;
				if (r < 10)
				{
					m_gameScene->SpawnMedkit(m_pos);
				}
				respawnTimer = rand() % 180 + 120;
				score->Add(100);
			}

			break;
		}
	}
}


void C_Scout::Draw()
{
	// 弾描画
	for (auto& b : scoutbullet)
	{
		SHADER.m_spriteShader.SetMatrix(b.mat);
		SHADER.m_spriteShader.DrawTex(m_bulletTex, b.rect);
	}

	if (destructionFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_DestructionTex, m_destructionrect);
		return;
	}
	if (!m_aliveFlg)return;
	
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_EngineTex, m_enginerect);


	
}
