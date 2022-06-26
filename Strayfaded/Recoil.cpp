#include "include.h"

DWORD WINAPI RecoilThread(HMODULE hMod)
{
	Localplayer L;
	DWORD localplayer = L.Get();
	Vector3 OldPunch{ 0, 0, 0 };

	while (!GetAsyncKeyState(UNINJECT_KB))
	{
		if (Settings.EnableRecoilControl)
		{
			if (localplayer)
			{
				int* ShotsFired = (int*)(localplayer + m_iShotsFired);
				Vector3* RecoilPunch = (Vector3*)(localplayer + m_aimPunchAngle);
				Vector3 PunchAngle = *RecoilPunch * (Settings.EnableRecoilControlAmount * 2);

				if (*ShotsFired > 1 && GetAsyncKeyState(VK_LBUTTON))
				{
					Vector3 Angle = L.GetViewAngels() + OldPunch - PunchAngle;
					L.SetViewAngels(Angle);

				}
				OldPunch = PunchAngle;
			}
			else
			{
				localplayer = L.Get();
			}
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}