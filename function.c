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

/*	ź�� ��带 ���� ����Ʈ�� �߰��ϴ� �Լ�	*/
void AddANode(AMMO _AMMO)
{
	//	�Ʒ��� ��带 �ϳ� ����.
	ANode* NewANode = (ANode*)malloc(sizeof(ANode));
	NewANode->ammo = _AMMO;
	NewANode->pNext = NULL;

	if (AHead == NULL)		AHead = NewANode;
	else					ATail->pNext = NewANode;

	ATail = NewANode;
}
/*	ź���� ��带 ���� ����Ʈ�� �߰��ϴ� �Լ�	*/
void AddBNode(BLSTC _AMMO)
{
	//	�Ʒ��� ��带 �ϳ� ����.
	BNode* NewBNode = (BNode*)malloc(sizeof(BNode));
	NewBNode->blstc = _AMMO;
	NewBNode->pNext = NULL;

	if (BHead == NULL)		BHead = NewBNode;
	else					BTail->pNext = NewBNode;

	BTail = NewBNode;
}

//���Ͽ��� ���� �ҷ��� ����ü�� �����ϴ� �Լ�
void init() {
	FILE* aFile = fopen("AmmunitionDB.txt", "r");	//	txt ���Ϸκ��� ź�������� �о���ڴٴ� �ǹ�.
	FILE* bFile = fopen("BallisticDB.txt", "r");	//	txt ���Ϸκ��� ź���������� �о���ڴٴ� �ǹ�.
	AMMO ammo;								//	ź�������� �޾ƿ��� ���ؼ�.
	BLSTC ball;
	char TempBuffer[50] = { 0 };				//	ź���̸��� �ӽ÷� �����ϱ� ���� �뵵.
	int NameLength;

	//	������ ���� �����ߴٰ��ϸ�, feof�Լ��� 1���� ��ȯ. 
	//	1�� ���ö����� ������ �о�鿩�� �ϹǷ�.
	while (!feof(aFile))
	{
		//	1. ź���� ������ ����
		fscanf(aFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);					//	�̸� ���ڿ��� ���� ����.
		ammo.caliber = (char*)malloc(NameLength + 1);	//	NULL���ڰ� �߰��� �ʿ��ϹǷ� + 1�� �� ������ŭ �����Ҵ�. 
		strcpy(ammo.caliber, TempBuffer);				//	TempBuffer�� �ִ� �̸��� ����ü ������ ����.

		//	2. ź���� �̸��� ����.
		fscanf(aFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);					//	�̸� ���ڿ��� ���� ����.
		ammo.name = (char*)malloc(NameLength + 1);	//	NULL���ڰ� �߰��� �ʿ��ϹǷ� + 1�� �� ������ŭ �����Ҵ�. 
		strcpy(ammo.name, TempBuffer);				//	TempBuffer�� �ִ� �̸��� ����ü ������ ����.

		//	3. �������� ����.
		fscanf(aFile, " %hd ", &ammo.damage);
		//	4. ������� ����.
		fscanf(aFile, " %hd ", &ammo.penetrationPower);
		//	5. �Ƹ� �������� ����.
		fscanf(aFile, " %hd ", &ammo.armorDamage);
		//	6. ��Ȯ�� ������ ����.
		fscanf(aFile, " %hd ", &ammo.accuracy);
		//	7. �ݵ� ������ ����.
		fscanf(aFile, " %hd ", &ammo.recoil);
		//	8. ����Ȯ���� ����.
		fscanf(aFile, " %hd ", &ammo.bleedLow);
		//	9. ��������Ȯ���� ����.
		fscanf(aFile, " %hd ", &ammo.bleedHigh);

		AddANode(ammo);
		memset(TempBuffer, 0, sizeof(TempBuffer));
	}
	while (!feof(bFile))
	{
		//	1. ź���� ������ ����
		fscanf(bFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);				//	���� ���ڿ��� ���� ����.
		ball.caliber = (char*)malloc(NameLength + 1);	//	NULL���ڰ� �߰��� �ʿ��ϹǷ� + 1�� �� ������ŭ �����Ҵ�. 
		strcpy(ball.caliber, TempBuffer);				//	TempBuffer�� �ִ� �̸��� ����ü ������ ����.

		//	2. ź���� �̸��� ����.
		fscanf(bFile, " %s", TempBuffer);
		NameLength = strlen(TempBuffer);			//	�̸� ���ڿ��� ���� ����.
		ball.name = (char*)malloc(NameLength + 1);	//	NULL���ڰ� �߰��� �ʿ��ϹǷ� + 1�� �� ������ŭ �����Ҵ�. 
		strcpy(ball.name, TempBuffer);				//	TempBuffer�� �ִ� �̸��� ����ü ������ ����.

		//	3. �Ÿ� ������ ����.
		fscanf(bFile, " %hd", &ball.distanceUnit);	//	�Ÿ� ���� ����

		//	4. �Ÿ��� ������ ����.
		for (int i = 0; i < 10; i++) {
			fscanf(bFile, " %f", &ball.drop[i]);	// �Ÿ��� ������ �迭�� ����
		}

		AddBNode(ball);
		memset(TempBuffer, 0, sizeof(TempBuffer));
	}
	fclose(aFile);
	fclose(bFile);
}

/*	��忡 �ִ� ������ ����ϴ� �Լ�	*/
void DisplayAmmo(AMMO* pAmmo)
{
	printf("%20s | %28s | %8hd | %8hd | %11hd | %8hd | %8hd | %8hd | %9hd |\n",
		pAmmo->caliber, pAmmo->name, pAmmo->damage, pAmmo->penetrationPower, pAmmo->armorDamage,
		pAmmo->accuracy, pAmmo->recoil, pAmmo->bleedLow, pAmmo->bleedHigh);
}
/*	��忡 �ִ� ������ ����ϴ� �Լ�	*/
void DisplayBlstc(BLSTC* pAmmo)
{
	printf("%16s | %14s |", pAmmo->caliber, pAmmo->name);
	for (int i = 0; i < 10; i++)	printf(" %8.2f |", pAmmo->drop[i]);
	printf("\n");
}

void AmmoIndex() {
	system("cls");
	printf("\n%20s | %28s | %8s | %8s | %11s | %8s | %8s | %8s | %9s |\n", "����", "ź��", "���ط� ", "����� ", "�� ����", "���߷�%", "�ݵ�%", "����%", "��������%");
}

void BallIndex(BLSTC* pAmmo) {
	printf("\n%16s | %14s ", "����", "ź��");
	for (int i = 0; i < 10; i++) {
		printf("| %7hdm ", (i + 1) * pAmmo->distanceUnit);
	}
	printf("|\n");
}

//	���� ����Ʈ�� �ִ� ź�� �����͵��� ��� ���
void DisplayAmmoData()
{
	ANode* pCur = AHead;

	if (AHead == NULL)
	{
		printf("�����Ͱ� ����\n");
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
//	Ư�� ���� ź���� �����͸� ���
void DisplayBallData(char* caliber)
{
	short oldUnit = 0;
	BNode* pCur = BHead;

	if (pCur == NULL)
	{
		printf("�����Ͱ� ����\n");
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

//Ư�� ���� ź��ǥ ���
void DisplayCaliberData(char* caliber)
{
	ANode* pCur = AHead;

	if (AHead == NULL)
	{
		printf("�����Ͱ� ����\n");
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

/*	�޴� ����� �����ִ� �Լ�	*/
void Menu()
{
	system("cls");
	printf("\n\n\n");
	printf("1, ��ü ź�� ������ ���\n");
	printf("2, ź���� ������ ���\n");
	printf("3, Ư�� ���� ������ ���\n");
	printf("4, ����\n");
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

//	��忡 �ִ� ������ ����
void DeleteInfo(AMMO* pAmmo)
{
	if (pAmmo->name != NULL)
		free(pAmmo->name);
	if (pAmmo->caliber != NULL)
		free(pAmmo->caliber);
}

//	���� ����Ʈ�� ������ ��� ����
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