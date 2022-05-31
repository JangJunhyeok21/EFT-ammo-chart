#ifndef STRUCT_H
#define STRUCT_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable:4996)
#define LINES 40

typedef struct ammunition {
	char* caliber;
	char* name;
	unsigned short damage;
	unsigned short penetrationPower;
	unsigned short armorDamage;
	unsigned short accuracy;
	unsigned short recoil;
	unsigned short bleedLow;
	unsigned short bleedHigh;
}AMMO;

typedef struct AmmoNode
{
	AMMO ammo;
	struct AmmoNode* pNext;
}ANode;

typedef struct ballistic {
	char* caliber;
	char* name;
	short distanceUnit;
	float drop[10];
}BLSTC;

typedef struct BlstcNode
{
	BLSTC blstc;
	struct AmmoNode* pNext;
}BNode;

#endif
