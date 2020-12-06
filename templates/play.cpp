#include<iostream>
#include<bits/stdc++.h>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif
using namespace std;
//***************************Declared variables******************************
char name[25];
string a0;
char board[9][9];
int i,j,co,check,status=-1,f=0;
char rcount='0';
char rboard[9][9];
int row,row1,row2,column,column1,column2,x,y;
char chcontinue='y';
//****************************End of variables*******************************
//*******************************Functions***********************************


void show()
    {
    for(i=0;i<9;i++)
       {
       cout<<'\t'<<i+1;
       }
    cout<<'\n';
    for(i=0;i<9;i++)
       {
       cout<<i+1<<'\t';
       for(j=0;j<9;j++)
	  {
	   cout<<board[i][j]<<'\t';
	  }
       cout<<'\n';
       }
    }

int isvalid(int row2,int column2)
    {
    if(row2>=0&&row2<9&&column2>=0&&column2<9)
     return 1;
    else
     return 0;
    }


int ismine(int row1,int column1)
   {
    if(rboard[row1][column1]=='*')
      return 1;
    else
      return 0;
   }


char count(int row,int column)
   {
    rcount='0';
    if(isvalid(row-1,column-1)==1)
     {
      if(ismine(row-1,column-1)==1)
	rcount++;
     }
    if(isvalid(row-1,column)==1)
      {
      if(ismine(row-1,column)==1)
	rcount++;
      }
    if(isvalid(row-1,column+1)==1)
      {
      if(ismine(row-1,column+1)==1)
	rcount++;
      }
    if(isvalid(row,column-1)==1)
      {
      if(ismine(row,column-1)==1)
	rcount++;
      }
    if(isvalid(row,column+1)==1)
      {
      if(ismine(row,column+1)==1)
	rcount++;
      }
    if(isvalid(row+1,column-1)==1)
      {
      if(ismine(row+1,column-1)==1)
	rcount++;
      }
    if(isvalid(row+1,column)==1)
      {
      if(ismine(row+1,column)==1)
	rcount++;
      }
    if(isvalid(row+1,column+1)==1)
      {
      if(ismine(row+1,column+1)==1)
	rcount++;
      }
    return rcount;
    }


void rboardesign()
    {
    for(i=0;i<9;i++)
       {
       for(j=0;j<9;j++)
	 {
	 board[i][j]='-';
	 rboard[i][j]='-';
	 }
       }
     for(co=0;co<10;)
	{
	i=rand()%9;
	j=rand()%9;
	if(rboard[i][j]=='-')
	  {
	   co++;
	   rboard[i][j]='*';
	  }
	}
     for(i=0;i<9;i++)
       {
       for(j=0;j<9;j++)
	  {
	   if(rboard[i][j]!='*')
	     {
	      rcount='0';
	      rboard[i][j]=count(i,j);
	     }
	  }
       }
    }

void nomine(int xh,int yk)
   {
    board[xh][yk]=rboard[xh][yk];
    if(isvalid(xh-1,yk-1)==1)
    {
    board[xh-1][yk-1]=rboard[xh-1][yk-1];
    if(rboard[xh-1][yk-1]=='0'&&board[xh-1][yk-1]!='0')
    nomine(xh-1,yk-1);
    }
    if(isvalid(xh-1,yk)==1)
    {
    board[xh-1][yk]=rboard[xh-1][yk];
    if(rboard[xh-1][yk]=='0'&&board[xh-1][yk]!='0')
    nomine(xh-1,yk);
    }
    if(isvalid(xh-1,yk+1)==1)
    {
    board[xh-1][yk+1]=rboard[xh-1][yk+1];
    if(rboard[xh-1][yk+1]=='0'&&board[xh-1][yk+1]!='0')
    nomine(xh-1,yk+1);
    }
    if(isvalid(xh,yk-1)==1)
    {
    board[xh][yk-1]=rboard[x][y-1];
    if(rboard[xh][yk-1]=='0'&&board[xh][yk-1]!='0')
    nomine(xh,yk-1);
    }
    if(isvalid(xh,yk+1)==1)
    {
    board[xh][yk+1]=rboard[xh][yk+1];
    if(rboard[xh][yk+1]=='0'&&board[xh][yk+1]!='0')
    nomine(xh,yk+1);
    }
    if(isvalid(xh+1,yk-1)==1)
    {
    board[xh+1][yk-1]=rboard[xh+1][yk-1];
    if(rboard[xh+1][yk-1]=='0'&&board[xh+1][yk-1]!='0')
    nomine(xh+1,yk-1);
    }
    if(isvalid(xh+1,yk)==1)
    {
    board[xh+1][yk]=rboard[xh+1][yk];
    if(rboard[xh+1][yk]=='0'&&board[xh+1][yk]!='0')
    nomine(xh+1,yk);
    }
    if(isvalid(xh+1,yk+1)==1)
    {
    board[xh+1][yk+1]=rboard[xh+1][yk+1];
    if(rboard[xh+1][yk+1]=='0'&&board[xh+1][yk+1]!='0')
    nomine(xh+1,yk+1);
    }
   }

int win()
   {
   f=0;
   for(i=0;i<9;i++)
     {
      for(j=0;j<9;j++)
	{
	 if(board[i][j]==rboard[i][j])
	  f++;
	}
     }
   if(f==71)
    return 1;
   else
    return 0;
   }

void play()
     {
     while(chcontinue=='y')
     {
      status=-1;
      rboardesign();
      cout<<"WELCOME TO THE GAME\n";
       if (system("CLS")) system("clear");
      show();
      while(status==-1)
	  {
	   cout<<"Enter row and column:\n";
	   cout<<"Row:";
	   cin>>x;
	   cout<<"Column:";
	   cin>>y;
	   --x;
	   --y;
	   if(isvalid(x,y)==1)
	     {
	      if(ismine(x,y)==1)
		{
		 for(i=0;i<9;i++)
		    {
		     for(j=0;j<9;j++)
			{
			 board[i][j]=rboard[i][j];
			}
		     }
		  if (system("CLS")) system("clear");
		 cout<<" ROW "<<x+1<<"  COLUMN "<<y+1<<"\n";
		 show();
		 cout<<"You lost the game .";
     cin>>a0;
		 status=0;
		}
	      else
		  {
		   if(rboard[x][y]=='0')
		     {
		      nomine(x,y);
		       if (system("CLS")) system("clear");
		      cout<<" ROW "<<x+1<<"  COLUMN "<<y+1<<"\n";
		      show();
		     }
		   else
		     {
		      board[x][y]=rboard[x][y];
		       if (system("CLS")) system("clear");
		      cout<<" ROW "<<x+1<<"  COLUMN "<<y+1<<"\n";
		      show();
		      for(i=0;i<9;i++)
			{
			 for(j=0;j<9;j++)
			   {
			    if(win()==1)
			     {
			      status=1;
			      cout<<"YOU WON THE GAME!!!\n";
            cin>>a0;
			     }
			    else
				status=-1;
			   }
			}
		      }
		   }
       }
     }
      if (system("CLS")) system("clear");
     cout<<"Do you want to start a new game. (y/n)?";
     cin>>chcontinue;
   }
   }

int main ()
     {
      if (system("CLS")) system("clear");
     cout<<"\t\t\t\tWELCOME TO MINESWEEPER GAME\n\nENTER YOUR NAME---";
     gets(name);
      if (system("CLS")) system("clear");
     cout<<"\t\t\t\tINSTRUCTION\n\n";
     cout<<"Minesweeper is a deceptively simple test of memory and reasoning.\n";
     cout<<"The goal of the game is to find empty squares and avoid mines.\n";
     cout<<"1.Uncover a mine(*), and the game ends.\n";
     cout<<"2.Uncover a empty square(-), and you keep playing.\n";
     cout<<"3.Uncover a number, it tells you how many mines lay hidden in eight surrounding squares.\n";
      if (system("CLS")) system("clear");
     play();  
     return 0;
     }