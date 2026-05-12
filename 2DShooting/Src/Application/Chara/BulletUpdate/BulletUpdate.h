#pragma once
#include "../CharaBase/CharaBase.h"

    void UpdateSpiral(Bullet& b);
	void UpdateConverge(Bullet& b);
	void UpdateSplit(Bullet& b, std::vector<Bullet>& newBullets);
	void UpdateLockSplit(Bullet& b, std::vector<Bullet>& newBullets);
	void UpdateMine(Bullet& b, std::vector<Bullet>& newBullets);
	void UpdateSpiralCross(Bullet& b);
	void UpdateConvergeBurst(Bullet& b, std::vector<Bullet>& newBullets);
	void UpdateRotateRing(Bullet& b);
	void UpdateBullet(Bullet& b, std::vector<Bullet>& bulletList);
	
	

