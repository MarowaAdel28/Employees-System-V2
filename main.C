/*

 * employee application version 2

 * using c programming [dynamic allocation,array,struct,functions,conditions]

 * features new disply exit

 * new:

 *     user can enter number of employee he want to add

 *     user can increase #employee and add more without lost data

 *     code must be unique

 *     salary must be >= 5k

 *     bonus must be >= 0

 *     reduction must be < (0.5*salary)

 * display:

 *     press next and last employee is displayed will disply first employee

 *     press prev and first employee is displayed will disply last employee

 *     press home then press disply will disply last displayed employee

 * exit: will display thanking message

*/

#include<stdio.h>

#include<stdlib.h>

#include<conio.h>

#include<string.h>

int currentEmpNo=0,currentDisplyEmpNo=0,reqEmpNo=0,empArrSize=0;

typedef struct employee
{
	int code;

	char name[50];

	float salary;

	float reduction;

	float bonus;

}emp;

emp *empArr;

void drawRect(int st_pos_x,int st_pos_y,int width,int height);

void drawText(int st_pos_x,int st_pos_y,int text_len,char text[],char clor[]);

void drawNoEmpMeg(void);

void drawFullArrMeg(void);

void setArrSize(void);

void resetArrSize(void);

void colorHomeButtons(int currentposY);

int moveCurrentPositionY(int currentposY);

void executeEnterKey(int currentposY);

void colorDisplyButtons(int positionX);

void displyNextPrevEmp(int positionX);

void drawEmpInfo(int emp_num);

void runHomePage(void);

void drawExit(void);

int isCodeUnique(int emp_num,int code);

int getUserCode(int emp_num);

float getUserSalary(void);

float getUserBonus(void);

float getUserReduction(float salary);

void addNewEmp(int emp_num);

void displayEmp(int emp_num);

void drawHomePage(void);

void drawHomeButton(void);

void drawNextButton(void);

void drawPrevButton(void);

void drawNewButton(void);

void drawDisplyButton(void);

void drawExitButton(void);

int main(void)
{
	char arrow;

	setArrSize();

	drawRect(35,13,10,3);

	gotoxy(40,14);

	drawText(35,13,10,"Enter","GREEN");

	while(1)
	{
		flushall();

		arrow=getch();

		if(arrow==13) break;

	}

	addNewEmp(currentEmpNo);

	getch();

	return 0;

}

void setArrSize(void)
{
	while(1)
	{

		system("cls");

		drawRect(5,3,70,21);

		drawText(5,4,70,"ITI System","GREEN");

		drawText(5,6,70,"please enter numbers of employees you want to enter ",

		"BLUE");

		drawRect(35,10,10,3);

		gotoxy(40,11);

		scanf("%d",&empArrSize);

		if (empArrSize>0) break;

		drawText(5,13,70,"please enter valid number of employees and greater than 0",

		"BLUE");

		drawText(5,14,70,"please press enter to continue ",

		"BLUE");

		getch();
	}

	empArr=(emp *)malloc(empArrSize*sizeof(emp));

	if(empArr==NULL)

	{
		printf("\n no space ");

		return;

	}

}

void drawHomePage(void){

	system("cls");

	//start position x, start position y, width ,height

	drawRect(20,3,40,17); // home page

	drawRect(30,7,20,3);  // new button

	drawRect(30,11,20,3); // display button

	drawRect(30,15,20,3); // exit button

	drawText(30,4,20,"ITI System","GREEN");

	drawText(30,7,20,"New","GREEN");

	drawText(30,11,20,"Display","BLUE");

	drawText(30,15,20,"Exit","BLUE");

	gotoxy(40,8); // in the middle of first rect new button

	runHomePage();

}
void runHomePage(void)
{
	int currentPosY=wherey();

	char arrow;

	while(1)

	{
		colorHomeButtons(currentPosY);

		flushall();

		arrow=getch();

		if(arrow==NULL)

			currentPosY=moveCurrentPositionY(currentPosY);

		else if (arrow ==13)
		{
			executeEnterKey(currentPosY);

			break;  //when press enter mean another page will disply so break from home page
		}
	}
}

void colorHomeButtons(int positionY)
{
	int currentPosY=positionY;

	if(currentPosY ==8) drawNewButton();

	else if (currentPosY==12) drawDisplyButton();

	else if (currentPosY==16) drawExitButton();
}

int moveCurrentPositionY(int positionY)
{
	char arrow;

	int currentPosY=positionY;

	arrow=getch();

	if(arrow==72)  //go to up
	{

		if (currentPosY==8) currentPosY=16;

		else currentPosY -=4;

	}

	else if(arrow==80) //go to down
	{
		if(currentPosY == 16) currentPosY=8;

		else currentPosY+=4;

	}
	gotoxy(wherex(),currentPosY);

	return currentPosY;
}

void executeEnterKey(int positionY)
{
	int currentPosY=positionY;

	if(currentPosY==8)   //add new employee

	{
		if(currentEmpNo==empArrSize) drawFullArrMeg();//no space to add new employee

		else addNewEmp(currentEmpNo);
	}

	else if(currentPosY==12)// display employee

	{
		reqEmpNo=currentDisplyEmpNo; //to print always last displayed employee

		displayEmp(reqEmpNo);
	}

	else if(currentPosY==16) drawExit();

}
void addNewEmp(int emp_num)
{

	struct employee e;

	char arrow;

	currentEmpNo++;

	e.code=getUserCode(emp_num);

	drawText(10,8,20,"Emplyee_Name: ","BLUE");

	gotoxy(35,9);

	flushall();

	gets(e.name);

	e.salary=getUserSalary();

	e.bonus=getUserBonus();

	e.reduction=getUserReduction(e.salary);

	gotoxy(40,21);

	drawRect(35,20,10,3);

	drawText(35,20,10,"Save","GREEN");

	while (1)
	{

		flushall();

		arrow=getch();

		if(arrow==13)
		{
			empArr[emp_num]=e; //press enter to save data

			drawHomePage();

			break;

		}
	}
}
void resetArrSize(void)
{
	int size=0;

	while(1)
	{

		drawRect(35,10,10,3);

		gotoxy(40,11);

		printf("   ");

		gotoxy(40,11);

		scanf("%d",&size);

		if(size>empArrSize) break;

		drawText(15,14,50,"must enter new size more than original size!","RED");

		drawText(15,15,50,"press enter to continue!","RED");

		flushall();

		getch();

		gotoxy(15,15);

		printf("                                                     ");

		gotoxy(15,16);

		printf("                                                     ");
	}

	empArrSize=size;

	empArr=(emp *)realloc(empArr,empArrSize*sizeof(emp));

	addNewEmp(currentEmpNo);
}
void drawFullArrMeg(void)
{

	system("cls");

	drawRect(5,5,70,15);

	drawText(5,6,70,"ITI System","GREEN");

	drawText(5,7,70,"Array is full!","RED");

	drawText(5,8,70,"please enter numbers of employees you want to add again",

	"BLUE");

	resetArrSize();
}

int isCodeUnique(int emp_num,int code)
{
	int i;

	for (i=0;i<emp_num;i++) //start from first employee to last one entered
	{
		if (code ==(empArr+i)->code ) return 1;//duplicated code so refuse it
	}
	return 0;
}

int getUserCode(int emp_num)
{

	int code;

	while (1)
	{

		system("cls");

		drawRect(5,3,70,21);

		drawText(5,4,70,"ITI System","GREEN");

		drawText(10,6,20,"Emplyee_ID: ","BLUE");

		gotoxy(35,7);

		scanf("%d",&code);

		if(isCodeUnique(emp_num,code)==0 && code>0) return code;

		drawText(15,8,50,"please enter uniqu code! To continue press enter"

		,"RED");

		getch();
	}

}

float getUserSalary()
{
	float salary;

	while(1)
	{

		drawText(10,10,20,"Employee_Salary: ","BLUE");

		gotoxy(35,11);

		printf("                ");

		gotoxy(35,11);

		scanf("%f",&salary);

		if(salary>=5000) return salary;

		drawText(15,13,50,

		"can't enter employee'salary less than 5k! To continue press enter"

		,"RED");

		getch();

		gotoxy(6,14);

		printf("                                                                   ");

	}

}

float getUserBonus()
{
	float bonus;

	while(1)
	{
		drawText(10,12,20,"Employee_Bonus: ","BLUE");

		gotoxy(35,13);

		printf("                ");

		gotoxy(35,13);

		scanf("%f",&bonus);

		if(bonus>=0) return bonus;

		drawText(15,14,50,"can't enter negative bonus! To continue press enter"

		,"RED");

		getch();

		gotoxy(6,15);

		printf("                                                                    ");
	}

}

float getUserReduction(float salary)
{

	float reduction;

	while(1)
	{

		drawText(10,15,20,"Emplyee_Reduction: ","BLUE");

		gotoxy(35,16);

		printf("                ");

		gotoxy(35,16);

		scanf("%f",&reduction);

		if(reduction>=0 && reduction<0.5*salary) return reduction;

		drawText(30,16,20,"can't enter reduction negative!"

		,"RED");

		drawText(30,17,20,"or more than the half of employee salary!","RED");

		drawText(30,18,20,"To continue press enter","RED");

		getch();

		gotoxy(6,17);

		printf("			                                            ");

		gotoxy(6,18);

		printf("                                                        ");

		gotoxy(6,19);

		printf("                                                        ");
	}


}
void drawEmpInfo(int emp_num)
{
	double netSalary;

	netSalary=(empArr+emp_num)->salary+(empArr+emp_num)->bonus

	-(empArr+emp_num)->reduction;

	system("cls");

	drawRect(10,4,60,18);

	gotoxy(40-strlen("EmployeeNo    ")/2,6);

	textcolor(GREEN);

	cprintf("EmployeeNo %d",emp_num+1);


	drawText(10,8,25,"Emplyee_Name: ","BLUE");

	gotoxy(40,9);

	textcolor(GREEN);

	cprintf("%s",(empArr+emp_num)->name);

	drawText(10,10,25,"Emplyee_ID: ","BLUE");

	gotoxy(40,11);

	textcolor(GREEN);

	cprintf("%d",(empArr+emp_num)->code);

	drawText(10,12,25,"Employee_Net_Salary: ","BLUE");

	gotoxy(40,13);

	textcolor(GREEN);

	cprintf("%f",netSalary);
}

void colorDisplyButtons(int positionX)
{

	if (positionX == 20) drawPrevButton();

	else if (positionX == 40) drawHomeButton();

	else if (positionX == 60) drawNextButton();
}

int moveCurrentPositionX(int positionX)
{
	char arrow;

	arrow=getch();

	if(arrow==77) //go to right
	{
		if(positionX !=60) positionX +=20;

		else positionX =20;

	}
	else if(arrow == 75) //go to left
	{
		if (positionX !=20) positionX -=20;

		else positionX =60;
	}

	return positionX;
}

void displyNextPrevEmp(int positionX)
{
	if(positionX == 20) //press previou button
	{

		reqEmpNo=currentDisplyEmpNo-1; // get previous employee

		if (reqEmpNo <0) reqEmpNo =currentEmpNo-1;  //get last employee

		displayEmp(reqEmpNo);

	}

	else if (positionX == 40)

	{ //press home button

		drawHomePage();
	}

	else if (positionX == 60) //press next button
	{
		reqEmpNo=currentDisplyEmpNo+1;

		if(reqEmpNo == currentEmpNo) reqEmpNo=0; //get first employee

		displayEmp(reqEmpNo);

	}

}

void displayEmp(int emp_num)
{

	int positionX;

	char arrow;

	currentDisplyEmpNo= emp_num;

	drawEmpInfo(emp_num);

	positionX=40;   //go to home button

	while(1)
	{
		colorDisplyButtons(positionX);

		flushall();

		arrow=getch();

		if(arrow==NULL) positionX=moveCurrentPositionX(positionX);

		else if (arrow ==13) //press enter
		{
			 displyNextPrevEmp(positionX);

			 break;

		}
	}
}

void drawNoEmpMeg(void)
{
	char arrow;

	system("cls");

	drawRect(10,5,60,15);

	drawText(30,6,20,"ITI System","GREEN");

	drawText(25,10,30,"must add all employees you enter their size!","RED");

	drawText(25,12,30,"Please add the rest of employees then you can disply them!","GREEN");

	drawText(25,13,30,"press enter key to back to home","");

	arrow=getch();

	if (arrow==13) return;

}

void drawHomeButton(void)
{
	drawRect(35,18,10,3);

	drawText(35,18,10,"Home","GREEN");

	drawRect(15,18,10,3);

	drawText(15,18,10,"prev","BLUE");

	drawRect(55,18,10,3);

	drawText(55,18,10,"Next","BLUE");
}
void drawNextButton(void)
{
	drawRect(35,18,10,3);

	drawText(35,18,10,"Home","BLUE");

	drawRect(15,18,10,3);

	drawText(15,18,10,"prev","BLUE");

	drawRect(55,18,10,3);

	drawText(55,18,10,"Next","GREEN");
}
void drawPrevButton(void)
{
	drawRect(35,18,10,3);

	drawText(35,18,10,"Home","BLUE");

	drawRect(15,18,10,3);

	drawText(15,18,10,"prev","GREEN");

	drawRect(55,18,10,3);

	drawText(55,18,10,"Next","BLUE");
}

void drawExit(void)
{
	system("cls");

	drawRect(20,5,40,15);

	drawRect(30,9,20,9);

	drawText(20,6,40,"ITI System","GREEN");

	drawText(30,10,20,"Thank you! ","BLUE");

	drawText(30,13,20," for your time ","BLUE");

}

void drawNewButton(void)
{
	drawText(30,7,20,"New","GREEN");

	drawText(30,11,20,"Display","BLUE");

	drawText(30,15,20,"Exit","BLUE");

}

void drawDisplyButton(void)
{
	drawText(30,7,20,"New","BLUE");

	drawText(30,11,20,"Display","GREEN");

	drawText(30,15,20,"Exit","BLUE");
}

void drawExitButton(void)
{
	drawText(30,7,20,"New","BLUE");

	drawText(30,11,20,"Display","BLUE");

	drawText(30,15,20,"Exit","GREEN");
}

void drawRect(int st_pos_x,int st_pos_y,int width,int height)
{
	int i=0,j=0,startX=st_pos_x;

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			gotoxy(st_pos_x ++,st_pos_y);


			if(i==0 || i==height-1) printf("* ");

			else if(j==0||j==width-1) printf("* ");

		}
		st_pos_y++;

		st_pos_x=startX;
	}
}

void drawText(int st_pos_x,int st_pos_y,int text_len,char text[],char clor[])
{
	int strLen=strlen(text);

	int startPosX=(text_len-strLen)/2;

	gotoxy(st_pos_x+startPosX,st_pos_y+1);


	if(strcmp(clor,"BLUE")==0) textcolor(BLUE);

	else if(strcmp(clor,"GREEN")==0) textcolor(GREEN);

	else if(strcmp(clor,"RED")==0) textcolor(RED);

	cprintf("%s",text);

}
