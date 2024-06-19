

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#define underline "\033[4m"
#define nounderline "\033[0m"


using namespace std;

class snake;
class walls;
class fruit;
class game;


void gotoxy(int x, int y) {
    COORD pos;   pos.X = x; pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}






class snake {
    
    vector<int> x, y;
    
    int size = 1;
    char kent = '\0', lkent = '\0';
    int mode=2;  // 1=simple 2=3 leveled game
    bool loopdm=0;

public:

    friend class game;
    friend class walls;
    friend class world1;
    friend class world2;
    friend class world3;
    friend int options(walls& o,bool &a, int& b, bool& d);

    bool player2 = false;
    char b1='w', b2='a', b3 = 's', b4 = 'd';
    int clo = 50;
    clock_t time=clock();
    int c=219;
    snake() {}
    snake(bool a,int b=0,bool c=false) :player2(a),mode(b),loopdm(c){}

    void addlen(){ x.push_back(x[size-1]); y.push_back(size-1); }

    bool gp2() { return player2; }
    int gx() { return x[0]; }
    int gy() { return y[0]; }

    void ini() {
        if (player2 == 0) { x.push_back(50); y.push_back(11); }
        else { x.push_back(50); y.push_back(36);  }
        //gotoxy(50, 35);    
        //gotoxy(50, 10);
    }

    void move() {
    	
    	HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

         SetConsoleTextAttribute(col, 14);
        
        gotoxy(x.back(), y.back());

        printf(" ");

        for (int i = size - 1; i > 0; i--) {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }
        lkent = kent;
        if (size > 1)
        {
            gotoxy(x[1], y[1]);
            printf("%c", c);
        }

    }


    void move2() {

        if (player2 == true) { b1 = 'i';  b2 = 'j';  b3 = 'k';  b4 = 'l'; }

        time = clock();

        while ((clock() < time + clo) && !_kbhit())
            ;




        if (clock() < time + clo) {

            kent = _getch();
            if ((kent == b4) && (lkent == b2))
                kent = b2;
            else if ((kent == b1) && (lkent == b3))
                kent = b3;
            else if ((kent == b3) && (lkent == b1))
                kent = b1;
            else if ((kent == b2) && (lkent == b4))
                kent = b4;
        }

    }


    void move3() {
        
        if (player2 == true) { b1 = 'i';  b2 = 'j';  b3 = 'k';  b4 = 'l'; }

    if (kent == b3) {
		move();
		gotoxy(x[0], ++y[0]);
		printf("%c", 31);
    }

    else if (kent == b1) {

		move();
		gotoxy(x[0], --y[0]);
		printf("%c", 30);
        }
    else if (kent == b2) {

		move();
		gotoxy(--x[0], y[0]);
		printf("%c", 17);
       }

    else if (kent == b4) {

		move();
		gotoxy(++x[0], y[0]);
		printf("%c", 16);
       }

    }

   
    void loop() {


        if (x[0] == 0) { gotoxy(x[0], y[0]); printf("%c", 186); x[0] = 99; }
        if (x[0] == 100) { gotoxy(x[0], y[0]); printf("%c", 186); x[0] = 1; }
        if (y[0] == 0) { gotoxy(x[0], y[0]); printf("%c", 205); y[0] = 20; }
        if (y[0] == 21) { gotoxy(x[0], y[0]); printf("%c", 205); y[0] = 1; }


        if (x[0] == 0) { gotoxy(x[0], y[0]); printf("%c", 186); x[0] = 99; }
        if (x[0] == 100) { gotoxy(x[0], y[0]); printf("%c", 186); x[0] = 1; }
        if (y[0] == 25) { gotoxy(x[0], y[0]); printf("%c", 205); y[0] = 45; }
        if (y[0] == 46) { gotoxy(x[0], y[0]); printf("%c", 205); y[0] = 26; }


    }


};





class fruit {

public:

    int fruitx, fruity;

    void assigningval(snake &obj) {
        srand(time(0));
        if (obj.player2==0) fruity = (rand() % 17) + 2;
        else fruity = (rand() % 20) + 26;
      
        fruitx = (rand() % 90) + 2;
    }


    void display() {
        gotoxy(fruitx, fruity);
        cout << (char)254;
    }

};



class walls : public fruit {

public:

    

    COORD a;

   void border() {
         HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

         SetConsoleTextAttribute(col, 2);
        
		a = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

        for (int c = 0;c <= 100;c++) {
            if (c == 0)
                printf("%c", 201);
            else if (c == 100)
                printf("%c", 187);
            else
                printf("%c", 205);
        }
        for (int c = a.Y;c < a.Y + 20;c++) {
            gotoxy(a.X, c + 1);
            printf("%c", 186);
            gotoxy(a.X + 100, c + 1);
            printf("%c", 186);
        }
        gotoxy(a.X, a.Y + 21);

        for (int c = 0;c <= 100;c++) {
            if (c == 0)
                printf("%c", 200);
            else if (c == 100)
                printf("%c", 188);
            else
                printf("%c", 205);
        }
    }

    virtual void border(snake& obj) {
         HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

         SetConsoleTextAttribute(col, 2);
        
		a = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
      
        for (int c = 0;c <= 100;c++) {
            if (c == 0)
                printf("%c", 201);
            else if (c == 100)
                printf("%c", 187);
            else
                printf("%c", 205);
        }
        for (int c = a.Y;c <a.Y+ 20;c++) {
            gotoxy(a.X, c + 1);
            printf("%c", 186);
            gotoxy(a.X+100, c + 1);
            printf("%c", 186);
        }
        gotoxy(a.X, a.Y + 21);
        
        for (int c = 0;c <= 100;c++) {
            if (c == 0)
                printf("%c", 200);
            else if (c == 100)
                printf("%c", 188);
            else
                printf("%c", 205);
        }
    }

    virtual int check(int &fx, int &fy, vector<int> &x, vector<int>  &y, int size) {
        for (int i = 0; i < size; i++)
        {
            if (fx == x[i] && fy == y[i])
            {
                return 1;
            }
        }
        return 0;
    }


    int out(int x, int y, int size, snake& obj) {
        int a = 10;
        if (obj.player2 == 1) a = 35;


        if (obj.size < 2|| obj.mode!=2) {
            gotoxy(40, a);
            printf("you are out\n");
            gotoxy(40, a + 1);
            printf("%cScore : %d   ", 179, size - 1);
        }


        else if(obj.size>2&&obj.mode==2) {
            gotoxy(40, a);
            printf("you cleared this level!!!\n");
        }


        gotoxy(0, 22);
        while (_getch() != 13) {
        }
        //exit(0);
        return 1;


    }

    // void
     int out2(snake& obj) {

        for (int i = 4; i < obj.size; i++)
        {
            if (obj.x[0] == obj.x[i] && obj.y[0] == obj.y[i]) {
                gotoxy(obj.x[0], obj.y[0]); cout << "X";
                return out(obj.x[0], obj.y[0], obj.size, obj);
            }
        }

        

        return 0;
    }

     int levelcleared(snake& obj) {
         if (obj.mode == 2 && obj.size > 2)return out(obj.x[0], obj.y[0], obj.size, obj); else return 0;
     }


    //void
    int out3(snake& obj) {
        if (obj.player2 == 1) {
            if (obj.y[0] == 46) {
                gotoxy(obj.x[0], obj.y[0]); cout << "X";
                return out(obj.x[0], obj.y[0], obj.size, obj);
            }
            if (obj.y[0] == 25) {
                gotoxy(obj.x[0], obj.y[0]); cout << "X";
                return out(obj.x[0], obj.y[0], obj.size, obj);
            }
        }
        else {
            if (obj.y[0] == 21) {
                gotoxy(obj.x[0], obj.y[0]); cout << "X";
                return out(obj.x[0], obj.y[0], obj.size, obj);
            }
            if (obj.y[0] == 0) {
                gotoxy(obj.x[0], obj.y[0]); cout << "X";
                return out(obj.x[0], obj.y[0], obj.size, obj);
            }
        }
        if (obj.x[0] == 0) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";
            return out(obj.x[0], obj.y[0], obj.size, obj);
        }
        if (obj.x[0] == 100) {
        gotoxy(obj.x[0], obj.y[0]); cout << "X";
        return out(obj.x[0], obj.y[0], obj.size, obj);
    }
        return 0;

    }

    virtual int out4(snake& obj) { return 0; }

    /*bool hitcheck(snake obj){
        if ()
    }*/

};


class world1 : public walls {


public:

    void obstacles(snake& obj) {
        int y;
        if (obj.gp2() == 0)y = 5;
        else y = 30;

        gotoxy(20, y);
        cout << "000000000000000000000000000000000000000000000000000000000000";

        gotoxy(20, y+10);
        cout << "000000000000000000000000000000000000000000000000000000000000";

    }
   
    void border(snake& obj) {
        walls::border(obj);
        obstacles(obj);
    }


    int check(int& fx, int& fy, vector<int>& x, vector<int>& y, int size) {
        for (int i = 0; i < size; i++)
        {
            if (fx == x[i] && fy == y[i])
            {
                return 1;
            }
        }
        if (fy == 5 || fy == 15 || fy == 30 || fy == 35) return 1;
        return 0;
    }

    int out4(snake& obj) {

            
                if (obj.x[0] > 20 && obj.x[0] < 80 && (obj.y[0] == 5 || obj.y[0] == 15 || obj.y[0] == 30 || obj.y[0] == 40 )) {
                    gotoxy(obj.x[0], obj.y[0]); cout << "X";
                    
                    return out(obj.x[0], obj.y[0], obj.size, obj);
                }
            
            return 0;
        }



}; 



class world2 : public walls {


public:

    void obstacles(snake& obj) {
        int y;
        if (obj.gp2() == 0)y = 4;
        else y = 29;

       
        gotoxy(10, y);
        printf("00000000000000000000");

        gotoxy(70, y);
        printf("00000000000000000000");

        gotoxy(40, y+6);
        printf("00000000000000000000");

        gotoxy(10, y+12);
        printf("00000000000000000000");

        gotoxy(70, y+12);
        printf("00000000000000000000");



    }

    void border(snake& obj) {
        walls::border(obj);
        obstacles(obj);
    }


    int check(int& fx, int& fy, vector<int>& x, vector<int>& y, int size) {
        for (int i = 0; i < size; i++)
        {
            if (fx == x[i] && fy == y[i])
            {
                return 1;
            }
        }
        if (fy == 4 || fy == 16 || fy == 29 || fy == 41 || fy == 10 || fy == 35) return 1;
        return 0;
    }

    int out4(snake& obj) {


        if (obj.x[0] >= 10 && obj.x[0] < 30 && (obj.y[0] == 4 || obj.y[0] == 16 || obj.y[0] == 29 || obj.y[0] == 41)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }

        if (obj.x[0] >= 70 && obj.x[0] < 90 && (obj.y[0] == 4 || obj.y[0] == 16 || obj.y[0] == 29 || obj.y[0] == 41)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }


        if (obj.x[0] >= 40 && obj.x[0] < 60 && (obj.y[0] == 10 || obj.y[0] == 351)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }

        return 0;
    }




};



class world3 : public walls {


public:

    void obstacles(snake& obj) {
        int y;
        if (obj.gp2() == 0)y = 2;
        else y = 27;

        gotoxy(20, y);
        cout << "000000000000000000000000000000000000000000000000000000000000";

        gotoxy(10, y+7);
        cout << "00000000000000000000000000000000000000000000000000000000000000000000000000000000";
        gotoxy(10, y + 8);
        cout << "0                                                                              0";

        gotoxy(10, y + 10);
        cout << "0                                                                              0";
        gotoxy(10, y+11);
        cout << "00000000000000000000000000000000000000000000000000000000000000000000000000000000";

        gotoxy(20, y + 17);
        cout << "000000000000000000000000000000000000000000000000000000000000";

    }

    void border(snake& obj) {
        walls::border(obj);
        obstacles(obj);
    }


    int check(int& fx, int& fy, vector<int>& x, vector<int>& y, int size) {
        for (int i = 0; i < size; i++)
        {
            if (fx == x[i] && fy == y[i])
            {
                return 1;
            }
        }
        if ((fy == 2 || fy == 9 || fy == 13 || fy == 19)||((fy==10)&&(fx==10|| fx == 70)) || ((fy == 12) && (fx == 10 || fx == 70))) return 1;
        return 0;
    }

    int out4(snake& obj) {



        if (obj.x[0] >= 20 && obj.x[0] < 80 && (obj.y[0] == 2 || obj.y[0] == 19 || obj.y[0] == 27 || obj.y[0] == 44)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }


        if (obj.x[0] >= 10 && obj.x[0] < 90 && (obj.y[0] == 9 || obj.y[0] == 13 || obj.y[0] == 38 || obj.y[0] == 34)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }

        if ((obj.x[0] == 10 || obj.x[0] == 89) && (obj.y[0] == 10 || obj.y[0] == 12 || obj.y[0] == 35 || obj.y[0] == 37)) {
            gotoxy(obj.x[0], obj.y[0]); cout << "X";

            return out(obj.x[0], obj.y[0], obj.size, obj);
        }


        return 0;


    }



};



class game {
   
public:

    int gscore() { return 1; }
  
    int leveledgame(bool a,int b,bool d,int c,int cc) {

        world1 w1;
        world2 w2;
        world3 w3;

        walls w0;
        walls* o1 = &w0;
        int x=0;

        

        for (x = 1;x <= 3;++x) {
           
            int check = 0; check = playgame(a,b,d,c, w1, w2, w3, w0, x,cc);
            if (check >= 1 )break;

            (x != 3) ? system("cls") : ++x;
        }
        return x;
    }

    int playgame(bool a,bool b,int cc) {

       
        /*world1 w1;
        world2 w2;
        world3 w3;*/
        
          int h=0;
        (a==1)?h=26:h=1;
        
        walls w0;

        walls *o1=&w0;
        snake o2(a,0,b);
        o2.c=cc;
       


            if (o2.player2 == 1) gotoxy(0, 25);
            else gotoxy(0, 0);

            o2.ini();

            o1->border(o2);

            gotoxy(o2.x[0], o2.y[0]); cout << "X";


            do {
                o1->assigningval(o2);
            } while (o1->check(o1->fruitx, o1->fruity, o2.x, o2.y, o2.size));
            o1->display();

            // gotoxy(50, 10);
            while (1) {
            	
            	
            	 gotoxy(103,h);
                    printf("%cPlayer %d", 179,a+1);
                    gotoxy(103,h+1);
                    printf("%cScore : %d   ", 179, o2.size - 1);
            	
            	

                do {
                    o2.move2();

                    o2.move3();

                    if (o2.loopdm == 1)  o2.loop(); 

                    if (o1->levelcleared(o2) == 1) return (o2.size-1);

                    if (o1->out3(o2) == 1) return (o2.size - 1);

                    if (o1->out2(o2) == 1) return (o2.size - 1);

                    if (o1->out4(o2) == 1) return (o2.size - 1);

                } while ((o2.gx() != o1->fruitx) || (o2.gy() != o1->fruity));

                o2.addlen();
                gotoxy(o2.x[o2.size], o2.y[o2.size]);
                printf("%c", 254);
                o2.size++;

                do {
                    o1->assigningval(o2);
                } while (o1->check(o1->fruitx, o1->fruity, o2.x, o2.y, o2.size));

                o1->display();

           

        }
    }



    int playgame(bool a,int b,bool d,int c,world1 &w1,world2 &w2, world3& w3,walls &w0,int x,int cc) {

        
          int h=0;
        (a==1)?h=26:h=1;


        walls* o1 = &w0;
        snake o2(a,b,d);

        o2.c=cc;
       

            if(c != 0)  x = c ;

            (x == 1) ? o1 = &w1 : (x == 2) ? o1 = &w2 : o1 = &w3;


            if (o2.player2 == 1) gotoxy(0, 25);
            else gotoxy(0, 0);

            o2.ini();

            o1->border(o2);

            gotoxy(o2.x[0], o2.y[0]); cout << "X";


            do {
                o1->assigningval(o2);
            } while (o1->check(o1->fruitx, o1->fruity, o2.x, o2.y, o2.size));
            o1->display();

            // gotoxy(50, 10);
            while (1) {
            	
            	
            	 gotoxy(103,h);
                    printf("%cPlayer %d", 179,a+1);
                    gotoxy(103,h+1);
                    printf("%cScore : %d   ", 179, o2.size - 1);
            	
            	

                do {
                    o2.move2();

                    o2.move3();

                    if (o2.loopdm == 1)  o2.loop();
                    
                    if (o1->levelcleared(o2) == 1) return 0;

                    if (o1->out3(o2) == 1) return 1;

                    if (o1->out2(o2) == 1) return 1;

                    if (o1->out4(o2) == 1) return 1;

                } while ((o2.gx() != o1->fruitx) || (o2.gy() != o1->fruity));

                o2.addlen();
                gotoxy(o2.x[o2.size], o2.y[o2.size]);
                printf("%c", 254);
                o2.size++;

                do {
                    o1->assigningval(o2);
                } while (o1->check(o1->fruitx, o1->fruity, o2.x, o2.y, o2.size));

                o1->display();

            }

        
    }




};






void intro(walls &o) {
    o.border();
//    gotoxy(48, 10);
//    cout << "game";
//    _getch();
      
      gotoxy(5, 2);
    cout << "0 0 0 0 0";
    gotoxy(5, 3);
    cout << "0       0";
    gotoxy(5, 4);
    cout << "0           0       0   0 0 0 0   0     0   0 0 0 0   0 0 0 0   0   0    0   0 0 0 0";
    gotoxy(5, 5);
    cout << "0 0 0 0 0   0       0      0      0     0   0         0     0   0   00   0   0      ";
    gotoxy(5, 6);
    cout << "        0   0       0      0      0 0 0 0   0 0 0     0 0 0 0   0   0  0 0   0  0  0";
    gotoxy(5, 7);
    cout << "0       0   0       0      0      0     0   0         0  0      0   0   00   0     0";
    gotoxy(5, 8);
    cout << "0 0 0 0 0   0 0 0   0      0      0     0   0 0 0 0   0     0   0   0    0   0 0 0 0";
	
	gotoxy(5, 11);
	cout << "            0 0 0 0 0 "; 
	gotoxy(5, 12);
	cout << "            0       0";
	gotoxy(5, 13);
	cout << "            0           0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0   0    0   0 0 0 0   0 0 0 0";
	gotoxy(5, 14);
	cout << "            0 0 0 0 0   0         0     0   0     0   0         00   0      0      0";
	gotoxy(5, 15);
	cout << "                    0   0 0 0     0 0 0 0   0 0 0 0   0 0 0     0  0 0      0      0 0 0 0";
	gotoxy(5, 16);
	cout << "            0       0   0         0  0      0         0         0   00      0            0" ;
	gotoxy(5, 17);
	cout << "            0 0 0 0 0   0 0 0 0   0     0   0         0 0 0 0   0    0      0      0 0 0 0";
    _getch();

    system("cls");
}




int options(walls& o,bool &a, int& b, bool& d,int &c) {

   // COORD a;
   bool check=false;
    string str;
    int x=0,x2=0,x3=0,mx2=0,mx3=0;
    int y=9;
    char key;
   
    a = 0; b = 1;d = 1;

    o.border();
    
    gotoxy(45, y-1);
    cout << underline << "OPTIONS" << nounderline;
    
    gotoxy(45, y+1);
    cout << "Start Game" ;
    
    gotoxy(45, y+2);
    cout <<"Settings";

    gotoxy(45, y+3);
    cout <<"View Score Board" ;

    gotoxy(45, y+4 );
    cout <<"Credits" ;
    
    gotoxy(45, y+5 );
    cout <<"Set Char" ;

    y = 10;

    while (1) {
    	
        gotoxy(42, y); cout << "->";

        key=_getch();
        
        if (key == 's'&&check==0) { gotoxy(42, y); cout << "  "; y++; if (y > 14)y = 10; }
        else if (key == 'w'&&check==0) { gotoxy(42, y); cout << "  "; y--; if (y < 10)y = 14; }
        
        else if (y == 10 && key == 'd') {  return 1; }

        else if (y == 11 && key == 'd') {

            y = 9;

            system("cls");
            o.border();

            gotoxy(45, y - 1);
            cout << underline << "Settings" << nounderline;

            gotoxy(45, y + 1);
            cout << "Mode";

            gotoxy(45, y + 2);
            cout << "Loop";

            gotoxy(45, y + 3);
            cout << "Vs Game";

           /* gotoxy(45, y + 4);
            cout << "Back";*/


            y = 10;
            while (1) {
                gotoxy(42, y); cout << "->";

                key = _getch();



                if (key == 's') { gotoxy(42, y); cout << "  "; y++; if (y > 12)y = 10; }
                else if (key == 'w') { gotoxy(42, y); cout << "  "; y--; if (y < 10)y = 12; }


                if (y == 10 && key == 'd') {
                    gotoxy(59, y);
                    cout << "Campaign";

                    gotoxy(59, y + 1);
                    cout << "Simple";

                    while (1) {
                        gotoxy(56, y); cout << "->";

                        key = _getch();



                        if (key == 's') { gotoxy(56, y); cout << "  "; y++; if (y > 11)y = 10; }
                        else if (key == 'w') { gotoxy(56, y); cout << "  "; y--; if (y < 10)y = 11; }
                        else if (key == 'a') {
                           
                            if ((key == 'a' || key == 'd') && y == 10) {
                                b = 2;
                            }

                            if ((key == 'a' || key == 'd') && y == 11) {
                                b = 1;
                            }

                            
                            gotoxy(56, 10);
                            cout << "           ";

                            gotoxy(56, 11);
                            cout << "         ";
                            y = 10;
                            break;
                        }
                        else if ((key == 'a' || key == 'd') && y == 10) { b = 2; return 0; }

                        else if ((key == 'a' || key == 'd') && y == 10) { b = 1; return 0; }

                        else if (key == 13 && y == 13) break;

                    }

                }


                if (y == 11 && key == 'd')
                     {
                        gotoxy(59, y);
                        cout << "Yes";

                        gotoxy(59, y + 1);
                        cout << "No";
                        y = 11;
                        while (1) {
                            gotoxy(56, y); cout << "->";

                            key = _getch();



                            if (key == 's') { gotoxy(56, y); cout << "  "; y++; if (y > 12)y = 11; }
                            else if (key == 'w') { gotoxy(56, y); cout << "  "; y--; if (y < 11)y = 12; }
                            else if (key == 'a') {
                                
                                if ((key == 'a' || key == 'd') && y == 11) {
                                    d = 1;
                                }

                                if ((key == 'a' || key == 'd') && y == 12) {
                                    d = 0;
                                }

                                
                                gotoxy(56, 11);
                                cout << "           ";

                                gotoxy(56, 12);
                                cout << "         ";
                                y = 11;
                                break;
                            }
                            else if ((key == 'a' || key == 'd') && y == 11) { d = 1; return 0; }

                            else if ((key == 'a' || key == 'd') && y == 12) { d = 0; return 0; }

                            else if (key == 13 && y == 13) break;

                        }

                    }


                if (y == 12 && key == 'd')
                {
                    gotoxy(59, y);
                    cout << "Yes";

                    gotoxy(59, y + 1);
                    cout << "No";

                    y = 12;
                    while (1) {
                        gotoxy(56, y); cout << "->";

                        key = _getch();



                        if (key == 's') { gotoxy(56, y); cout << "  "; y++; if (y > 13)y = 12; }
                        else if (key == 'w') { gotoxy(56, y); cout << "  "; y--; if (y < 12)y = 13; }
                        else if (key == 'a') {
                           
                            if ((key == 'a' || key == 'd') && y == 12) {
                                a = 1;
                            }

                            if ((key == 'a' || key == 'd') && y == 13) {
                                a = 0;
                            }
                            
                            gotoxy(56, 12);
                            cout << "           ";

                            gotoxy(56, 13);
                            cout << "         ";
                            y = 12;
                          
                            break;
                        }
                        else if ((key == 'a' || key == 'd') && y == 12) { a = 1; return 0; }

                        else if ((key == 'a' || key == 'd') && y == 13) { a = 0; return 0; }

                        else if (key == 13 && y == 13) break;

                    }

                }


                else if (key == 'a' ) {
                   
                     y = 9;
                     gotoxy(42, y - 1);

                     cout << underline << "           " << nounderline;

                     gotoxy(42, y + 1);
                     cout << "       ";

                     gotoxy(42, y + 2);
                     cout << "       ";

                     gotoxy(42, y + 3);
                     cout << "          ";
                    

                     system("cls");
                     o.border();

                     gotoxy(45, y - 1);
                     cout << underline << "OPTIONS" << nounderline;

                     gotoxy(45, y + 1);
                     cout << "Start Game";

                     gotoxy(45, y + 2);
                     cout << "Settings";

                     gotoxy(45, y + 3);
                     cout << "View Score Board";

                     gotoxy(45, y + 4);
                     cout << "Credits";
                     
                      gotoxy(45, y+5 );
                      cout <<"Set Char" ;

                     y = 10;
                     break;
                }



                else if (key == 13) return 0;
            
            }

           


        }
        
        
        else if (y == 12 && key == 'd') {
          check=true;
            fstream file("score.txt", ios::in);

            system("cls");
            o.border();
            gotoxy(44, 9);
            cout << "player1 : player2";
            x = 11;

            while (getline(file,str)) {
                x2 = stoi(str);
                if(mx2<x2)mx2=x2;
                gotoxy(44, x); cout << x2;
                getline(file,str);
                x3 = stoi(str);
                if(mx3<x3)mx3=x3;
				gotoxy(54, x); cout << x3;
                ++x;
            }
            
            gotoxy(44, ++x); cout << "max score = "; (mx2>mx3)? cout<<mx2 << " player1" :cout<< mx3<< " player2"; 

            file.close();
           // _getch();
        
        }

        
        else if (y == 13 && key == 'd') {
            system("cls");
            o.border();
            gotoxy(45, 8);
            cout << underline << "GROUP MEMBERS" << nounderline;

            gotoxy(45, 10);
            cout << "Furzan Ahmed 22k-4330";

            gotoxy(45, 11);
            cout << "Taha Sharif 22k-4145";

            gotoxy(45, 12);
            cout << "Mehdi Aabdi 22k-4480";

        }
        
          else if (y == 14 && key == 'd'){
          	
          	gotoxy(55,14);
          	cout<<"enter character ascii value : ";cin>>c;
          		gotoxy(55,14);
          	cout<<"                                       ";
          	
		  }
        
        else if (key == 'a') {
            check=false;
            y = 9;
            gotoxy(42, y - 1);

            cout << underline << "           " << nounderline;

            gotoxy(42, y + 1);
            cout << "       ";

            gotoxy(42, y + 2);
            cout << "       ";

            gotoxy(42, y + 3);
            cout << "          ";


            system("cls");
            o.border();

            gotoxy(45, y - 1);
            cout << underline << "OPTIONS" << nounderline;

            gotoxy(45, y + 1);
            cout << "Start Game";

            gotoxy(45, y + 2);
            cout << "Settings";

            gotoxy(45, y + 3);
            cout << "View Score Board";

            gotoxy(45, y + 4);
            cout << "Credits";
            
             gotoxy(45, y+5 );
             cout <<"Set Char" ;
            
            y = 10;
         
                }


        else if ( key == 13) break;
    }
    
    
    system("cls");
    return 0;

}




int main() {
	
	
	
    bool  a = 0, d = 0;
    
	
	int b = 0, c = 219, p1=0,p2=0,ans=1;

    fstream file("score.txt", ios::app);


    walls ob;
   
    
    int check=0;
    
    intro(ob);
    
    while(ans){
	
    check=0;
    
    while(check!=1){
       
	   check= options(ob, a, b, d,c);
              
	   system("cls");

    }
    
    
    
    game o1;
    
	game o2;
    
	
	if (b == 1) {
    
	    if(a==1){ 
            p1=o1.playgame(0,d,c); p2=o2.playgame(1, d,c);
            file << p1 <<endl;  file << p2 << endl;
        }
        else {
            p1 = o1.playgame(0, d,c); p2 = 0; file << p1 <<endl;  file << p2 << endl;
        }
    }
    else {
        if (a == 1) {
            p1=o1.leveledgame(0,b,d,0,c); p2=o2.leveledgame(1, b, d, 0,c);
            if (p1>p2){
            	gotoxy(44,15); cout<<"player 1 won!!!";
			}
			else if (p1<p2){
            	gotoxy(44,15); cout<<"player 2 won!!!";
			}
			else{
            	gotoxy(44,15); cout<<"nobody won!!!";
			}
        }
        else o1.leveledgame(0, b, d, 0,c);
    }
    
	gotoxy(25,17);
	
	
	cout<<"do you want to continue? if yes than press 1 else 0";
	
	gotoxy(25,18); 
	
	cin>>ans;
	
	system("cls");
	
}
    
	file.close();

}




