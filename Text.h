#pragma once
#include <SimpleMath.h>
#include <string>

class Text
{
private:
    DirectX::SimpleMath::Vector2 m_Position = DirectX::SimpleMath::Vector2::Zero;
    std::wstring m_Text = L"";
    bool m_Visible = true;
    
public:
    Text();
    Text(DirectX::SimpleMath::Vector2 position, std::wstring text);
    ~Text() = default;

    DirectX::SimpleMath::Vector2 GetPosition() { return m_Position; }
    std::wstring GetText() { return m_Text; }

    void SetPosition(DirectX::SimpleMath::Vector2 position);
    void SetText(std::wstring text);
    void ToggleVisibility();

    bool IsVisible() { return m_Visible; }
    
};
