#include "struct.h"

ANode* AHead = NULL;
ANode* ATail = NULL;
BNode* BHead = NULL;
BNode* BTail = NULL;

char CaliberList[22][18] = { "caliber","12/70","20/70","23x75mm","9x18mm","7.62x25mm","9x19mm",".357_Magnum",
".45_ACP","9x21mm","5.7x28mm","4.6x30mm",".366_TKM","5.45x39mm","5.56x45mm",".300","7.62x39mm","7.62x51mm",
"7.62x54mm_R",".338_Lapua_Magnum","12.7x55mm","9x39mm" };
char CaliberList4ball[19][12] = { "caliber","12/70","20/70","23x75mm","9x18mm","7.62x25mm","9x19mm",
".45_ACP","9x21mm","5.7x28mm","4.6x30mm",".366_TKM","5.45x39mm","5.56x45mm","7.62x39mm","7.62x51mm",
"7.62x54mm_R","12.7x55mm","9x39mm" };

/*	탄약 노드를 연결 리스트에 추가하는 함수	*/
void AddANode(AMMO _AMMO)
{
	//	아래는 노드를 하나 생성.
	ANode* NewANode = (ANode*)malloc(sizeof(ANode));
	NewANode->ammo = _AMMO;
	NewANode->pNext = NULL;

	if (AHead == NULL)		AHead = NewANode;
	else					ATail->pNext = NewANode;

	ATail = NewANode;
}
/*	탄도학 노드를 연결 리스트에 추가하는 함수	*/
void AddBNode(BLSTC _AMMO)
{
	//	아래는 노드를 하나 생성.
	BNode* NewBNode = (BNode*)malloc(sizeof(BNode));
	NewBNode->blstc = _AMMO;
	NewBNode->pNext = NULL;

	if (BHead == NULL)		BHead = NewBNode;
	else					BTail->pNext = NewBNode;

	BTail = NewBNode;
}

//파일에서 값을 불러와 구조체에 저장하는 함수
void init() {
	FILE* aFile = fopen("AmmunitionDB.txt", "r");	//	txt 파일로부터 탄약정보를 읽어오겠다는 의미.
	FILE* bFile = fopen("BallisticDB.txt", "r");	//	txt 파일로부터 탄도학정보를 읽어오겠다는 의미.
	AMMO ammo;								//	탄약정보를 받아오기 위해서.
	BLSTC ball;
	char TempBuffer[50] = { 0 };				//	탄약이름을 임시로 저장하기 위한 용도.
	int NameLength;

	//	파일의 끝에 도달했다고하면, feof함수는 1값을 반환. 
	//	1이 나올때까지 파일을 읽어들여야 하므로.
	while (!feof(aFile))
	{
		//	1. 탄약의 구경을 저장
		fscanf(aFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);					//	이름 문자열의 갯수 저장.
		ammo.caliber = (char*)malloc(NameLength + 1);	//	NULL문자가 추가로 필요하므로 + 1을 한 갯수만큼 동적할당. 
		strcpy(ammo.caliber, TempBuffer);				//	TempBuffer에 있는 이름을 구조체 변수에 저장.

		//	2. 탄약의 이름을 저장.
		fscanf(aFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);					//	이름 문자열의 갯수 저장.
		ammo.name = (char*)malloc(NameLength + 1);	//	NULL문자가 추가로 필요하므로 + 1을 한 갯수만큼 동적할당. 
		strcpy(ammo.name, TempBuffer);				//	TempBuffer에 있는 이름을 구조체 변수에 저장.

		//	3. 데미지를 저장.
		fscanf(aFile, " %hd ", &ammo.damage);
		//	4. 관통력을 저장.
		fscanf(aFile, " %hd ", &ammo.penetrationPower);
		//	5. 아머 데미지를 저장.
		fscanf(aFile, " %hd ", &ammo.armorDamage);
		//	6. 정확도 보정을 저장.
		fscanf(aFile, " %hd ", &ammo.accuracy);
		//	7. 반동 보정을 저장.
		fscanf(aFile, " %hd ", &ammo.recoil);
		//	8. 출혈확률을 저장.
		fscanf(aFile, " %hd ", &ammo.bleedLow);
		//	9. 과다출혈확률을 저장.
		fscanf(aFile, " %hd ", &ammo.bleedHigh);

		AddANode(ammo);
		memset(TempBuffer, 0, sizeof(TempBuffer));
	}
	while (!feof(bFile))
	{
		//	1. 탄약의 구경을 저장
		fscanf(bFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);				//	구경 문자열의 길이 저장.
		ball.caliber = (char*)malloc(NameLength + 1);	//	NULL문자가 추가로 필요하므로 + 1을 한 갯수만큼 동적할당. 
		strcpy(ball.caliber, TempBuffer);				//	TempBuffer에 있는 이름을 구조체 변수에 저장.

		//	2. 탄약의 이름을 저장.
		fscanf(bFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);			//	이름 문자열의 길이 저장.
		ball.name = (char*)malloc(NameLength + 1);	//	NULL문자가 추가로 필요하므로 + 1을 한 갯수만큼 동적할당. 
		strcpy(ball.name, TempBuffer);				//	TempBuffer에 있는 이름을 구조체 변수에 저장.

		//	3. 거리 단위를 저장.
		fscanf(bFile, " %hd", &ball.distanceUnit);	//	거리 단위 저장

		//	4. 거리별 낙차를 저장.
		for (int i = 0; i < 10; i++) {
			fscanf(bFile, " %f", &ball.drop[i]);	// 거리별 낙차를 배열에 저장
		}

		AddBNode(ball);
		memset(TempBuffer, 0, sizeof(TempBuffer));
	}
	fclose(aFile);
	fclose(bFile);
}

/*	노드에 있는 정보를 출력하는 함수	*/
void DisplayAmmo(AMMO* pAmmo)
{
	printf("%20s | %28s | %8hd | %8hd | %11hd | %8hd | %8hd | %8hd | %9hd |\n",
		pAmmo->caliber, pAmmo->name, pAmmo->damage, pAmmo->penetrationPower, pAmmo->armorDamage,
		pAmmo->accuracy, pAmmo->recoil, pAmmo->bleedLow, pAmmo->bleedHigh);
}
/*	노드에 있는 정보를 출력하는 함수	*/
void DisplayBlstc(BLSTC* pAmmo)
{
	printf("%16s | %14s |", pAmmo->caliber, pAmmo->name);
	for (int i = 0; i < 10; i++)	printf(" %8.2f |", pAmmo->drop[i]);
	printf("\n");
}

void AmmoIndex() {
	system("cls");
	printf("\n%20s | %28s | %8s | %8s | %11s | %8s | %8s | %8s | %9s |\n", "구경", "탄명", "피해량 ", "관통력 ", "방어구 피해", "명중률%", "반동%", "출혈%", "과다출혈%");
}

void BallIndex(BLSTC* pAmmo) {
	printf("\n%16s | %14s ", "구경", "탄명");
	for (int i = 0; i < 10; i++) {
		printf("| %7hdm ", (i + 1) * pAmmo->distanceUnit);
	}
	printf("|\n");
}

//	연결 리스트에 있는 탄약 데이터들을 모두 출력
void DisplayAmmoData()
{
	ANode* pCur = AHead;

	if (AHead == NULL)
	{
		printf("데이터가 없음\n");
		return;
	}
	AmmoIndex();
	for (int i = 1; pCur != NULL; i++)
	{
		if (i % LINES == 0) {
			system("pause");
			AmmoIndex();
		}
		DisplayAmmo(&pCur->ammo);
		pCur = pCur->pNext;
	}

	system("pause");
}
//	특정 구경 탄도학 데이터를 출력
void DisplayBallData(char* caliber)
{
	short oldUnit = 0;
	BNode* pCur = BHead;

	if (pCur == NULL)
	{
		printf("데이터가 없음\n");
		return;
	}
	system("cls");
	while (pCur != NULL)
	{
		if (0 == strcmp(pCur->blstc.caliber, caliber)) {
			if (oldUnit != pCur->blstc.distanceUnit) {
				BallIndex(&pCur->blstc);
				oldUnit = pCur->blstc.distanceUnit;
			}
			DisplayBlstc(&pCur->blstc);
		}
		pCur = pCur->pNext;
	}
	system("pause");
}

//특정 구경 탄약표 출력
void DisplayCaliberData(char* caliber)
{
	ANode* pCur = AHead;

	if (AHead == NULL)
	{
		printf("데이터가 없음\n");
		return;
	}
	AmmoIndex();
	while (pCur != NULL)
	{
		if (0 == strcmp(pCur->ammo.caliber, caliber))	DisplayAmmo(&pCur->ammo);
		pCur = pCur->pNext;
	}
	system("pause");
}

/*	메뉴 목록을 보여주는 함수	*/
void Menu()
{
	system("cls");
	printf("\n\n\n");
	printf("1, 전체 탄약 데이터 출력\n");
	printf("2, 탄도학 데이터 출력\n");
	printf("3, 특정 구경 데이터 출력\n");
	printf("4, 종료\n");
}
void Caliber()
{
	for (int i = 1; i <= 21; i++)
		printf("%02d. %s\n", i, CaliberList[i]);
	printf(">> ");
}
void Caliber4ball()
{
	for (int i = 1; i <= 18; i++)
		printf("%02d. %s\n", i, CaliberList4ball[i]);
	printf(">> ");
}

//	노드에 있는 정보를 삭제
void DeleteInfo(AMMO* pAmmo)
{
	if (pAmmo->name != NULL)
		free(pAmmo->name);
	if (pAmmo->caliber != NULL)
		free(pAmmo->caliber);
}

//	연결 리스트의 정보를 모두 삭제
void DeleteAllData()
{
	ANode* aCur = AHead;
	ANode* aDel = NULL;
	BNode* bCur = BHead;
	BNode* bDel = NULL;

	if (AHead == NULL)
		return;

	while (aCur != NULL)
	{
		aDel = aCur;
		aCur = aCur->pNext;
		DeleteInfo(&(aDel->ammo));
		free(aDel);
	}
	AHead = ATail = NULL;

	if (BHead == NULL)
		return;

	while (bCur != NULL)
	{
		bDel = bCur;
		bCur = bCur->pNext;
		DeleteInfo(&(bDel->blstc));
		free(bDel);
	}

	BHead = BTail = NULL;
}