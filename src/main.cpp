#include<bits/stdc++.h>
#include<graphics.h>
#include<math.h>
using namespace std;


#define KEY_UP  72
#define KEY_DOWN  80
#define RETURN 13
#define KEY_RIGHT 77
#define VIEW '-'
enum keys {
    escape = 27,
    enter = 13
};

int windowstatus = 1;

class animate{
  public:
  int rotate = 0;
  void animation();
  void animation2();
};

void animate::animation(){
  // initwindow(getmaxwidth(),getmaxheight(),"hello");
	setcolor(LIGHTBLUE);
	for (int i = getmaxheight(); i > 0; i-= 4){
	settextstyle(8,0,10);
  outtextxy(250,i,"MEDICAMENT");
	delay(1);
	}
}

void animate::animation2(){
    cleardevice();
		line(30,50,250,50);
		line(100+(20*11),50,getmaxwidth()-30,50);
		line(30,50,30,getmaxheight()-30);
		line(getmaxwidth()-30,50,getmaxwidth()-30,getmaxheight()-30);
		line(30,getmaxheight()-30,getmaxwidth()-30,getmaxheight()-30);
		if(rotate == 0){
			settextstyle(0,0,10);
			outtextxy(250,0,"MEDICAMENT");
		}
		else if(rotate == 1){
			settextstyle(0,0,10);
			// outtextxy(350,30,"M");
			// settextstyle(8,0,10);
      outtextxy(250,0,"ΣEDICAMENT");
		}
		else if(rotate == 2){
			settextstyle(0,0,10);
      outtextxy(250,0,"WEDICAMENT");
		}
		rotate += 1;
		if(rotate > 2){
			rotate  = 0;
		}
  restorecrtmode();
  settextstyle(8,0,2);
}


#include"D:/surgical equipment system/include/login.h"
#include"D:/surgical equipment system/include/util.h"
#include"D:/surgical equipment system/include/orders.h"
	
int main(){
  

  int wid;
  wid = initwindow(getmaxwidth(), getmaxheight(),"MEDICAMENT");
  settextstyle(8,0,2);
  setcolor(LIGHTBLUE);

  UserInfo obj;
  animate anime;
  anime.animation();
  obj.LoginMenu();
  // animate anime;
  product_detail p;
  order_details ord;
  sorting sort;
  p.read_category();
  p.readdata(head);

   vector<string> LIST{"(1) Equipments Data Management",
  "(2) Display Equipments",
  "(3) Order Management & Details",
  "(4) Bill generation",
  "(5) Out Of Stock Products",
  "(6) Display Equipments By",
  "(7) Add on stock",
  "(8) Add Product Category",
  "(9) Remove Product Category",
  "(10) Exit"
  };
  
  while (1)
  {
  int oos = 0;
  struct product* ptr = head;
  while (ptr!=NULL)
  {
    if (ptr->quantity <= ptr->limit)
    oos +=1;
    ptr = ptr->next;
  }
      
  
  int j = 1;
  int TOP = 100;

	char ch;

    int p1, p2, p3, p4, p5, p6;
	  p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    int I = 0;

    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(LIST.size()-1));
  
  while(j){

    anime.animation2();
    
	TOP = 130;
	for (int i = 0; i < LIST.size(); i++){
    bgiout<<LIST[i];
    outstreamxy(100,TOP);
    TOP+=30;
  }
    
    if(oos > 0){
    setcolor(LIGHTRED);
    bgiout<<oos;

    outstreamxy(450,130+(30*4));
    setcolor(LIGHTBLUE);
    }
      TOP = TOP + 30;
    

	p1 = 100 + (LIST[I].length()*15) + 20;
    p2 = 138 + (30*I);
    p3 = p1+20;
    p4 = p2-20;
    p5 = p3;
    p6 = p4 + 40;

   int vert[] = {p1, p2, p3, p4, p5, p6, p1, p2};
	setfillstyle(SOLID_FILL, MAGENTA);
	drawpoly(4, vert);
	fillpoly(4, vert);

	ch = getch();

	switch (ch){
		case KEY_UP:{
			if(p2 > MAX_UP){
			p2 -= 5, p4 -= 5, p6 -= 5;
            I--;
            }
			break;
		}

		case KEY_DOWN:{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            }
			break;
		}
        
		case RETURN:{
          j= 0;
          p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    
          MAX_UP = 138 + (30*0);
          MAX_DOWN = 138 + (30*(LIST.size()-1));
		  break;
        }

        case keys::escape :{
            obj.LoginMenu();
            break;
        }

        case VIEW:{
           p.display(head);
        }
break;

	}
	clearviewport();
	restorecrtmode();
  }

   switch(I+1){

    case 1:
    p.menu(wid);
    break;

    case 2:
    p.display(head);
    setcurrentwindow(wid);
    break;

    case 3:{
    ord.menu();
    break;
    }
    case 4:{
    int wid = getcurrentwindow();
    ord.billing();
    setcurrentwindow(wid);
    }
    break;

    case 5:
      p.out_of_stock(head); 
    break;


    case 6:
      sort.menu();
    break;

    case 7:{
      p.add_stock(head);
      p.writedata(head);
    break;
    }

    case 8:{
    p.add_category();
    p.read_category();
    break;
    }

    case 9:
    p.delete_category(wid);
    break;

    case 10:
    closegraph(wid);
    exit(1);
    break;
}
  }

	return 0;
}