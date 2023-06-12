typedef struct order{
   long long int orderid;
   int totalitems = 0;
   float final = 0;
   float tax = 0;
   struct date{
      int day;
      int month;
      int year;
      int tm_min;
      int tm_hour;
      int tm_sec;
   }dt;
   
   char cname[30];
   long long int ccontact;
   char email[50];
}order;

typedef struct values{
   char name[50];
   float price;
   int  quantity;
   float total; 
}it;

// vector<it*> cart;
float final = 0;

struct product *head2;
class order_details{
    public:
    animate anime;
    product_detail obj;
    void readfile(struct product*);
    order_details(){
        readfile(head2);
    }
    void menu();
    void process_order(int j);
//     void display(product *);
    void start_transaction(int,vector<it*>);
    long long int generate_id(long long int);
    bool display_currentbill(order *,vector<it*>);
    void read_order(int );
    void search_order();
    void update_quantity(struct product *,char *,int q);
    void write_quantity(struct product* );
    void billing();
};

void order_details::update_quantity(struct product *h,char name[],int q){

    while (h!=NULL)
    {
       if(strcmp(h->name,name)==0){
          h->quantity = h->quantity-q;
          break;
       }
       h=h->next;
    }
}

void order_details::write_quantity(struct product *h){

    FILE *fp = fopen("Product_details.bin","wb");
    while (h!=NULL)
    {
       fwrite(h,sizeof(product),1,fp);
       h=h->next;
    }
    fclose(fp);
}

void order_details::search_order(){
  
  long long int s = 0;
  int j = 1;
  char ch;
  string temp;
  int notfound = 1;
  cleardevice();

   while(j){
   bgiout<<"Enter Phone Number Or Order ID : "<<temp;
   outstreamxy(100,100);
   ch = getch();
   switch (ch)
   {
   case RETURN:
    j = 0;
    break;

   case pp::backspace:{
    if(temp.length() > 0){
    temp.pop_back();
    s = s/10;
    }
   }
   break;

   case VIEW:{
    obj.display(head);
    }
    break;
   
   default:{
      if(int(ch) >= 48 && int(ch) <= 57){
        temp = temp + ch;
        s = (s*10) + int(ch) - 48;
      }
   }
    break;
   }
    cleardevice();
   }

    // int wid = getcurrentwindow();

    int wid = initwindow(1200,getmaxheight(),"Order summuary");
    settextstyle(8,0,1);
	setcolor(LIGHTGRAY);
	outtextxy((getmaxwidth()/2)-230,5,"Order Summary");
	line(0,35,1200,35);
	line(0,getmaxheight()-50,1200,getmaxheight()-50);
    outtextxy(700,getmaxheight()-30,"Press right(->) arrow key to change page");

   FILE *fp = fopen("order_history.bin", "rb");
   order pd;
   it ii;
   int TOP = 35;
   int run = 1;
   while(fread(&pd,sizeof(order),1,fp) && run == 1){
      if(pd.ccontact == s || pd.orderid == s){
      notfound = 0;
      run = 0;
      TOP += 5;
      bgiout<<"Date : "<<pd.dt.day<<"/"<<pd.dt.month<<"/"<<pd.dt.year;
      outstreamxy(30,TOP);
      bgiout<<pd.dt.tm_hour<<":"<<pd.dt.tm_min<<":"<<pd.dt.tm_min;
      outstreamxy(getmaxwidth()/2-230,TOP);
      bgiout<<"Contact No. : "<<pd.ccontact;
      outstreamxy(900,TOP);
      TOP+=30;
      bgiout<<"Email : "<<pd.email;
      outstreamxy(30,TOP);
      bgiout<<"Order ID : "<<pd.orderid;
      outstreamxy(900,TOP);
      TOP+=50;

      outtextxy(200,TOP,"Name");
      outtextxy(400,TOP,"Quantity");
      outtextxy(500,TOP,"price");
      outtextxy(600,TOP,"Total");
      TOP+=10;

      for (int i = 0; i < pd.totalitems; i++){
      fread(&ii,sizeof(it),1,fp);
      TOP+=30;
      bgiout<<"("<<i+1<<") "<<ii.name;
      outstreamxy(170,TOP);
      bgiout<<ii.quantity;
      outstreamxy(400,TOP);
      bgiout<<ii.price;
      outstreamxy(500,TOP);
      bgiout<<ii.total;
      outstreamxy(600,TOP);
     }
     TOP+=5;
     TOP+=30;
     line(0,TOP,1200,TOP);
     TOP+=30;
     bgiout<<"GST(12%) : "<<pd.tax;
     outstreamxy(30,TOP);
     bgiout<<"Total Bill : "<<pd.final;
     outstreamxy(500,TOP);
     TOP+=35;
     line(0,TOP,1200,TOP);
    }
    for (int i = 0; i < pd.totalitems; i++){
      fread(&ii,sizeof(it),1,fp);
    }
   }
     fclose(fp);

    if(notfound){
        outtextxy(100,100,"Record Not Exist!");
    }
    getch();
    closegraph(wid);
}

vector<int>windows;

int getnewwindow(int &TOP,int menu){
   int j = 1;
   char ch;
   product_detail obj;
   while(j){
      ch = getch();
      switch (ch){
      case KEY_RIGHT:{
         j = 0;
         break;
      }
      case RETURN:{
        j = 0;
        for (int i = 0; i < windows.size(); i++)
        {
            closegraph(windows[i]);
        } 
        windows.clear();
         return -1;
      }
      break;

    case VIEW:{
    obj.display(head);
    }
    break;
}

   }

   int newwid = initwindow(1200,getmaxheight(),"Order summuary");
   windows.emplace_back(newwid);
	settextstyle(8,0,1);
	setcolor(LIGHTGRAY);
	outtextxy((getmaxwidth()/2)-230,5,"Order Summary");
	line(0,35,1200,35);
	line(0,getmaxheight()-50,1200,getmaxheight()-50);
   outtextxy(700,getmaxheight()-30,"Press right(->) arrow key to change page");   
   TOP = 45;
}

void order_details::read_order(int menu){
    int status = 0;
    int wid = initwindow(1200,getmaxheight(),"Order summuary");
    windows.emplace_back(wid);

   settextstyle(8,0,1);
	setcolor(LIGHTGRAY);
	outtextxy((getmaxwidth()/2)-230,5,"Order Summary");
	line(0,35,1200,35);
	line(0,getmaxheight()-50,1200,getmaxheight()-50);
   outtextxy(700,getmaxheight()-30,"Press right(->) arrow key to change page");

   FILE *fp = fopen("order_history.bin", "rb");
   order pd;
   it ii;
   int TOP = 35;
   
   while(fread(&pd,sizeof(order),1,fp)){

      TOP += 5;
      if(TOP >= getmaxheight()-55) status = getnewwindow(TOP,menu);
      if(status == -1) return;
      bgiout<<"Date : "<<pd.dt.day<<"/"<<pd.dt.month<<"/"<<pd.dt.year;
      outstreamxy(30,TOP);
      bgiout<<pd.dt.tm_hour<<":"<<pd.dt.tm_min<<":"<<pd.dt.tm_min;
      outstreamxy(getmaxwidth()/2-230,TOP);
      bgiout<<"Contact No. : "<<pd.ccontact;
      outstreamxy(900,TOP);
      TOP+=30;
      if(TOP >= getmaxheight()-55) status = getnewwindow(TOP,menu);
      if(status == -1) return;
      bgiout<<"Email : "<<pd.email;
      outstreamxy(30,TOP);
      bgiout<<"Order ID : "<<pd.orderid;
      outstreamxy(900,TOP);
      TOP+=50;
      if(TOP >= getmaxheight()-55) status = getnewwindow(TOP,menu);
      if(status == -1) return;

      outtextxy(200,TOP,"Name");
      outtextxy(400,TOP,"Quantity");
      outtextxy(500,TOP,"price");
      outtextxy(600,TOP,"Total");
      TOP+=10;
      if(TOP >= getmaxheight()-55)status = getnewwindow(TOP,menu);
      if(status == -1) return;

      for (int i = 0; i < pd.totalitems; i++){
      fread(&ii,sizeof(it),1,fp);
      TOP+=30;
      if(TOP >= getmaxheight()-55)status = getnewwindow(TOP,menu);
      if(status == -1) return;
      bgiout<<"("<<i+1<<") "<<ii.name;
      outstreamxy(170,TOP);
      bgiout<<ii.quantity;
      outstreamxy(400,TOP);
      bgiout<<ii.price;
      outstreamxy(500,TOP);
      bgiout<<ii.total;
      outstreamxy(600,TOP);
     }

     TOP+=35;
     if(TOP >= getmaxheight()-55) status = getnewwindow(TOP,menu);
     if(status == -1) return;
     else
     line(0,TOP,1200,TOP);
     TOP+=5;
     if(TOP >= getmaxheight()-55) status = getnewwindow(TOP,menu);
     if(status == -1) return;
     bgiout<<"GST(12%) : "<<pd.tax;
     outstreamxy(30,TOP);
     bgiout<<"Total Bill : "<<pd.final;
     outstreamxy(500,TOP);
     TOP+=35;
     if(TOP >= getmaxheight()-55) 
     status = getnewwindow(TOP,menu);
     if(status == -1) return;
     else
     line(0,TOP,1200,TOP);
   }
     fclose(fp);
    int currwindow = getcurrentwindow();
    char ch;
    while(1){
    ch = getch();
    if(ch == RETURN){

    for (int i = 0; i < windows.size(); i++){
      closegraph(windows[i]);
    }

    windows.clear();
    break;
    }
    }

}

bool order_details::display_currentbill(order *pd,vector<it*>cart){

int wid = initwindow(1200,getmaxheight(),"Order summuary");
    settextstyle(8,0,1);
	setcolor(LIGHTGRAY);
	outtextxy((getmaxwidth()/2)-230,5,"Order Summary");
	line(0,35,1200,35);
	line(0,getmaxheight()-50,1200,getmaxheight()-50);
      int TOP = 35;
    
      TOP += 5;
      bgiout<<"Date : "<<pd->dt.day<<"/"<<pd->dt.month<<"/"<<pd->dt.year;
      outstreamxy(30,TOP);
      bgiout<<pd->dt.tm_hour<<":"<<pd->dt.tm_min<<":"<<pd->dt.tm_min;
      outstreamxy(getmaxwidth()/2-230,TOP);
      bgiout<<"Contact No. : "<<pd->ccontact;
      outstreamxy(900,TOP);
      TOP+=30;
      bgiout<<"Email : "<<pd->email;
      outstreamxy(30,TOP);
      bgiout<<"Order ID : "<<pd->orderid;
      outstreamxy(900,TOP);
      TOP+=50;

      outtextxy(200,TOP,"Name");
      outtextxy(400,TOP,"Quantity");
      outtextxy(500,TOP,"price");
      outtextxy(600,TOP,"Total");
      TOP+=10;

      for (int i = 0; i < pd->totalitems; i++){
      TOP+=30;
      bgiout<<"("<<i+1<<") "<<cart[i]->name;
      outstreamxy(170,TOP);
      bgiout<<cart[i]->quantity;
      outstreamxy(400,TOP);
      bgiout<<cart[i]->price;
      outstreamxy(500,TOP);
      bgiout<<cart[i]->total;
      outstreamxy(600,TOP);
     }
     TOP+=5;
     TOP+=30;
     line(0,TOP,1200,TOP);
     TOP+=30;
     bgiout<<"GST(12%) : "<<pd->tax;
     outstreamxy(30,TOP);
     bgiout<<"Total Bill : "<<pd->final+pd->tax;
     outstreamxy(500,TOP);
     TOP+=35;
     line(0,TOP,1200,TOP);

    getch();
    closegraph(wid);
}

long long int order_details::generate_id(long long int contactno){

    int digit = 0;
    long long int copy = contactno;
    long long int id = 10000000+rand()%10000000;


    for (int i = 0; i < 4; i++)
    {
        digit = copy%10;
        id = (id*10) + digit;
        copy = copy/10;
    }
    
    return id;
}

void order_details::start_transaction(int l,vector<it*>cart){
    cleardevice();
    for(int i = 0;i < cart.size();i++){
        outtextxy(100,100+(i*30),cart[i]->name);
    }
    getch();
    cleardevice();
    order *pd = new order();
    pd->totalitems = cart.size();
    
    int j = 1;
    char ch;
    string temp;

    while (j){
        bgiout<<"Enter customer or company name : "<<temp;
        outstreamxy(100,100);
        ch = getch();

        switch(ch){
            case RETURN:{
            j = 0;
            }
            break;

            case pp::backspace:{
                if(temp.length() > 0){
                    temp.pop_back();
                }
            }
            break;

            case keys::escape:{
                return;
            }
            break;

            case VIEW:{
            obj.display(head);
            }
            break;

            default:{
                temp = temp + ch;
            }
            break;
        }
    
        cleardevice();
    }

    strcpy(pd->cname,temp.c_str());
     
    j =  1;
    temp.clear();

    while (j){
        bgiout<<"customer or company name : "<<pd->cname;
        outstreamxy(100,100);
        bgiout<<"Contact Number : "<<temp;
        outstreamxy(100,130);
        ch = getch();

        switch(ch){
            case RETURN:{
            j = 0;
            }
            break;

            case pp::backspace:{
                if(temp.length() > 0){
                    temp.pop_back();
                    pd->ccontact = pd->ccontact/10;
                }
            }
            break;

            case keys::escape:{
                return;
            }
            break;

            case VIEW:{
            obj.display(head);
            }
            break;

            default:{
                if(int(ch) >= 48 && int(ch) <= 57){
                temp = temp + ch;
                pd->ccontact = (pd->ccontact*10) + int(ch) - 48;
                }
            }
            break;
        }
        cleardevice();
    }

    j =  1;
    temp.clear();

    while (j){
        bgiout<<"customer or company name : "<<pd->cname;
        outstreamxy(100,100);
        bgiout<<"Contact Number : "<<pd->ccontact;
        outstreamxy(100,130);
        bgiout<<"Email : "<<temp;
        outstreamxy(100,160);
        ch = getch();

        switch(ch){
            case RETURN:{
            j = 0;
            }
            break;

            case pp::backspace:{
                if(temp.length() > 0){
                    temp.pop_back();
                }
            }
            break;

            case keys::escape:{
                return;
            }
            break;

            case VIEW:{
            obj.display(head);
            }
            break;

            default:{
                temp = temp + ch;
            }
            break;
        }
        cleardevice();
    }

    if(temp.length()==0){
        strcpy(pd->email,"NULL");
    }
    else{
        strcpy(pd->email,temp.c_str()); 
    }

    pd->final = final;
    pd->tax = (final/100)*12;
    pd->orderid = generate_id(pd->ccontact);

    time_t now = time(NULL);
    tm *ltm = localtime(&now);
    pd->dt.day = ltm->tm_mday;
    pd->dt.month = ltm->tm_mon+1;
    pd->dt.year = ltm->tm_year+1900;
    pd->dt.tm_hour = ltm->tm_hour;
    pd->dt.tm_min = ltm->tm_min+1;
    pd->dt.tm_sec = ltm->tm_sec+1;
    
    if(display_currentbill(pd,cart)){
    
    FILE *fp = fopen("order_history.bin","ab");
    fwrite(pd,sizeof(order),1,fp);

    for (int i = 0; i < pd->totalitems; i++)
    {
        fwrite(cart[i],sizeof(it),1,fp);
        update_quantity(head,cart[i]->name,cart[i]->quantity);
        
    }
    fclose(fp);
    
    write_quantity(head);

    }
    else{
        return;
    }
}
 

void order_details::process_order(int k){

    vector<it*>cart; 
    
    product_detail obj;
    int curr = getcurrentwindow();
    obj.display(head);
    setcurrentwindow(curr);
    char select[30],ch;
    int id = 0;
    bool check  = 0;
    string temp;
    int j = 1;
    int run = 1;

    while (run){
      j = 1;
    while(j){
        cleardevice();
        bgiout<<"Enter Equipment ID with first character (+) or enter the name directly : "<<temp;
        outstreamxy(100,100);
        restorecrtmode();
        ch = getch();
        switch (ch){
        case RETURN:{
            j = 0;
        }
            break;

        case pp::backspace:{
            if(temp.length() > 0){
            temp.pop_back();
            }
        }
        break;

        case keys::escape :{
            return;
        }
        break;

        case VIEW:{
            obj.display(head);
            }
            break;
        
        default:{
            temp = temp + ch;
        }
            break;
        }

        cleardevice();
    }

    strcpy(select,temp.c_str());
    temp.clear();

    if(select[0]=='\0') return;
    if(select[0] == '+'){
    check = 1;
    id = convertid(select);
    }

    struct product* ptr = head;
    struct product *item = new struct product();
    item = obj.searchbool(ptr,id,select,check);

    if(item == NULL){
    outtextxy(100,150,"Invalid Input");
    getch();
    }
    else{
    int q = 0;
    j = 1;
    
    while (j){
    bgiout<<"Enter Quantity : "<<temp;
    outstreamxy(100,150);
    ch = getch();
    switch (ch){
    case RETURN:{
    j = 0;
    }
    break;

    case pp::backspace:{
        if(temp.length() > 0){
        temp.pop_back();
        q = q/10;
        }
    }
    break;

    case keys::escape :{
    return ;
    }
    break;

    case VIEW:{
    obj.display(head);
    }
    break;

    default:{
    if(int(ch) >= 48 && int(ch) <= 57){ 
    temp = temp + ch;
    q = q*10 + int(ch) - 48;
    }
    }
    break;
    }
    cleardevice();
}


    temp.clear();
    int qt = item->quantity - q;

   if(qt < 0){
    setcolor(LIGHTRED);
    outtextxy(100,200,"Insufficient Stock");
    bgiout<<"Available Stock : "<<item->quantity;
    outstreamxy(100,230);
    getch();
    setcolor(LIGHTBLUE);
}
else{
    it * m = new it();
    m->quantity = q;
    strcpy(m->name,item->name);
    m->price = item->price;
    m->total = m->price * m->quantity;
    final = final + m->total;
    cart.emplace_back(m);
    char val;
    
    cleardevice();
    bgiout<<"Enter 1 for new entry and press enter to start billing and esc to end this transaction ";
    outstreamxy(100,200);
    j = 1;

    while (j){
    val = getch();
    if(val == RETURN ||val == '1' || val == keys::escape) j = 0;
    }

    if(val == '1') continue;
    else if(val == RETURN){
        start_transaction(k,cart);
        return;
    }
    else if(val == keys::escape){
        cart.clear();
        temp.clear();
        final = 0;
        return;
    }

}

}

   cleardevice();
}
    
    
}

void order_details::readfile(struct product *h){
    struct product p1;
    FILE *fp = fopen("Product_details.bin","rb");

    while (fread(&p1,sizeof(struct product),1,fp))
    {
        if(h==NULL){
        h = (struct product*)malloc(sizeof(struct product));
        h->id = p1.id;
        h->date.day = p1.date.day;
        h->date.month = p1.date.month;
        h->date.year = p1.date.year;
        strcpy(h->name,p1.name);
        h->price = p1.price;
        h->quantity = p1.quantity;
        h->type = p1.type;
        h->limit = p1.limit;
        h->next = NULL;
        head2 = h;
    }
    else{
        while(h->next != NULL)
        h =h->next;

        h->next = (struct product*)malloc(sizeof(struct product));
        h->next->id = p1.id;
        h->next->date.day = p1.date.day;
        h->next->date.month = p1.date.month;
        h->next->date.year = p1.date.year;
        strcpy(h->next->name,p1.name);
        h->next->price = p1.price;
        h->next->quantity = p1.quantity;
        h->next->type = p1.type;
        h->next->limit = p1.limit;
        h->next->next = NULL;
    }
    }
    fclose(fp);
}

void order_details::menu(){
    product_detail obj;
    cleardevice();
    vector<string> LIST{"(1) Process Order",
    "(2) Order History",
    "(3) Serch Order",
    "(4) Return",
  };

while (1) {
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

        case VIEW:{
            obj.display(head);
            }
            break;
        
		case RETURN:{
          j= 0;
          p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    
          MAX_UP = 138 + (30*0);
          MAX_DOWN = 138 + (30*(LIST.size()-1));
		  break;
        }

        case keys::escape :{
            return;
            break;
        }

	}
    cleardevice();

  }
  
   switch(I+1){
        case 1: {
        int wid = getcurrentwindow();
        final = 0;
        process_order(1);
        obj.writedata(head);
        setcurrentwindow(wid);
        }
        break;
        case 2:{ 
        int wid = getcurrentwindow();
        read_order(wid);
        setcurrentwindow(wid);
        }
        break;
        case 3:{ 
        int wid = getcurrentwindow();    
        search_order();
        setcurrentwindow(wid);
        }
        break;
        case 4: {
        return;
        }
    }
    cleardevice();
}
}


void order_details::billing(){

    cleardevice();

  int j = 1;
  char ch;
  long long int s = 0;
  string temp;

  while(j){
    bgiout<<"Enter Phone Number Or Order ID : "<<temp;
    outstreamxy(100,100);
    ch = getch();

    switch(ch){
       
       case RETURN :{
        j = 0;
       }
       break;

       case pp::backspace:{
         if(temp.length() > 0){
            temp.pop_back();
            s = s/10;
         }
       }
       break;

       case VIEW:{
        obj.display(head);
        }
        break;

       default:{
         if(int(ch) >= 48 && int(ch) <= 57){
            temp = temp + ch;
            s = s*10 + int(ch) - 48;
         }
       }
       break;

    }
   
    cleardevice();
  }  


  int wid = initwindow(1200,getmaxheight(),"Order summuary");
    settextstyle(8,0,1);
	setcolor(LIGHTGRAY);
	outtextxy((getmaxwidth()/2)-230,5,"Order Summary");
	line(0,35,1200,35);
	line(0,getmaxheight()-50,1200,getmaxheight()-50);
    outtextxy(700,getmaxheight()-30,"Press right(->) arrow key to change page");

   FILE *fp = fopen("order_history.bin", "rb");
   order pd;
   it ii;
   int TOP = 35;
   int run = 1;
   int notfound = 1;
   while(fread(&pd,sizeof(order),1,fp) && run == 1){
      if(pd.ccontact == s || pd.orderid == s){
      notfound = 0;
      run = 0;
      TOP += 5;
      bgiout<<"Date : "<<pd.dt.day<<"/"<<pd.dt.month<<"/"<<pd.dt.year;
      outstreamxy(30,TOP);
      bgiout<<pd.dt.tm_hour<<":"<<pd.dt.tm_min<<":"<<pd.dt.tm_min;
      outstreamxy(getmaxwidth()/2-230,TOP);
      bgiout<<"Contact No. : "<<pd.ccontact;
      outstreamxy(900,TOP);
      TOP+=30;
      bgiout<<"Email : "<<pd.email;
      outstreamxy(30,TOP);
      bgiout<<"Order ID : "<<pd.orderid;
      outstreamxy(900,TOP);
      TOP+=50;

      outtextxy(200,TOP,"Name");
      outtextxy(400,TOP,"Quantity");
      outtextxy(500,TOP,"price");
      outtextxy(600,TOP,"Total");
      TOP+=10;

      for (int i = 0; i < pd.totalitems; i++){
      fread(&ii,sizeof(it),1,fp);
      TOP+=30;
      bgiout<<"("<<i+1<<") "<<ii.name;
      outstreamxy(170,TOP);
      bgiout<<ii.quantity;
      outstreamxy(400,TOP);
      bgiout<<ii.price;
      outstreamxy(500,TOP);
      bgiout<<ii.total;
      outstreamxy(600,TOP);
     }
     TOP+=5;
     TOP+=30;
     line(0,TOP,1200,TOP);
     TOP+=30;
     bgiout<<"GST(12%) : "<<pd.tax;
     outstreamxy(30,TOP);
     bgiout<<"Total Bill : "<<pd.final;
     outstreamxy(500,TOP);
     TOP+=35;
     line(0,TOP,1200,TOP);
    string filename = to_string(pd.orderid)+".doc";
    fstream f;
    f.open(filename);
    if(!f){
    f.open(filename,ios::out);
    f<<endl;
    for (int i = 0; i < 75; i++)
    {
        f<<"_";
    }
    f<<endl;
    f<<pd.dt.day<<"/"<<pd.dt.month<<"/"<<pd.dt.year<<"                                                                                          "<<pd.dt.tm_hour<<":"<<pd.dt.tm_min<<":"<<pd.dt.tm_sec<<endl;
    f<<"Order ID : #"<<pd.orderid<<"\t";
    f<<endl;f<<endl; 
    
    for (int i = 0; i < pd.totalitems; i++){
        fread(&ii,sizeof(it),1,fp);
        f<<"("<<i+1<<") "<<ii.name<<"\t"<<ii.quantity<<"\t"<<ii.price<<"\t"<<ii.total<<endl;
    }
    }
    f.close();
    }

    for (int i = 0; i < pd.totalitems; i++)
      fread(&ii,sizeof(it),1,fp);
   }
     fclose(fp);

    if(notfound){
        outtextxy(100,100,"Record Not Exist!");
    }
    getch();
    closegraph(wid);

}
