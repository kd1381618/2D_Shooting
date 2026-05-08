#pragma once

class C_Score
{
public:
   
    C_Score() {}
    ~C_Score(){}

    void Init();
    void Add(unsigned long value);
    void Update();
    void Draw();
    void SetTex(KdTexture* tex) { m_tex = tex; }
    void SetScoreTex(KdTexture* tex) { m_scoreTex = tex; }
    unsigned long GetScore() { return m_score; }

private:
    unsigned long m_score = 0;
    static const int maxDigits = 10;
    int m_digits[maxDigits] = {};
    KdTexture* m_tex;
    KdTexture* m_scoreTex;
    Math::Vector2 m_pos;
};