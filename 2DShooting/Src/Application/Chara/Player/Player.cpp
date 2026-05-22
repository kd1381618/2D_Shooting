#include"Player.h"
#include"../../Manager/SceneManager.h"
#include"../Enemy/Scout/Scout.h"
#include"../CharaBase/CharaBase.h"

C_Player::C_Player()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	Init();
}

C_Player::~C_Player()
{
}

void C_Player::Init()
{
	m_Lv = 5;
	m_exp = 0;
	m_expMax = 10;
	m_hpMax = 4;
	m_hp = m_hpMax;
	m_pos = { -500,0 };
	m_move = { 0,0 };
	m_aliveFlg = true;
	Invincible = false;
	m_rect = { 0,0,48,48 };
	Engineanim = 0;
	ShieldTime = 0;
	Shieldanim = 0;
	Baseanim = 0;
	Weaponanim = 0;
	m_enginerect = { 0,0,48,48 };
	m_weaponrect = { 0,0,48,48 };
	m_shieldrect = { 0,0,64,64 };
	m_alpha = 1.0f;
	a_alpha = -0.1f;
	m_radius = 36.0f;
	HealFlg = false;
	Healanim = 0;
	m_scaleMat = Math::Matrix::CreateScale(1.5,1.5,1);
	m_EnginescaleMat = Math::Matrix::CreateScale(1.5,1.5, 1);
	m_WeaponscaleMat = Math::Matrix::CreateScale(1.5, 1.5, 1);
}

void C_Player::Action()
{
	if (m_aliveFlg)
	{
		if (shotwait > 0)
		{
			shotwait--;
		}
		if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_move.x = -7;
		}
		if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_move.x = 7;
		}
		if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_move.y = -7;
		}
		if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_move.y = 7;
		}
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		{
			m_move.x *= 0.5;
			m_move.y *= 0.5;
		}
		switch (m_playertype)
		{
		case PlayerType::cannon:
			if (shotwait == 0)
			{
				float baseAngle = 0;
				float interval = DirectX::XMConvertToRadians(10);
				int center = m_Lv / 2;
				for (int i = 0; i < m_Lv; i++)
				{
					float a = baseAngle + (i - center) * interval;
					Bullet b;
					b.pos = m_pos;
					b.move = { cosf(a) * 8,sinf(a) * 8 };
					b.deg = a;
					b.Flg = true;
					b.anim = 0;
					playerbullet.push_back(b);
				}
				shotwait = cannonshotinterval;

			}
			break;
		case PlayerType::spacegun:
			if (shotwait == 0)
			{
				Bullet b;
				b.pos = m_pos;
				b.move = { 10,0 };
				b.Flg = true;
				b.anim = 0;
				playerbullet.push_back(b);
				shotwait = spacegunshotinterval;
			}
				break;
		case PlayerType::rocket:
			if (shotwait == 0)
			{
				Bullet b;
				b.pos = m_pos;
				b.move = { 2,0 };
				b.speed = 5;
				b.Flg = true;
				b.anim = 0;
				playerbullet.push_back(b);
				shotwait = rocketshotinterval;
			}
			break;
		}
		
			
	}
}

void C_Player::Update()
{
	Action();
	if (m_aliveFlg)
	{
		BulletSize = m_Lv + 1;
		BulletUpdate();
		playerbullet.erase(
			std::remove_if(playerbullet.begin(), playerbullet.end(),
				[](const Bullet& b) {return !b.Flg; }),
			playerbullet.end());
		//‰æ–Ê’[
		if (m_pos.x >= 604)
		{
			m_pos.x = 604;
		}
		if (m_pos.x <= -604)
		{
			m_pos.x = -604;
		}
		if (m_pos.y >= 324)
		{
			m_pos.y = 324;
		}
		if (m_pos.y <= -324+65)
		{
			m_pos.y = -324+65;
		}
		switch (m_playertype)
		{
		case PlayerType::cannon:
			Engineanim += 0.1f;
			if (Engineanim > 4.0f)
			{
				Engineanim = 0.0f;
			}
			Weaponanim += 0.2;
			if (Weaponanim > 7.0f)
			{
				Weaponanim = 0.0f;
			}
			break;
		case PlayerType::spacegun:
			Engineanim += 0.1f;
			if (Engineanim > 4.0f)
			{
				Engineanim = 0.0f;
			}
			Weaponanim += 0.2;
			if (Weaponanim > 12.0f)
			{
				Weaponanim = 0.0f;
			}
			break;
		case PlayerType::rocket:
			Engineanim += 0.1f;
			if (Engineanim > 4.0f)
			{
				Engineanim = 0.0f;
			}
			Weaponanim += 0.2;
			if (Weaponanim > 17.0f)
			{
				Weaponanim = 0.0f;
			}
			break;
		}
		
	
		m_pos += m_move;
		m_move = { 0,0 };
		if (m_hp > 4)
		{
			m_hp = 4;
		}
	
		if (m_hp <= 0)
		{
			m_aliveFlg = false;
		}
		ShieldTime--;
		if (ShieldTime <= 0)
		{
			ShieldTime = 0;
			m_alpha = 1.0f;
			a_alpha = -0.1f;
		}
		else
		{
			m_alpha += a_alpha;
			if(m_alpha<=0.0f||m_alpha>1.0f)
			{
				a_alpha *= -1;
			}
			Shieldanim += 0.2f;
			if (Shieldanim > 10.0f)
			{
				Shieldanim = 0;
			}
		}
		Baseanim = m_hpMax - m_hp;
		if (HealFlg)
		{
			Healanim += 0.25;
			if (Healanim > 18)
			{
				Healanim = 0;
				HealFlg = false;
			}
			Healrect = { 64 * (int)Healanim,0,64,64 };
		}
		m_enginerect = { 0,48 * (int)Engineanim,48,48 };
		m_weaponrect = { 0, 48 * (int)Weaponanim,48,48 };
		m_shieldrect = { 0,64 * (int)Shieldanim,64,64 };
		m_rect = { 48 * (int)Baseanim,0,48,48 };
	}
	

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y,0);
	m_mat = m_scaleMat*transMat;
	Math::Matrix weapontransMat = Math::Matrix::CreateTranslation(m_pos.x+10, m_pos.y, 0);
	m_WeaponMat = m_WeaponscaleMat * weapontransMat;
	Math::Matrix EnginetransMat = Math::Matrix::CreateTranslation(m_pos.x-4, m_pos.y, 0);
	m_EngineEffectMat = m_EnginescaleMat * EnginetransMat;

	for (auto& b: playerbullet) {
		b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
		b.rotatemat= Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(b.deg));
		switch (m_playertype)
		{
		case PlayerType::cannon:
			b.scalemat = Math::Matrix::CreateScale(1.5, 1.5, 1);
			break;
		case PlayerType::spacegun:
			b.scalemat= Math::Matrix::CreateScale(BulletSize, BulletSize, 1);
			break;
		case PlayerType::rocket:
			b.scalemat = Math::Matrix::CreateScale(1.5, 1.5, 1);
			break;
		}
		
		b.mat = b.scalemat*b.rotatemat * b.transmat;
	}
}

void C_Player::BulletUpdate()
{

	for (auto& b : playerbullet) {
		switch (m_playertype)
		{
		case PlayerType::cannon:
			b.pos += b.move;
			if (b.pos.x > 640) {
				b.Flg = false;
			}
			b.anim += 0.2;
			if (b.anim > 4)b.anim = 0;
			break;
		case PlayerType::spacegun:
			b.pos += b.move;
			if (b.pos.x > 640) {
				b.Flg = false;
			}
			b.anim += 0.2;
			if (b.anim > 10)b.anim = 0;
			break;
		case PlayerType::rocket:
			b.anim += 0.2;
			if (b.anim > 3)b.anim = 0;
			C_CharaBase* target = m_gameScene->FindNearestEnemy(b.pos);

			if (!target)
			{
				b.pos += b.move * b.speed;
				break;
			}
			if (b.pos.x > 640) {
				b.Flg = false;
			}
			Math::Vector2 dir = target->GetPos() - b.pos;
			float targetAngle = atan2f(dir.y, dir.x);
			float currentAngle = atan2f(b.move.y, b.move.x);

			float diff = targetAngle - currentAngle;
			const float PI = 3.14f;

			if (diff > PI) diff -= PI * 2;
			if (diff < -PI) diff += PI * 2;

			currentAngle += diff * b.turnSpeed;

			b.move = { cosf(currentAngle), sinf(currentAngle) };
			b.pos += b.move * b.speed;
			break;
		}
		b.rect = { 0,32 * (int)b.anim,32,32 };

	}
}


void C_Player::Draw()
{
	if (m_aliveFlg)
	{
		switch (m_playertype)
		{
		case PlayerType::cannon:
			SHADER.m_spriteShader.SetMatrix(m_WeaponMat);
			SHADER.m_spriteShader.DrawTex(m_WeaponTex, m_weaponrect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_EngineEffectMat);
			SHADER.m_spriteShader.DrawTex(m_EngineTex, m_enginerect, m_alpha);
			break;
		case PlayerType::spacegun:
			SHADER.m_spriteShader.SetMatrix(m_WeaponMat);
			SHADER.m_spriteShader.DrawTex(m_spacegunWeaponTex, m_weaponrect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(m_spacegunBaseTex, m_rect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_EngineEffectMat);
			SHADER.m_spriteShader.DrawTex(m_spacegunEffectTex, m_enginerect, m_alpha);
			break;
		case PlayerType::rocket:
			SHADER.m_spriteShader.SetMatrix(m_WeaponMat);
			SHADER.m_spriteShader.DrawTex(m_rocketWeaponTex, m_weaponrect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(m_rocketBaseTex, m_rect, m_alpha);

			SHADER.m_spriteShader.SetMatrix(m_EngineEffectMat);
			SHADER.m_spriteShader.DrawTex(m_rocketEffectTex, m_enginerect, m_alpha);
			break;
		}
		
		if (HealFlg)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(m_HealTex, Healrect);
		}
		

		if (ShieldTime >= 1)
		{
			if (m_hp >= 1)
			{
				SHADER.m_spriteShader.SetMatrix(m_mat);
				SHADER.m_spriteShader.DrawTex(m_ShieldTex, m_shieldrect);
			}
		}
		for (auto& b : playerbullet) {
			switch (m_playertype)
			{
			case PlayerType::cannon:
				SHADER.m_spriteShader.SetMatrix(b.mat);
				SHADER.m_spriteShader.DrawTex(m_bulletTex, b.rect);
				break;
			case PlayerType::spacegun:
				SHADER.m_spriteShader.SetMatrix(b.mat);
				SHADER.m_spriteShader.DrawTex(m_spacegunTex, b.rect);
				break;
			case PlayerType::rocket:
				SHADER.m_spriteShader.SetMatrix(b.mat);
				SHADER.m_spriteShader.DrawTex(m_rocketTex, b.rect);
				break;
			}
			
		}
	}
}

void C_Player::Damage(int amount)
{
	if (!m_aliveFlg) return;

	m_hp -= amount;

	if (m_hp <= 0)
	{
		if (Invincible)
		{
			m_hp = 1;
		}
		else
		{
			m_hp = 0;
			m_aliveFlg = false;
		}
	}
}

void C_Player::Heal(int heal)
{
	if (!m_aliveFlg)return;

	m_hp += heal;
	if (m_hp >= 4)
	{
		m_hp = 4;
	}
	HealFlg = true;
	Healanim = 0;
}

void C_Player::Exp(int exp)
{
	if (!m_aliveFlg)return;

	m_exp += exp;
	if (m_exp >= m_expMax)
	{
		m_Lv++;
		m_exp = 0;
		m_expMax *= 2;
	}
}
