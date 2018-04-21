#pragma once
//Introduced in chapter 5
#include "hitable.h"

class hitableList : public hitable
{
public:
	hitable** l;
	int n;
	hitableList() {}
	hitableList(hitable** l, int n) : l(l), n(n) {}
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& hitrec) const
	{
		hitRecord tempRec;
		float closest = tMax;
		bool hitAnything = false;
		for (int i = 0; i < n; ++i)
		{
			if (l[i]->hit(r, tMin, closest, tempRec))
			{
				hitrec = tempRec;
				closest = hitrec.t;
				hitAnything = true;
			}
		}
		return hitAnything;
	}
};
