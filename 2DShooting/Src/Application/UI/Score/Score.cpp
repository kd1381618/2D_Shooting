#include"Score.h"

void C_Score::Init()
{
    m_pos = { 250, -328 };
}

void C_Score::Add(unsigned long score)
{
    m_score += score;
    if (m_score > 9999999999)
        m_score = 9999999999;

    Update();
}

void C_Score::Update()
{
    unsigned long tmp = m_score;
    for (int i = maxDigits - 1; i >= 0; --i)
    {
        m_digits[i] = tmp % 10;
        tmp /= 10;
    }
}

void C_Score::Draw()
{

    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    for (int i = 0; i < maxDigits; ++i)
    {
        Math::Rectangle rc = { 40 * m_digits[i], 0, 40, 40 };

        SHADER.m_spriteShader.DrawTex(
            m_tex,
            m_pos.x + (i * 40), m_pos.y,
            56, 56,
            &rc
        );
    }
    Math::Rectangle src = { 0, 0, 207, 40 };
    SHADER.m_spriteShader.DrawTex(m_scoreTex, m_pos.x-140, m_pos.y, 207, 40, &src);
}