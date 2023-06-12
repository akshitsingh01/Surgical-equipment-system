#include<bits/stdc++.h>

enum pp{
    backspace = 8,
    returns  = 13
};

bool check(string);


class UserInfo{
public:
 animate anime;
void login(int attempt);
void signup();
void LoginMenu(){

 vector<string>LIST{"LOGIN",
    "CHANGE ADMIN",
    "EXIT",
    };

  int wid10 = initwindow(getmaxwidth(), getmaxheight(),"WELCOME");
  setcolor(LIGHTBLUE);
 
  anime.animation();

     while (1){
anime.animation2();
  int j = 1;
  int TOP = 100;

	char ch;

    int p1, p2, p3, p4, p5, p6;
	  p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    // int px;
    int I = 0;

    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(LIST.size()-1));
  while(1){
  while(j){
  
  settextstyle(8,0,2);
	TOP = 130;
	for (int i = 0; i < LIST.size(); i++){
    bgiout<<LIST[i];
    outstreamxy(100,TOP);
      TOP = TOP + 30;
    }

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
            clearviewport();
      anime.animation2();
            }
			break;
		}

		case KEY_DOWN:{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            clearviewport();
            anime.animation2();
            }
			break;
		}
        
		case RETURN:{
          j= 0;
          p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    
          MAX_UP = 138 + (30*0);
          MAX_DOWN = 138 + (30*(LIST.size()-1));
          clearviewport();
          anime.animation2();
		  break;
        }

        case keys::escape :{
            closegraph(wid10);
			      exit(1);
            break;
        }

	}

  }
        cleardevice();
          switch(I+1){
        case 1:
        login(0);
           return;
        break;

        case 2:{
        signup();
        login(0);
        return;
        }
        
        break;

        case 3:{
        closegraph();
        exit(1);
        }
        break;
    }
     
  }
   cleardevice();
}
closegraph(wid10);
}

};

 void UserInfo::signup(){

    
   anime.animation2();
   string userid;
   string password;
   string pwd;
   string master;
   
   fstream f;
   f.open("password.dat");
   fflush(stdin);
  getline(f,pwd);
  // f>>pwd;
  fflush(stdin);
  getline(f,pwd);


   if(f){
    int op  = 1;
    string oldpwd;
    char buff;
    while(op){
    anime.animation2();
    outtextxy(100,130,"Already admin account exists!");
    bgiout<<"Enter old password or master key : ";
    for (int i = 0; i < oldpwd.length(); i++)
    {
      bgiout<<"*";
    }
    outstreamxy(100,200);
    buff = getch();

    switch(buff){
       case RETURN:{
        ifstream mst;
        mst.open("master.txt",ios::out);
        getline(mst,master);
        if(oldpwd==pwd ||oldpwd==master){
          op = 0;
        }
        else{
          outtextxy(100,250,"password not matched press any key to continue");
          getch();
          oldpwd.clear();
        }
        mst.close();
       }
       break;

      case pp::backspace:{
        
        if(oldpwd.length() > 0){
        oldpwd.pop_back();
        }
       }
       break;

      default :{
          oldpwd = oldpwd+ buff;
      }
      break;
    
    }
    cleardevice();
    }
  }

  char buff;
  int p = 1;

  while(p){
  anime.animation2();
  outtextxy(100,100,"SIGNUP");
  outtextxy(100,150,"Create Login Account");
  outtextxy(100,180,"Enter Details :");
  bgiout<<"Create UID : "<<userid;
  outstreamxy(100,230);

    buff = getch();

        switch(buff){
            case RETURN:{
                p = 0;
            }
            break;

            case pp::backspace:{
              if(userid.length() > 0){
                userid.pop_back();
              }
            }
            break;

            case keys::escape:{
               return;
            }
            break;

            default:{
               userid = userid + buff;
            }
            break;
        }
        cleardevice();
    }
    int msg = 0;
    p = 1;
    while(p){
   anime.animation2();
  if(msg){
    setcolor(RED);
    outtextxy(100,450,"Password requirements not matched");            
    setcolor(LIGHTBLUE);
  }    

  outtextxy(100,100,"SIGNUP");
  outtextxy(100,150,"Create Login Account");
  outtextxy(100,180,"Enter Details :");
  bgiout<<"Create UID : "<<userid;
  outstreamxy(100,230);
  outtextxy(100,260,"minimum 8 characters including at least 1 capital letter ,1 number and 1 symbol");
  bgiout<<"Password : ";
  for (int i = 0; i < password.length(); i++)
  {
    bgiout<<"*";
  }
  outstreamxy(100,290);

    buff = getch();

        switch(buff){
            case RETURN:{
                if(check(password)){
                  p = 0;
                }
                else{
                    msg = 1;
                }
            }
            break;

            case pp::backspace:{
              if(password.length() > 0){
                password.pop_back();
              }
            }
            break;

            case keys::escape:{
               return;
            }
            break;

            default:{
               password = password + buff;
            }
            break;
        }
        cleardevice();
    }
   
  f.close();
  remove("password.dat");
  fstream newuser;
  newuser.open("password.dat",ios::out);
  newuser<<userid;
  newuser<<endl;
  newuser<<password;
  newuser.close();
  cleardevice();
 }

 void UserInfo::login(int attempt){
    anime.animation2();
    fstream f; 
    f.open("password.dat");

    if(attempt>= 3){
        closegraph();
        exit(1);
    }   
    
    if(!f) signup();
     outtextxy(100,200,"LOGIN");

     outtextxy(100,230,"Only 3 attempts allowed");

     bgiout<<"Attempt : "<<attempt+1;
     outstreamxy(100,260);
    
     string checkUid,checkpwd;

    int l = 1;

    while(l){
    anime.animation2();
    settextstyle(8,0,2);
    restorecrtmode();
    outtextxy(100,200,"LOGIN");
    outtextxy(100,230,"Only 3 attempts allowed");
    bgiout<<"Attempt : "<<attempt+1;
    outstreamxy(100,260);
    restorecrtmode();
    bgiout<<"UID : "<<checkUid;
    outstreamxy(100,300);

    char buff = getch();

        switch(buff){
            case RETURN:{
                l = 0;
                break;
            }

            case pp::backspace:{
              if(checkUid.length() > 0){
                checkUid.pop_back();
              }
               break;
            }

            case keys::escape:{
               return ;
               break;
            }
            
            default:{
               checkUid = checkUid + buff;
               break;
            }
        }
        cleardevice();
    }

    int p = 1;

    while (p)
    {
    anime.animation2();
    settextstyle(8,0,2);
    outtextxy(100,200,"LOGIN");
    outtextxy(100,230,"Only 3 attempts allowed");
    bgiout<<"Attempt : "<<attempt+1;
    outstreamxy(100,260);
    bgiout<<"UID : "<<checkUid;
    outstreamxy(100,300);
    bgiout<<"Password : ";
  
    for (int i = 0; i < checkpwd.length(); i++)
    {
      bgiout<<"*";
    }
    outstreamxy(100,340);
    char buff = getch();

        switch(buff){
            case RETURN:{
                p = 0;
                break;
            }

            case pp::backspace:{
              if(checkpwd.length() > 0){
                checkpwd.pop_back();
              }
               break;
            }

            case keys::escape:{
               return ;
               break;
            }

            default:{
               checkpwd = checkpwd + buff;
               break;
            }
        }
        cleardevice();
    }
    

     string storedid,storedpwd;
     
     ifstream in;
     in.open("password.dat");
    
     getline(in,storedid);
     getline(in,storedpwd);
     in.close();
     if (storedid==checkUid && storedpwd==checkpwd)
     {
      return;
     }
     else{
        attempt+=1;
        login(attempt);
     }
     clearviewport();
 }

bool check(string s){

  if (s.length() < 7) return false;
  bool Capletter = false,number = false,specialchar = false;
  for (int i = 0; i < s.length(); i++){
      if (s[i] >= char(65) && s[i] <= char(90)) Capletter = true;
      else if (s[i]>= char(48) && s[i] <= char(57)) number = true;
      else if (s[i] >= char(33) && s[i] <= char(47) || s[i] >= char(58) && s[i] <= char(64) || s[i] >= char(91) && s[i] <= char(96) || s[i] >= char(123) && s[i] <= char(127))
       specialchar=true;
}

 if(Capletter == true && number == true && specialchar == true)return true;
      else return false; 

return false;

}