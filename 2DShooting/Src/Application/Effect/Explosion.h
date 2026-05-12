#pragma once

class C_Explosion
{
public:
    C_Explosion(Math::Vector2 pos);
    ~C_Explosion(){}
   
    void Init();
    void Update();
    void Draw();
    void SetExplosionTex(KdTexture* tex) { m_tex = tex; }
    bool GetFlg() { return Flg; }
private:
    KdTexture* m_tex;
    Math::Vector2 m_pos;
    float anim;
    bool Flg = true;
    Math::Rectangle m_rect;
    Math::Matrix m_mat;
    Math::Matrix m_scalemat;
    Math::Matrix m_transmat;
};