#include "Music.h"

std::wstring MusicFiles[] = {L"Music/menumusic.wav", L"Music/jump.wav", L"Music/keypickup.wav",L"Music/doors.wav"};

void playMusic(int Music)
{
	PlaySound(MusicFiles[Music].c_str(), NULL, SND_FILENAME | SND_ASYNC);
}