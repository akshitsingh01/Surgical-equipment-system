#include<ctime>

void pattern2(int n){
    for (int i = 0; i < n; i++)
    {
        cout<<"_";
    }
    cout<<endl;
}

struct product{
    int id;
    char name[50];
    float price;
    int quantity;
    int type;
    int limit;
    struct dt{
        int day;
        int month;
        int year;
    }date;
    struct product *next;   
}product;

int convertid(char select[]){
    
    map<char,int> map{
        {'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},
        {'6',6},{'7',7},{'8',8},{'9',9}
    };
    int result = 0;
    int i = 1;
    while(select[i] != '\0' && select[1] != 0){
    
      result =(result*10)+map[select[i]];
      i++;
    }
    return result;
}

vector<string>type;


struct product *head; 
class product_detail{
    public:
    animate anime;
    void addproduct(struct product*);
    void readdata(struct product*);
    void writedata(struct product*);
    void display(struct product*);
    void search(struct product *);
    void modify(struct product*);
    struct product* removedata(struct product*);
    void menu(int );
    int getid(struct product *);
    void out_of_stock(struct product *);
    void add_stock(struct product *);
    struct product *searchbool(struct product *h,int id,char *select,bool check);
    void add_category();
    void read_category();
    void delete_category(int );
};

struct product* product_detail::removedata(struct product *head){

    char name[30],ch;
    int nm = 1;
    string temp ;
    int id;
    bool found = 0;
    cleardevice();
    int window = getcurrentwindow();
    display(head);
    setcurrentwindow(window);

    while (nm)
    {
        bgiout<<"Enter Product name : "<<temp;
        outstreamxy(100,100);
        ch = getch();

        switch (ch){
        case RETURN:{
            strcpy(name,temp.c_str());
            nm = 0;
        }
         break;

        case pp::backspace : {
            if(temp.length() > 0)
            temp.pop_back();
        }
        break;

        case keys::escape:{
            return head;
        }
        break;

        case VIEW:{
        display(head);
        }
        break;
        
        default:{
           temp = temp + ch;
        }
        break;
        }
        cleardevice();
    }

    cleardevice();

    struct product *h = head;
    struct product *ptr;

    // if(strcmp(h->name,name)==0){
        
    //     ptr = h;
    //     h = h -> next;
    //     free(ptr);
    //     outtextxy(100,100,"Entry Removed Sucessfully Press any key to go back");
    //     getch();
    //     cleardevice();
    //     return h;
    // }
    struct product *prev;
 
    // while (h!=NULL){
    //     if(strcmp(h->name,name)==0){
    //         if(h->next==NULL){
    //            ptr = h;
    //            prev->next = NULL;
    //            free(ptr);
    //         }
    //         else{
    //             ptr = h;
    //             prev->next = h->next;
    //             free(ptr);
    //         }
    //         found = 1;
    //     }
    //     prev = h;
    //     h = h->next;
    // }

    while (h!=NULL && !found){
        // if(strcmp(h->name,name)==0){
        if(strcmp(h->name,name)==0){
            
            if(h==head){
                if(h->next == NULL){
                    return NULL;
                }
                else{
                    ptr = h;
                    h = h->next;
                    return h;
                    free(ptr);
                }
            }
            else if(h != head && h->next==NULL){
                ptr = h;
                prev->next = NULL;
                free(ptr);
            }
            else{
                ptr = h;
                prev->next=prev->next->next;
                free(ptr);
            }
           found = 1;
        }
        prev = h;
        h = h->next;
    }
    // }
 
    if(found){
        outtextxy(100,100,"Entry Removed Sucessfully Press any key to go back");
    }
    else{
    outtextxy(100,100,"Product not found Press any key to go back");
    }    
    getch();
    cleardevice();
    return head;
}

void product_detail::add_category(){
    cleardevice();
    ofstream fp;

    string category;
    char ch;
    int a = 1;
  
    while(a){

       outtextxy(100,100,"Existing Categories ");
       int TOP = 100; 
       
       for (int i = 0; i < type.size(); i++)
       {
        TOP+=30;
        bgiout<<"("<<i+1<<") "<<type[i];
        outstreamxy(100,TOP);
       }

       TOP+=50;

       bgiout<<"Enter category name : "<<category;
       outstreamxy(100,TOP);

       ch = getch();
       switch (ch){
       case RETURN:
        //   a = 0;
          if(category.length() > 0)
          type.emplace_back(category);
          category.clear();
           
          cleardevice();
        break;
       
       case keys::escape:{
        a = 0;
       }
       break;

       case pp::backspace :{

        if(category.length() > 0){
        category.pop_back();
        cleardevice();
        }
       }
       break;

       case VIEW:{
        display(head);
        }
        break;
       
       default:
       category = category + ch;
        break;
       }
       
    }

    fp.open("categories.txt",ios::out);
        for (int i = 0; i < type.size(); i++){
           fp<<type[i]<<endl;
    }
        fp.close();
        return;
    cleardevice();
 
}

void product_detail::read_category(){
     
    ifstream fp;
    fp.open("categories.txt");
    string temp;
    type.clear();
    while(getline(fp,temp)){
        type.emplace_back(temp);
    }
    fp.close();
}

void product_detail::delete_category(int wid){
    char TP[100];
    int j = 1;

    char ch;

    int p1, p2, p3, p4, p5, p6;
	p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    int px;
    int I = 0;
while(true){
    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(type.size()-1));

while(j){

    px = 130;
   read_category();     
   outtextxy(100,100,"Select Category : ");
   for (int i = 0; i < type.size(); i++)
   {
    strcpy(TP,type[i].c_str());
     bgiout<<"("<<i+1<<")";
    outstreamxy(100,px);
    outtextxy(140,px,TP);
    px =px+ 30;
   }
      p1 = 100 + (type[I].length()*20) + 20;
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
		switch (ch)
		{
		case KEY_UP:
		{
			if(p2 > MAX_UP){
			p2 -= 5, p4 -= 5, p6 -= 5;
            I--;
            }
			break;
		}

		case KEY_DOWN:
		{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            }
			break;
		}
        
		case RETURN:
		{
          char C;
          int k = 1;
          
          int wid4 = initwindow(400,100,"Confirmation Box");
          setcurrentwindow(wid4);
          outtextxy(10,10,"Are you Sure you want to delete this category ? ") ;
          outtextxy(10,40,"Press enter to continue and esc to cancel");
          while(k){
          closegraph(C = getch());
          if(C==RETURN ||C==keys::escape){ 
            closegraph(wid4);
            k = 0;
        }
        }
          setcurrentwindow(wid);
          p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
          if(C==RETURN){
		  ofstream fp;
          fp.open("categories.txt",ios::out);
          for (int i = 0; i < type.size(); i++){
          if (i!=I){
          fp<<type[i]<<endl;
          }
          }
          read_category();
        
          MAX_UP = 138 + (30*0);
          MAX_DOWN = 138 + (30*(type.size()-1));
          I = 0;
          fp.close();
          }
        break;
		}

        case keys::escape :{
            // closegraph(wid3);
            cleardevice();
            return;
            break;
        }

        case VIEW:{
        display(head);
        }
        break;

		}
		clearviewport();
	}
    clearviewport();
}
}

void product_detail::addproduct(struct product *h){
    cleardevice();
    int id,quantity = 0,limit = 0;
    int day,month,year;
    char name[30];
    float price = 0;
    int t;
   
   char TP[100];
    int j = 1;

    char ch;

    int p1, p2, p3, p4, p5, p6;
	p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    int px;
    int I = 0;

    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(type.size()-1));

while(j){

    px = 130;
   read_category();     
   outtextxy(100,100,"Select Product Type : ");
   for (int i = 0; i < type.size(); i++)
   {
    strcpy(TP,type[i].c_str());
     bgiout<<"("<<i+1<<")";
    outstreamxy(100,px);
    outtextxy(140,px,TP);
    px =px+ 30;
   }
      p1 = 100 + (type[I].length()*20) + 20;
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
		switch (ch)
		{
		case KEY_UP:
		{
			if(p2 > MAX_UP){
			p2 -= 5, p4 -= 5, p6 -= 5;
            I--;
            }
			break;
		}

		case KEY_DOWN:
		{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            }
			break;
		}
        
		case RETURN:
		{
          t = I+1;
          j = 0;
        break;
		}

        case VIEW:{
        display(head);
        }
        break;

        case keys::escape :{
            cleardevice();
            return;
        }

		}
		cleardevice();
	}

    cleardevice();

    id = getid(head);

    time_t now = time(NULL);
    tm * ltm = localtime(&now);
    day = ltm->tm_mday;
    month = ltm->tm_mon+1;
    year = ltm->tm_year+1900;
    

    int nm = 1;
    string temp;
    while(nm){
        bgiout<<"Enter Equipment Name : "<<temp;
        outstreamxy(100,100);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            nm = 0;
            strcpy(name,temp.c_str());
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0)
            temp.pop_back();
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;

        case VIEW:{
        display(head);
        }
        break;    
        
        default:
            temp = temp + ch;
            break;
        }
        cleardevice();
    }
    
    nm = 1;
    temp.clear();
    int point = 0;

    while(nm){
        bgiout<<"Enter Equipment Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Enter Price : "<<temp;
        outstreamxy(100,130);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            if(temp[temp.length()-1]=='.'){
                point = 0;
            }
            temp.pop_back();
            }
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;  

        case VIEW:{
        display(head);
        }
        break;  
        
        default:{
            if(int(ch) >= 48 && int(ch) <= 57){
            temp = temp + ch;
            }
            if(ch=='.' && point == 0){
              point = 1;
              temp = temp +'.';
            }
            
        }
            break;
        }
        cleardevice();
    }

    int num = 0,f = 0;
    point = 0;

    for (int i = 0; i < temp.length(); i++)
    {
        if(temp[i] != '.'){
        num  = int(temp[i]) - 48;
        price = (price * 10) + num;
        }

        if(point) f+=1;

        if(temp[i] == '.')
        point = 1;
    }
    
    price = price/pow(10,f);
    
    nm = 1;
    temp.clear();

     while(nm){
        bgiout<<"Enter Equipment Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Enter Price : "<<price;
        outstreamxy(100,130);
        bgiout<<"Enter Quantity : "<<temp;
        outstreamxy(100,160);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            temp.pop_back();
            quantity = quantity/10;
            }

        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break; 

        case VIEW:{
        display(head);
        }
        break;   
        
        default:{
        if(int(ch) >= 48 && int(ch) <= 57){
        temp = temp + ch;
        quantity = (quantity *(10)) +(int(ch) - 48);
        }
        }
        break;

        }
        cleardevice();
    }

    nm = 1;
    temp.clear();

    while(nm){
        bgiout<<"Enter Equipment Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Enter Price : "<<price;
        outstreamxy(100,130);
        bgiout<<"Enter quantity : "<<quantity;
        outstreamxy(100,160);
        bgiout<<"Enter Minimum Stock Limit : "<<temp;
        outstreamxy(100,190);
        ch = getch();
        switch (ch){
        case RETURN:{
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            temp.pop_back();
            limit = limit/10;
            }
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;  

        case VIEW:{
        display(head);
        }
        break;  
        
        default:{
            if(int(ch) >= 48 && int(ch) <= 57){
            temp = temp + ch;
            limit = (limit *10) +(int(ch) - 48);
            }
        }
            break;
        }
        cleardevice();
    }
    int currwindow = getcurrentwindow();
    int wid = initwindow(400,100,"Message Box");
    outtextxy(30,40,"Are you sure you want to confirm ?");
    outtextxy(30,70,"Press enter to confirm or esc to return");
    
    nm = 1;
    while(nm){
    ch = getch();
    if(ch==RETURN){
        nm = 0;
        setcurrentwindow(currwindow);
        closegraph(wid);
    }
    else if(ch == keys::escape){
        setcurrentwindow(currwindow);
        closegraph(wid);
        return;
    }
    }

    if(h==NULL){
        head = (struct product*)malloc(sizeof(struct product));
        head->date.day = day;
        head->date.month = month;
        head->date.year = year;
        head->id = id;
        strcpy(head->name,name);
        head->price = price;
        head->quantity = quantity;
        head->limit = limit;
        head->type = t-1;
        head->next = NULL;
    }
    else{
        while(h->next != NULL)
        h =h->next;

        h->next = (struct product*)malloc(sizeof(struct product));
        h->next->date.day = day;
        h->next->date.month = month;
        h->next->date.year = year;
        h->next->id = id;
        strcpy(h->next->name,name);
        h->next->price = price;
        h->next->quantity = quantity;
        h->next->type = t-1;
        h->next->limit = limit;
        h->next->next = NULL;
    }
}


void product_detail::display(struct product *h){
        int curr = getcurrentwindow();
        int widdisplay = initwindow(1200,getmaxheight(),"List Equipments");
        // settextstyle(3,0,1);  
        setcolor(WHITE);  
        int y1 = 25;
	    int y2 = 50;

        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);
        setcolor(LIGHTGREEN);
        outtextxy(20,y1+5,"DATE");
	    outtextxy(110,y1+5,"ID");
	    outtextxy(160,y1+5,"TYPE");
	    outtextxy(460,y1+5,"PRICE");
	    outtextxy(550,y1+5,"QTY.");
	    outtextxy(640,y1+5,"TYPE");
	    outtextxy(940,y1+5,"M.S.T");

        int x, y;

    
    while(h!=NULL){
        setcolor(WHITE);
        y1 = y1+25;
	    y2 = y2+25;
        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);
        if(h->quantity <= h->limit){
        setcolor(LIGHTRED);
        bgiout<<h->date.day<<"/"<<h->date.month<<"/"<<h->date.year;
        outstreamxy(30,y1+5);
        bgiout<<h->id;
        outstreamxy(110,y1+5);
        bgiout<<h->name;
        outstreamxy(160,y1+5);
        bgiout<<h->price;
        outstreamxy(460,y1+5);
        bgiout<<h->quantity;
        outstreamxy(550,y1+5);
        bgiout<<type[h->type];
        outstreamxy(640,y1+5);
        bgiout<<h->limit;
        outstreamxy(940,y1+5);
        setcolor(LIGHTGREEN);

        }
        else{
        setcolor(LIGHTGREEN);
        bgiout<<h->date.day<<"/"<<h->date.month<<"/"<<h->date.year;
        outstreamxy(30,y1+5);
        bgiout<<h->id;
        outstreamxy(110,y1+5);
        bgiout<<h->name;
        outstreamxy(160,y1+5);
        bgiout<<h->price;
        outstreamxy(460,y1+5);
        bgiout<<h->quantity;
        outstreamxy(550,y1+5);
        bgiout<<type[h->type];
        outstreamxy(640,y1+5);
        bgiout<<h->limit;
        outstreamxy(940,y1+5);
        }

        h =h->next;
    }
    getch();
    closegraph(widdisplay);
    setcurrentwindow(curr);
    return;
    // pattern2(120);
    // system("pause");
}

void product_detail::writedata(struct product *h){

    FILE *fp = fopen("Product_details.bin","wb");
    
    while(h!=NULL){
        fwrite(h,sizeof(product),1,fp);
        h = h->next;
    }

    fclose(fp);
 
}

void product_detail::readdata(struct product *h){

    struct product p1;
    FILE *fp = fopen("Product_details.bin","rb");
    

    while (fread(&p1,sizeof(product),1,fp))
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
        head = h;

    }
    else{
        while(h->next != NULL)
        h =h->next;
        
        h->next = (struct product*)malloc(sizeof(product));
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

void product_detail::search(struct product *h){
    char name[30];
    int pk = 1;
    int j = 0;
    char a;
    string n;
int wid = getcurrentwindow();
    while(pk){

        bgiout<<"Enter product name : ";
        for(int i = 0;i <= j;i++){
        bgiout<<n;
        }
        outstreamxy(100,100);


        a = getch();

        switch (a){
        case RETURN:{
            strcpy(name,n.c_str());
            pk = 0;
            break;
        }

        case pp::backspace :{
            if (n.length() > 0)
            {
              n.pop_back();
            }
            break;
        }

        case VIEW:{
        display(head);
        }
        break;
        
        default:
           n = n+a;
           break;
        }

        cleardevice();
    }

    bool notfound = 1;

    int wid5 = initwindow(1200,200, "Equipment Data Management::Search");
	       int x = 20;
	       settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	       outtextxy(20, 20, "SEARCHING,PLEASE WAIT");
           setfillstyle(SOLID_FILL,MAGENTA);

	       for (int i = 0; i < 250; ++i)
	       {   
		       if(i <= 150)
		       delay(5);
               else delay(10);

		       int vert[] = {x, 70, x, 70, x,75, x, 70};
		
		       drawpoly(4, vert);
		       fillpoly(4, vert);
		       x++;
	       }
           cleardevice();

        setcolor(LIGHTGREEN);  

    while (h!= NULL){
        if(strcmp(h->name,name)==0){
        clearviewport();
        notfound = 0;

        int y1 = 25;
	    int y2 = 50;

        for(int i = 0;i < 2;i++){
        setcolor(WHITE);
        int box1[] = {15,y1,130,y1,130,y2,15,y2,15,y1};
	    int box2[] = {130,y1,180,y1,180,y2,130,y2,130,y1};
	    int box3[] = {180,y1,480,y1,480,y2,180,y2,180,y1};
	    int box4[] = {480,y1,570,y1,570,y2,480,y2,480,y1};
	    int box5[] = {570,y1,660,y1,660,y2,570,y2,570,y1};
	    int box6[] = {660,y1,1060,y1,1060,y2,660,y2,660,y1};
	    int box7[] = {1060,y1,1150,y1,1150,y2,1060,y2,1060,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);
        y1 = y1+25;
	    y2 = y2+25;
        }
        y1 = 25;
	    y2 = 50;
        settextstyle(8,0,1);
        setcolor(LIGHTGREEN);
        outtextxy(20,y1+5,"DATE");
	    outtextxy(135,y1+5,"ID");
	    outtextxy(185,y1+5,"TYPE");
	    outtextxy(485,y1+5,"PRICE");
	    outtextxy(575,y1+5,"QTY.");
	    outtextxy(665,y1+5,"TYPE");
	    outtextxy(1065,y1+5,"M.S.T");
        
        y1 = y1 + 25;
        y2 = y2 + 25;

        if(h->quantity <= h->limit)
        setcolor(LIGHTRED);
        else setcolor(LIGHTGREEN);
        bgiout<<h->date.day<<"/"<<h->date.month<<"/"<<h->date.year;
        outstreamxy(20,y1+5);
        bgiout<<h->id;
        outstreamxy(135,y1+5);
        bgiout<<h->name;
        outstreamxy(185,y1+5);
        bgiout<<h->price;
        outstreamxy(485,y1+5);
        bgiout<<h->quantity;
        outstreamxy(575,y1+5);
        bgiout<<type[h->type];
        outstreamxy(665,y1+5);
        bgiout<<h->limit;
        outstreamxy(1065,y1+5);
        setcolor(LIGHTGREEN);
        break;
        }
        h=h->next;
    }
    if(notfound){
        outtextxy(100,100,"Sorry Result Not Found ,or Check Product Name");
    }
    getch();
    closegraph(wid5);
    return;
}

void product_detail::modify(struct product *h){
    char name[30],ch;
    int nm = 1;
    string temp ;
    bool notfound = 1;
    cleardevice();

    while (nm)
    {
        bgiout<<"Enter Product name : "<<temp;
        outstreamxy(100,100);
        ch = getch();

        switch (ch){
        case RETURN:{
            strcpy(name,temp.c_str());
            nm = 0;
            break;
        }

        case pp::backspace : {
            if(temp.length() > 0)
            temp.pop_back();
            break;
        }

        case keys::escape:{
            return;
            break;
        }

        case VIEW:{
        display(head);
        break;
        }
        
        default:{
           temp = temp + ch;
           break;
        }
        }
        cleardevice();
    }
    
    temp.clear();
    cleardevice();

    while (h!= NULL){
    if(strcmp(h->name,name)==0){
    notfound = 0;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    h->date.day = ltm->tm_mday;
    h->date.month = ltm->tm_mon+1;
    h->date.year = ltm->tm_year+1900;
    int j = 1;

    char TP[30];
    int p1, p2, p3, p4, p5, p6;
	p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    int px;
    int I = 0;

    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(type.size()-1));

while(j){

    px = 130;
   read_category();     
   outtextxy(100,100,"Select Product Type : ");
   for (int i = 0; i < type.size(); i++)
   {
    strcpy(TP,type[i].c_str());
     bgiout<<"("<<i+1<<")";
    outstreamxy(100,px);
    outtextxy(140,px,TP);
    px =px+ 30;
   }
      p1 = 100 + (type[I].length()*20) + 20;
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
		switch (ch)
		{
		case KEY_UP:
		{
			if(p2 > MAX_UP){
			p2 -= 5, p4 -= 5, p6 -= 5;
            I--;
            }
			break;
		}

		case KEY_DOWN:
		{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            }
			break;
		}
        
		case RETURN:
		{
          h->type = I;
          j = 0;
        break;
		}

        case VIEW:{
        display(head);
        }
        break;

        case keys::escape :{
            cleardevice();
            return;
        }

		}
		cleardevice();
	}

    cleardevice();
    nm = 1;
    while(nm){
        bgiout<<"Enter Equipment New Name : "<<temp;
        outstreamxy(100,100);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            nm = 0;
            strcpy(h->name,temp.c_str());
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0)
            temp.pop_back();
        }
        break;

        case VIEW:{
        display(head);
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;    
        
        default:
            temp = temp + ch;
            break;
        }
        cleardevice();
    }
    
    nm = 1;
    temp.clear();
    int point = 0;
    int quantity = 0,limit = 0;
    float price = 0;

     while(nm){
        bgiout<<"Equipment New Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Enter New Price : "<<temp;
        outstreamxy(100,130);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            if(temp[temp.length()-1]=='.'){
                point = 0;
            }
            temp.pop_back();
            }
        }
        break;

        case VIEW:{
        display(head);
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;    
        
        default:{
            if(int(ch) >= 48 && int(ch) <= 57){
            temp = temp + ch;
            }
            if(ch=='.' && point == 0){
              point = 1;
              temp = temp +'.';
            }
            
        }
            break;
        }
        cleardevice();
    }

    int num = 0,f = 0;
    point = 0;

    for (int i = 0; i < temp.length(); i++)
    {
        if(temp[i] != '.'){
        num  = int(temp[i]) - 48;
        price = (price * 10) + num;
        }

        if(point) f+=1;

        if(temp[i] == '.')
        point = 1;
    }
    
    price = price/pow(10,f);
    h->price = price;

    nm = 1;
    temp.clear();

     while(nm){
        bgiout<<"Equipment Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Price : "<<price;
        outstreamxy(100,130);
        bgiout<<"Enter Quantity : "<<temp;
        outstreamxy(100,160);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            h->quantity = quantity;
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            temp.pop_back();
            quantity = quantity/10;
            }
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break;   

        case VIEW:{
        display(head);
        }
        break; 
        
        default:{
        if(int(ch) >= 48 && int(ch) <= 57){
        temp = temp + ch;
        quantity = (quantity *(10)) +(int(ch) - 48);
        }
        }
        break;

        }
        cleardevice();
    }

    nm = 1;
    temp.clear();

     while(nm){
        bgiout<<"Equipment Name : "<<name;
        outstreamxy(100,100);
        bgiout<<"Price : "<<price;
        outstreamxy(100,130);
        bgiout<<"Quantity : "<<quantity;
        outstreamxy(100,160);
        bgiout<<"Enter Minimum stock limit : "<<temp;
        outstreamxy(100,190);
        ch = getch();
        switch (ch)
        {
        case RETURN:{
            h->limit = limit;
            nm = 0;
        }
        break;

        case pp::backspace:{
            if(temp.length() > 0){
            temp.pop_back();
            limit = limit/10;
            }
        }
        break;

        case keys::escape : {
            cleardevice();
            return;
        }
        break; 

        case VIEW:{
        display(head);
        }
        break;   
        
        default:{
        if(int(ch) >= 48 && int(ch) <= 57){
        temp = temp + ch;
        limit = (limit *(10)) +(int(ch) - 48);
        }
        }
        break;

        }
        cleardevice();
    }

    int currwindow = getcurrentwindow();
    int wid = initwindow(400,100,"Message Box");
    outtextxy(30,40,"Are you sure you want to confirm ?");
    outtextxy(30,70,"Press enter to confirm or esc to return");
    
    nm = 1;
    while(nm){
    ch = getch();
    if(ch==RETURN){
        nm = 0;
        setcurrentwindow(currwindow);
        closegraph(wid);
    }
    else if(ch == keys::escape){
        setcurrentwindow(currwindow);
        closegraph(wid);
        return;
    }
    }

    }
    h =h->next;
}


if(notfound){
    setcolor(RED);
    outtextxy(100,100,"Wrong Product Name Press Enter");
    getch();
    setcolor(LIGHTBLUE);
}
cleardevice();
}

int product_detail::getid(struct product* h){
    struct product *fast = h;
    struct product *slow = h;

  if(h==NULL){
    return 1;
  } 
  else{
   while(fast->next!=NULL){
    slow = slow->next;
    fast = fast->next;
    if(fast->next!=NULL)
    fast = fast->next;
   }
}
   int id = fast->id+1;
 return id;

}

void product_detail::menu(int window){

    vector<string> LIST{"(1) Add Equipment Or Kit",
  "(2) Update",
  "(3) Search Equipment",
  "(4) Remove Equipment Entry",
  "(5) Return"
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

        case VIEW:{
        display(head);
        }
        break;

	}
    cleardevice();

  }
  
   switch(I+1){
            case 1 :{
            addproduct(head);
            writedata(head);
            }
            break;

            case 2:{
            modify(head);
            writedata(head);
            break;
            }
            
            case 3:{
            int currwid = getcurrentwindow();
            search(head);
            setcurrentwindow(currwid);
            }
            break;

            case 4:{
            // int currwid = getcurrentwindow();
            struct product * ptr = removedata(head);
            writedata(ptr);
            head = NULL;
            readdata(head);
            // setcurrentwindow(currwid);
            }
            break;

            case 5:
            return;
            break;
        }
    cleardevice();
}

}
void product_detail::out_of_stock(struct product *h){
   int currwindow = getcurrentwindow();
   int widdisplay = initwindow(1200,getmaxheight(),"List Equipments");  
        setcolor(LIGHTGREEN);  
        int y1 = 25;
	    int y2 = 50;

        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);

        outtextxy(20,y1+5,"DATE");
	    outtextxy(110,y1+5,"ID");
	    outtextxy(160,y1+5,"TYPE");
	    outtextxy(460,y1+5,"PRICE");
	    outtextxy(550,y1+5,"QTY.");
	    outtextxy(640,y1+5,"TYPE");
	    outtextxy(940,y1+5,"M.S.T");

        int x, y;

    
    while(h!=NULL){
        
        if(h->quantity <= h->limit){

        y1 = y1+25;
	    y2 = y2+25;
        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);
        setcolor(LIGHTRED);

        bgiout<<h->date.day<<"/"<<h->date.month<<"/"<<h->date.year;
        outstreamxy(30,y1+5);
        bgiout<<h->id;
        outstreamxy(110,y1+5);
        bgiout<<h->name;
        outstreamxy(160,y1+5);
        bgiout<<h->price;
        outstreamxy(460,y1+5);
        bgiout<<h->quantity;
        outstreamxy(550,y1+5);
        bgiout<<type[h->type];
        outstreamxy(640,y1+5);
        bgiout<<h->limit;
        outstreamxy(940,y1+5);
        setcolor(LIGHTGREEN);

        }

        h =h->next;
    }
    getch();
    closegraph(widdisplay);
    setcurrentwindow(currwindow);
}


void product_detail::add_stock(struct product *h){

    char val[30],ch;
    int nm = 1;
    string temp ;
    int id;
    bool found = 0;
    cleardevice();
    int window = getcurrentwindow();
    display(head);
    setcurrentwindow(window);

    while (nm){
        bgiout<<"Enter Equipment ID with first character (+) or enter the name directly : "<<temp;
        outstreamxy(100,100);
        ch = getch();

        switch (ch){
        case RETURN:{
            strcpy(val,temp.c_str());
            nm = 0;
        }
         break;

        case pp::backspace : {
            if(temp.length() > 0)
            temp.pop_back();
        }
        break;

        case keys::escape:{
            return;
        }
        break;

        case VIEW:{
        display(head);
        }
        break;
        
        default:{
           temp = temp + ch;
        }
        break;
    }
        cleardevice();
    }

    cleardevice();
    // while (1)
    // {

            if(val[0]=='+'){
            id = convertid(val);
            while (h->id!=id && h!=NULL)
            h = h->next;
            }
            else{
            while (strcmp(h->name,val)!=0 && h!=NULL)
            h = h->next;
            }

            if(h==NULL){
            return;
            }
            else{
            temp.clear();
            nm = 1;
            int q = 0;

           while (nm){
           bgiout<<"Enter Quantity : "<<temp;
           outstreamxy(100,100);
           ch = getch();

           switch (ch){
           case RETURN:{
               strcpy(val,temp.c_str());
               nm = 0;
           }
            break;

           case pp::backspace : {
               if(temp.length() > 0)
               temp.pop_back();
           }
           break;

           case keys::escape:{
               return;
           }
           break;

        case VIEW:{
        display(head);
        }
        break;
        
           default:{
              if(int(ch) >= 48 && int(ch) <= 57){
               temp = temp + ch;
               q =(q * 10) + int(ch) - 48;
              }
           }
           break;
           }
           cleardevice();
       }
            h->quantity = q+h->quantity;
    }   

    cleardevice();
}

struct product* product_detail::searchbool(struct product *h,int id,char *select,bool check){

    if(check){
        while(h!=NULL){
           if(h->id==id) {
            return h;
           }
           h=h->next;
        }
    }
    else{
        while(h!=NULL){
           if(strcmp(h->name,select)==0) {
           return h;
           }
           h = h->next;
        }
    }
    return NULL;
}

class sorting{
   public:
   animate anime;
   struct product *temp_head = NULL;
   product_detail obj;
   void menu();
   void sort_by_type(struct product *,product_detail );
   struct product* sort_a_z(struct product *,product_detail );
   struct product* merge(struct product* ,struct product* );
   struct product* findmid(struct product *);
//    void display(product *,product_detail);
   struct product* sort_z_a(struct product *,product_detail );
   struct product* merge_rev(struct product *,struct product*); 
   void decreasing_id(struct product*);
   struct product* create_copy(struct product *);
};

struct product* sorting::create_copy(struct product *ptr){

 struct  product *ans = new struct product;
 struct  product *temp = new struct product;
  ans = temp; 
  while(ptr!= NULL){
    temp->next = new struct product();
    temp->next->id = ptr->id;
    temp->next->limit = ptr->limit;
    temp->next->price = ptr->price;
    temp->next->quantity = ptr->quantity;
    temp->next->type = ptr->type;
    strcpy(temp->next->name , ptr->name);
    temp->next->date.day = ptr->date.day;
    temp->next->date.month = ptr->date.month;
    temp->next->date.year = ptr->date.year;
    temp->next->next = NULL;
    temp = temp->next;
    ptr = ptr->next;
  }
    ans = ans->next;
    return ans;
}

void sorting::menu(){

    cleardevice();
    if(temp_head==NULL)temp_head = create_copy(head);

    vector<string> LIST{
    "(1) Display By Type",
    "(2) Display [a-z]",
    "(3) Display [z-a]",
    "(4) Display By Decreasing ID",
    "(5) Return"
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

        case VIEW:{
        obj.display(head);
        }
        break;

	}
    cleardevice();

  }
  
           switch(I+1){
           case 1 : {
           int window = getcurrentwindow();
           sort_by_type(temp_head,obj);
           setcurrentwindow(window);
           break;
           }
           case 2 :{
           struct product*ptr = sort_a_z(temp_head,obj); 
           int window = getcurrentwindow();
           obj.display(ptr);
           setcurrentwindow(window);
           break;
           }

           case 3 :{
           struct product * ptr2 = sort_z_a(temp_head,obj);
        //    display(ptr2,obj);
           int window = getcurrentwindow();
           obj.display(ptr2);
           setcurrentwindow(window);
           break;
           }

           case 4 :{
            decreasing_id(temp_head);
            break;
           }
           case 5 :return;
        }
    cleardevice();
    // setcurrentwindow(currwindow);
}

}

void sorting::sort_by_type(struct product *h,product_detail obj){
    cleardevice();
 while(true){
    char TP[100];
    int j = 1;
    char ch;

    int p1, p2, p3, p4, p5, p6;
	p1 = 450, p2 = 100, p3 = 470, p4 = 80, p5 = 470, p6 = 120;
    int px;
    int I = 0;

    int MAX_UP = 138 + (30*0);
    int MAX_DOWN = 138 + (30*(type.size()-1));

while(j){
    px = 130;
   obj.read_category();     
   outtextxy(100,100,"Select Category : ");
   for (int i = 0; i < type.size(); i++){
    strcpy(TP,type[i].c_str());
     bgiout<<"("<<i+1<<")";
    outstreamxy(100,px);
    outtextxy(140,px,TP);
    px =px+ 30;
   }
      p1 = 100 + (type[I].length()*20) + 20;
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
		switch (ch)
		{
		case KEY_UP:
		{
			if(p2 > MAX_UP){
			p2 -= 5, p4 -= 5, p6 -= 5;
            I--;
            }
			break;
		}

		case KEY_DOWN:
		{
            if(p2 < MAX_DOWN){
			p2 += 5, p4 += 5, p6 += 5;
            I++;
            }
			break;
		}
        
		case RETURN:
		{
        j = 0;
        break;
		}

        case keys::escape :{
            cleardevice();
            return;
            break;
        }

        case VIEW:{
        obj.display(head);
        }
        break;

		}
		clearviewport();
	}

    clearviewport();
   struct product *sbt = head;
   int window = getcurrentwindow();

   int widdisplay = initwindow(1200,getmaxheight(),"List Equipments"); 
        setcolor(LIGHTGREEN);  
        int y1 = 25;
	    int y2 = 50;

        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);

        outtextxy(20,y1+5,"DATE");
	    outtextxy(110,y1+5,"ID");
	    outtextxy(160,y1+5,"TYPE");
	    outtextxy(460,y1+5,"PRICE");
	    outtextxy(550,y1+5,"QTY.");
	    outtextxy(640,y1+5,"TYPE");
	    outtextxy(940,y1+5,"M.S.T");

        int x, y;

    
    while(sbt!=NULL){
        if(sbt->type == I){
        y1 = y1+25;
	    y2 = y2+25;
        int box1[] = {15,y1,105,y1,105,y2,15,y2,15,y1};
	    int box2[] = {105,y1,155,y1,155,y2,105,y2,105,y1};
	    int box3[] = {155,y1,455,y1,455,y2,155,y2,155,y1};
	    int box4[] = {455,y1,545,y1,545,y2,455,y2,455,y1};
	    int box5[] = {545,y1,635,y1,635,y2,545,y2,545,y1};
	    int box6[] = {635,y1,935,y1,935,y2,635,y2,635,y1};
	    int box7[] = {935,y1,1025,y1,1025,y2,935,y2,935,y1};
	    drawpoly(5, box1);
	    drawpoly(5, box2);
	    drawpoly(5, box3);
	    drawpoly(5, box4);
	    drawpoly(5, box5);
        drawpoly(5, box6);
	    drawpoly(5, box7);
        if(sbt->quantity <= sbt->limit){
        setcolor(LIGHTRED);
        bgiout<<sbt->date.day<<"/"<<sbt->date.month<<"/"<<sbt->date.year;
        outstreamxy(30,y1+5);
        bgiout<<sbt->id;
        outstreamxy(110,y1+5);
        bgiout<<sbt->name;
        outstreamxy(160,y1+5);
        bgiout<<sbt->price;
        outstreamxy(460,y1+5);
        bgiout<<sbt->quantity;
        outstreamxy(550,y1+5);
        bgiout<<type[sbt->type];
        outstreamxy(640,y1+5);
        bgiout<<sbt->limit;
        outstreamxy(940,y1+5);
        setcolor(LIGHTGREEN);

        }
        else{

        bgiout<<sbt->date.day<<"/"<<sbt->date.month<<"/"<<sbt->date.year;
        outstreamxy(30,y1+5);
        bgiout<<sbt->id;
        outstreamxy(110,y1+5);
        bgiout<<sbt->name;
        outstreamxy(160,y1+5);
        bgiout<<sbt->price;
        outstreamxy(460,y1+5);
        bgiout<<sbt->quantity;
        outstreamxy(550,y1+5);
        bgiout<<type[sbt->type];
        outstreamxy(640,y1+5);
        bgiout<<sbt->limit;
        outstreamxy(940,y1+5);
        }
    }

        sbt = sbt->next;
    }
    getch();
    setcurrentwindow(window);
    closegraph(widdisplay);
 }
}

struct product* sorting::findmid(struct product *h){
     
    struct product *slow = h;
    struct product *fast = h->next;

    while (!slow->next && (!fast && !fast->next))
    {
       slow = slow->next;
       fast = fast->next->next;
    }
    return slow;
}


struct product* sorting::sort_a_z(struct product* h,product_detail obj){
       
    if(h==NULL || h->next == NULL){
        return h;
    }
   

    struct product *mid = findmid(h);
    struct product *left = h;
    struct product *right = mid->next;
    mid->next = NULL; 

    left = sort_a_z(left,obj);
    right = sort_a_z(right,obj);

    struct product *sorted = merge(left,right);
    temp_head = sorted;
    return sorted; 
}

struct product* sorting::merge(struct product *left,struct product *right){
      
    struct product *ans = new struct product;
    struct product *temp = new struct product;
    ans = temp;
    
    while (left != NULL && right != NULL)
    {
        if(int(left->name[0]) <= int(right->name[0])){
        temp->next = left;
        left = left->next;
        temp = temp->next;
        }
        else{
        temp->next = right;
        right = right->next;
        temp = temp->next;
        }
    }
    
    while (left != NULL)
    {
        temp->next = left;
        left = left->next;
        temp = temp->next;
    }

    while (right != NULL)
    {
        temp->next = right;
        right = right->next;
        temp = temp->next;
    }
   ans = ans->next;
   return ans;
}

struct product *sorting::sort_z_a(struct product *h,product_detail obj){

    if(h==NULL || h->next ==NULL)return h;
    
    struct product *mid = findmid(h);
    struct product *left = h;
    struct product *right = mid->next;
    mid->next = NULL;

    left = sort_z_a(left,obj);
    right = sort_z_a(right,obj);

    struct product *sorted_rev = merge_rev(left,right);
    temp_head = sorted_rev;
    return sorted_rev;
}

struct product *sorting::merge_rev(struct product *left,struct product *right){

   struct product *ans = new struct product;
    struct product *temp = new struct product;
    ans = temp;
    
    while (left != NULL && right != NULL)
    {
        if(int(left->name[0]) >= int(right->name[0])){
        temp->next = left;
        left = left->next;
        temp = temp->next;
        }
        else{
        temp->next = right;
        right = right->next;
        temp = temp->next;
        }
    }
    
    while (left != NULL)
    {
        temp->next = left;
        left = left->next;
        temp = temp->next;
    }

    while (right != NULL)
    {
        temp->next = right;
        right = right->next;
        temp = temp->next;
    }
   ans = ans->next;
   return ans;
    
    
   ans = ans->next;
   return ans;
}

void sorting::decreasing_id(struct product *h){

   h = create_copy(head);
   product_detail obj;
   struct product *curr = h;
   struct product *forward =NULL;
   struct product *prev = NULL;

   while (curr!=NULL)
   {
       forward = curr->next;
       curr->next = prev;
       prev = curr;
       curr = forward;
   }
   temp_head = prev;
    // obj.display(prev);
    int window = getcurrentwindow();
    obj.display(prev);
    setcurrentwindow(window);
}