#include "Text.h"

Text::Text()
{
    m_Position = DirectX::SimpleMath::Vector2::Zero;
    m_Text = L"";
}

Text::Text(DirectX::SimpleMath::Vector2 position, std::wstring text)
{
    m_Position = position;
    m_Text = text;
}

void Text::SetPosition(DirectX::SimpleMath::Vector2 position)
{
    m_Position = position;
}

void Text::SetText(std::wstring text)
{
    m_Text = text;
}

void Text::ToggleVisibility()
{
    m_Visible = !m_Visible;
}
