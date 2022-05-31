#include "struct.h"
extern char CaliberList[22][18];
extern char CaliberList4ball[19][12];

int main()
{
	system("mode con cols=150 lines=45");
	int menu, CaliberNum;
	char caliber[50];
	init();
	while (1)
	{
		Menu();
		printf("선택하시오>> ");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1: DisplayAmmoData();		break;
		case 2:
		regetB:
			system("cls");
			printf("어느 구경에 대해 출력할까요?\n");
			Caliber4ball();
			scanf(" %d", &CaliberNum);
			if (CaliberNum > 18)	goto regetB;
			DisplayBallData(CaliberList4ball[CaliberNum]);			
			break;
	
		case 3:
		regetA:
			system("cls");
			printf("어느 구경에 대해 출력할까요?\n");
			Caliber();
			scanf(" %d", &CaliberNum);
			if (CaliberNum > 21)	goto regetA;
			DisplayCaliberData(CaliberList[CaliberNum]);
			break;

		case 4:
			DeleteAllData();
			exit(0);
			break;
		}
	}
}