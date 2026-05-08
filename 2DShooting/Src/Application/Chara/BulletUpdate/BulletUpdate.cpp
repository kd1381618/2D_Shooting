#include "BulletUpdate.h"
#include"../../Manager/SceneManager.h"
#include"../Player/Player.h"
void UpdateConverge(Bullet& b)
{
    b.timer++;

    if (!b.converge)
    {
        // 広がる
        b.pos += b.move;

        if (b.timer > 60)
        {
            b.converge = true;
            C_GameScene* m_gameScene=static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
            C_Player* player = m_gameScene->GetPlayer();
            b.target = player->GetPos();
            Math::Vector2 dir = b.target - b.pos;
            float angle = atan2f(dir.y, dir.x);

            b.move.x = cosf(angle) * 10.0f;
            b.move.y = sinf(angle) * 10.0f;
        }
    }
    else
    {
        // 収束
        b.pos += b.move;
    }
}

void UpdateSplit(Bullet& b, std::vector<Bullet>& bulletList)
{
    b.timer++;
    b.pos += b.move;
    if (!b.split && b.timer > 40)
    {
        b.split = true;

        float baseAngle = atan2f(b.move.y, b.move.x);

        // 分裂角度のリスト（5WAY）
        float angles[] = {
            baseAngle,
            baseAngle + DirectX::XMConvertToRadians(15),
            baseAngle - DirectX::XMConvertToRadians(15),
            baseAngle + DirectX::XMConvertToRadians(30),
            baseAngle - DirectX::XMConvertToRadians(30),
        };
        for (float a : angles)
        {
            Bullet c = b;
            c.move = { cosf(a) * 8, sinf(a) * 8 };
            c.timer = 0;
            c.split = true; // 子弾は分裂しない
            c.color = { 0,1,1,1 };
            bulletList.push_back(c);
        }

        b.Flg = false; // 元弾消す
    }
}

void UpdateMine(Bullet& b, std::vector<Bullet>& bulletList)
{
    b.timer++;

    // ① 前進フェーズ
    if (b.timer < 30)
    {
        b.pos += b.move;
        return;
    }

    // ② 停止フェーズ
    if (b.timer < 60)
    {
        return;
    }

    // ③ 爆発フェーズ（1回だけ）
    if (b.timer == 90)
    {
        float baseAngle = 0;
        float interval = DirectX::XMConvertToRadians(30); 

        for (int i = 0; i < 12; i++)
        {
            float a = baseAngle + interval * i;

            Bullet c = b;
            c.type = Bullet::Split;
            c.move = { cosf(a) * 6, sinf(a) * 6 }; 
            c.timer = 0;
            c.color = { 1, 0, 1, 1 }; 

            bulletList.push_back(c);
        }

        // 元の地雷弾は消す
        b.Flg = false;
    }
}



void UpdateBullet(Bullet& b, std::vector<Bullet>& bulletList)
{
    if (!b.Flg) return;

    switch (b.type)
    {
    case Bullet::Converge:
        UpdateConverge(b);
        break;
    case Bullet::Split:
        UpdateSplit(b, bulletList);
        break;
    case Bullet::Mine:
        UpdateMine(b, bulletList);
        break;
    }
}


