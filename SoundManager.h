#pragma once

#include <Audio.h>
#include <map>
#include <string>
#include <memory>
#include <SimpleMath.h>

class SoundManager
{
private:
	SoundManager() = default;
	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(const SoundManager& other) = delete;

	std::unique_ptr<DirectX::AudioEngine> m_AudioEngine;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>> m_SoundEffects;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffectInstance>> m_SoundEffectInstances;
	std::map<std::unique_ptr<DirectX::SoundEffectInstance>, DirectX::AudioEmitter*> m_SpatialSoundEffectInstances;

	DirectX::AudioListener m_Listener;
public:
	static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}

	~SoundManager();

	bool Init();

	void LoadSoundEffects(std::string filename);

	// One shot audio
	void PlaySoundEffect(std::string name);

	// Continuous audio
	void PlaySoundEffectInstance(std::string name, bool loop);
	void StopSoundEffectInstance(std::string name);
	void StopAllSoundEffectInstances();

	// Spatial Audio
	void SetListenerPosition(DirectX::XMFLOAT3 position);
	void SetListenerOrientation(DirectX::XMFLOAT3 forward, DirectX::XMFLOAT3 up);
	void SetListenerOrientationFromQuaternion(DirectX::SimpleMath::Quaternion orientation);
	void UpdateListener(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion orientation, float deltaTime);
	void PlaySpatialSoundEffect(std::string name, DirectX::XMFLOAT3 emitterPos, bool loop);

	// Volume controls
	void SetMasterVolume(float volume);
	void SetPersistentAudioVolume(float volume);

	// Play/pause
	void PauseAll();
	void ResumeAll();

	void TogglePause(std::string name);

	// Update and Cleanup
	void Update();
	void Cleanup();

};

