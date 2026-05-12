#include "BulletUpdate.h"
#include"../../Manager/SceneManager.h"
#include"../Player/Player.h"

void UpdateSpiral(Bullet& b)
{
    b.pos += b.move * b.speed;
}
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

void UpdateSplit(Bullet& b, std::vector<Bullet>& newBullets)
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
            c.split = true; 
            c.color = { 0,1,1,1 };
            newBullets.push_back(c);
        }

        b.Flg = false; // 元弾消す
    }
}

void UpdateLockSplit(Bullet& b, std::vector<Bullet>& newBullets)
{
    b.timer++;
    b.pos += b.move;
    if (!b.split && b.timer > 60)
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
            c.split = true; 
            c.color = { 0,1,1,1 };
            newBullets.push_back(c);
        }

        b.Flg = false; // 元弾消す
    }
}

void UpdateMine(Bullet& b, std::vector<Bullet>& newBullets)
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

            newBullets.push_back(c);
        }

       
        b.Flg = false;
    }
}
void UpdateSpiralCross(Bullet& b)
{
    b.pos.x += cosf(b.ang) * b.speed;
    b.pos.y += sinf(b.ang) * b.speed;
}

void UpdateConvergeBurst(Bullet& b, std::vector<Bullet>& newBullets)
{
    b.timer++;

    // 収束フェーズ
    if (b.timer < 100)
    {
        b.pos += b.move * b.speed;
        return;
    }

    // 拡散フェーズ
    if (b.timer == 100)
    {
        const float PI = 3.14f;
        for (int i = 0; i < 8; i++)
        {
            Bullet nb;
            nb.Flg = true;
            nb.type = Bullet::Spiral;  
            nb.pos = b.pos;

            float a = (PI * 2.0f / 8.0f) * i;
            nb.ang = a;
            nb.speed = 5.0f;
            nb.move = { cosf(a), sinf(a) };
            nb.timer = 0;

            newBullets.push_back(nb);
           
        }
        b.Flg = false;
        return;
    }
}

void UpdateRotateRing(Bullet& b)
{
    b.timer++;

    // 半径を広げる
    b.rad += 2.0f;

    // 全体の回転
    b.baseAngle += b.rotateSpeed;

    // 位置を計算
    float x = cosf(b.baseAngle) * b.rad;
    float y = sinf(b.baseAngle) * b.rad;

    b.pos = { b.origin.x + x, b.origin.y + y };

    if (b.rad > 1200)
        b.Flg = false;
}




void UpdateBullet(Bullet& b, std::vector<Bullet>& bulletList)
{
    if (!b.Flg) return;

    switch (b.type)
    {
    case Bullet::Spiral:
        UpdateSpiral(b);
        break;
    case Bullet::Converge:
        UpdateConverge(b);
        break;
    case Bullet::Split:
        UpdateSplit(b, bulletList);
        break;
    case Bullet::lockSplit:
        UpdateLockSplit(b, bulletList);
        break;
    case Bullet::Mine:
        UpdateMine(b, bulletList);
        break;
    case Bullet::SpiralCross:
        UpdateSpiralCross(b);
        break;
    case Bullet::ConvergeBurst:
        UpdateConvergeBurst(b, bulletList);
        break;
    case Bullet::RotateRing:
        UpdateRotateRing(b);
        break;
    }

}




