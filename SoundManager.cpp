#include "SoundManager.h"
#include <iostream>
#include "StaticUtils.h"

SoundManager::~SoundManager()
{
    m_AudioEngine->Suspend();
    m_AudioEngine.release();
}

bool SoundManager::Init()
{
    DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_EnvironmentalReverb | DirectX::AudioEngine_ReverbUseFilters;

#ifdef _DEBUG
    eflags = eflags | DirectX::AudioEngine_Debug;
#endif
    
    m_AudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
    if (!m_AudioEngine)
        return false;

    m_AudioEngine->SetReverb(DirectX::Reverb_Off);
    
    return true;
}

void SoundManager::LoadSoundEffects(std::string filename)
{
    std::vector<std::string> files = StaticUtils::GetFilesInDirectory(filename, ".wav");

    for (size_t i = 0; i < files.size(); ++i)
    {
        std::wstring clip = std::wstring(files[i].begin(), files[i].end());
        std::wstring fp = std::wstring(filename.begin(), filename.end());
        std::wstring path = fp + clip;

        auto soundEffect = std::make_unique<DirectX::SoundEffect>(m_AudioEngine.get(), path.c_str());
        if (!soundEffect)
        {
            // scuffed error logging
            OutputDebugString(L"Failed to load sound effect\n");
            OutputDebugStringW(path.c_str());
            OutputDebugString(L"\n");
            return;
        }

        std::string soundEffectName = files[i].substr(0, files[i].find_last_of("."));
        m_SoundEffects[soundEffectName] = move(soundEffect);
    }
}

void SoundManager::PlaySoundEffect(std::string name)
{
    auto soundEffect = m_SoundEffects.find(name);
    if (soundEffect == m_SoundEffects.end())
    {
        OutputDebugString(L"Sound effect not found\n");
        return;
    }

    soundEffect->second->Play();
}

void SoundManager::PlaySoundEffectInstance(std::string name, bool loop)
{
    if (!m_SoundEffects[name])
    {
        OutputDebugString(L"Sound effect not found\n");
        return;
    }

    // Check if instance already exists
    if (!m_SoundEffectInstances[name])
    {
        // Create instance if none found
        m_SoundEffectInstances[name] = m_SoundEffects[name]->CreateInstance();
        if (!m_SoundEffectInstances[name])
        {
            OutputDebugString(L"Failed to create sound effect instance\n");
            return;
        }
    }

    // Play instance
    m_SoundEffectInstances[name]->Play(loop);
}

void SoundManager::StopSoundEffectInstance(std::string name)
{
    auto soundEffectInstance = m_SoundEffectInstances.find(name);
    if (soundEffectInstance == m_SoundEffectInstances.end())
    {
        OutputDebugString(L"Sound effect instance not found\n");
        return;
    }

    soundEffectInstance->second->Stop();
}

void SoundManager::StopAllSoundEffectInstances()
{
    for (auto& soundEffectInstance : m_SoundEffectInstances)
    {
        soundEffectInstance.second->Stop();
    }
}

void SoundManager::SetListenerPosition(DirectX::XMFLOAT3 position)
{
    m_Listener.SetPosition(position);
}

void SoundManager::SetListenerOrientation(DirectX::XMFLOAT3 forward, DirectX::XMFLOAT3 up)
{
    m_Listener.SetOrientation(forward, up);
}

void SoundManager::SetListenerOrientationFromQuaternion(DirectX::SimpleMath::Quaternion orientation)
{
    m_Listener.SetOrientationFromQuaternion(orientation);
}

void SoundManager::UpdateListener(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion orientation, float deltaTime)
{
    m_Listener.Update(position, orientation, deltaTime);
}

void SoundManager::PlaySpatialSoundEffect(std::string name, DirectX::XMFLOAT3 emitterPos, bool loop)
{
    OutputDebugString(L"Playing spatial sound effect\n");


    auto sound = m_SoundEffects.find(name);
    if (sound == m_SoundEffects.end())
    {
        OutputDebugString(L"Sound effect not found\n");
        return;
    }

    std::cout << "Playing sound effect: " << name << std::endl;
    DirectX::AudioEmitter m_Emitter;
    
    m_Emitter.ChannelCount = sound->second->GetFormat()->nChannels;
    
    m_SoundEffectInstances[name] = sound->second->CreateInstance(DirectX::SoundEffectInstance_Use3D | DirectX::SoundEffectInstance_ReverbUseFilters);

    m_Emitter.SetPosition(emitterPos);
    
    m_SoundEffectInstances[name]->Play(loop);
    m_SoundEffectInstances[name]->Apply3D(m_Listener, m_Emitter);
}

void SoundManager::SetMasterVolume(float volume)
{
    m_AudioEngine->SetMasterVolume(volume);
}

void SoundManager::SetPersistentAudioVolume(float volume)
{
    for (auto& soundEffectInstance : m_SoundEffectInstances)
    {
        soundEffectInstance.second->SetVolume(volume);
    }
}

void SoundManager::PauseAll()
{
    for (auto& soundEffectInstance : m_SoundEffectInstances)
    {
        soundEffectInstance.second->Pause();
    }

    for (auto& spatialSoundEffectInstance : m_SpatialSoundEffectInstances)
    {
        spatialSoundEffectInstance.first->Pause();
    }
}

void SoundManager::ResumeAll()
{
    for (auto& soundEffectInstance : m_SoundEffectInstances)
    {
        soundEffectInstance.second->Resume();
    }

    for (auto& spatialSoundEffectInstance : m_SpatialSoundEffectInstances)
    {
        spatialSoundEffectInstance.first->Resume();
    }
}

void SoundManager::TogglePause(std::string name)
{
    auto soundEffectInstance = m_SoundEffectInstances.find(name);
    if (soundEffectInstance == m_SoundEffectInstances.end())
    {
        OutputDebugString(L"Sound effect instance not found\n");
        return;
    }

    if (soundEffectInstance->second->GetState() == DirectX::SoundState::PLAYING)
        soundEffectInstance->second->Pause();
    else
        soundEffectInstance->second->Resume();
}

void SoundManager::Update()
{
    m_AudioEngine->Update();
}

void SoundManager::Cleanup()
{
	m_AudioEngine->Suspend();
    StopAllSoundEffectInstances();
    m_SoundEffects.clear();
    m_SoundEffectInstances.clear();
}
