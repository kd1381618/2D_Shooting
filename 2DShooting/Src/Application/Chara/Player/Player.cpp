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
	m_scaleMat = Math::Matrix::CreateScale(1.5,1.5,1);
	m_EnginescaleMat = Math::Matrix::CreateScale(1.5,1.5, 1);
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
		if (shotwait == 0)
		{
			Bullet b;
			b.pos = m_pos;
			b.move = { 10,0 };
			b.Flg = true;
			playerbullet.push_back(b);
			shotwait = shotinterval;

		}
			
	}
}

void C_Player::Update()
{
	Action();
	if (m_aliveFlg)
	{
		for (auto& b : playerbullet) {
			b.pos += b.move;


			if (b.pos.x >640) {
				b.Flg = false;
			}
		}
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
			if (Shieldanim > 12.0f)
			{
				Shieldanim = 0;
			}
		}
		Baseanim = m_hpMax - m_hp;
		m_enginerect = { 48 * (int)Engineanim,0,48,48 };
		m_weaponrect = { 48 * (int)Weaponanim,0,48,48 };
		m_shieldrect = { 64 * (int)Shieldanim,0,64,64 };
		m_rect = { 48 * (int)Baseanim,0,48,48 };
	}
	Math::Matrix m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y,0);
	m_mat = m_scaleMat*m_transMat;
	Math::Matrix m_EnginetransMat = Math::Matrix::CreateTranslation(m_pos.x-10, m_pos.y, 0);
	m_EngineEffectMat = m_EnginescaleMat * m_EnginetransMat;

	for (auto& b: playerbullet) {
		b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
		b.scalemat = Math::Matrix::CreateScale(1.5, 1.5, 1);
		b.mat = b.scalemat * b.transmat;
	}
}

void C_Player::BulletHit()
{

	
}

void C_Player::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect,m_alpha);

		SHADER.m_spriteShader.SetMatrix(m_EngineEffectMat);
		SHADER.m_spriteShader.DrawTex(m_EngineTex,m_enginerect,m_alpha);

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_WeaponTex, m_weaponrect,m_alpha);

		if (ShieldTime >= 1)
		{
			if (m_hp >= 1)
			{
				SHADER.m_spriteShader.SetMatrix(m_mat);
				SHADER.m_spriteShader.DrawTex(m_ShieldTex, m_shieldrect);
			}
		}
		for (auto& b : playerbullet) {
			SHADER.m_spriteShader.SetMatrix(b.mat);
			SHADER.m_spriteShader.DrawTex(m_bulletTex, Math::Rectangle(0, 0, 32, 32));
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
}
