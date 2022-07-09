#include<stdio.h>
#include <stdlib.h>
#include"FO.h"

int main() {
	char fileName[10];
	int i, mis;
	DataNode data;
	do {
		printf("\n 1.Insert");
		printf("\n 2.Search");
		printf("\n 3.Delete");
		printf("\n 4.Display");
		printf("\n 5.Display Stream Wise");
		printf("\n 6.Exit");
		printf("\n Select Choice : ");
		scanf("%d", &i);

		switch(i) {
			case 1:
				printf("\n Enter The File Name : ");
				scanf("%s", fileName);

				printf("\n Enter The Name : ");
				scanf("%s", data.name);

				printf("\n Enter The MIS : ");
				scanf("%d", &data.mis);

				printf("\n Enter The Stream : ");
				scanf("%s", data.stream);

				printf("\n Enter The CGPA : ");
				scanf("%lf", &data.cgpa);


				InsertRecord(fileName, data);
				break;
			case 2:
				printf("\n Enter The File Name : ");
				scanf("%s", fileName);

				printf("\n Enter the MIS : ");
				scanf("%d", &mis);

				Search(fileName, mis);
				break;
			case 3:
				printf("\n Enter The File Name : ");
				scanf("%s", fileName);

				printf("\n Enter the MIS : ");
				scanf("%d", &mis);

				Delete(fileName, mis);
				break;
			case 4:
				printf("\n Enter The File Name : ");
				scanf("%s", fileName);

				Display(fileName);
				break;
			case 5:
				printf("\n Enter The File Name : ");
				scanf("%s", fileName);

				DisplayStreamWise(fileName);
				break;
			case 6:
				break;
		}
		
	} while (i != 6);
	return 0;
}
