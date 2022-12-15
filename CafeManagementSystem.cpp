// CAFE MANAGEMENT SYSTEM by HET B. PATEL

#include<bits/stdc++.h>
using namespace std;

struct node
{
    string name;
    int quantity, data;
    float price;
    node* prev;
    node* next;
};

node* headc = NULL, *tailc = NULL;
node* heada = NULL, *taila = NULL;
node* head_s;

void create_adm(struct node* head, int data, string name, float price)
{
    node* newnode = new node();

    newnode->data = data;
    newnode->price = price;
    newnode->quantity=0;
    newnode->name=name;
    newnode->next=NULL;
    newnode->prev=NULL;

    node* temp=head;

    if(temp==NULL)
    {
        heada = taila = newnode;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
        newnode->prev = temp;
        taila = newnode;
    }
}

void create_cust(struct node* head, int data, int quantity)
{
    node* newnode = new node();

    node* temp1 = heada;
    int flag = 0;
    while(temp1->next!=NULL && temp1->data!=data)
    {
        temp1 = temp1->next;
    }
    if(temp1->data==data)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        newnode->name=temp1->name;
        newnode->next = NULL;
        newnode->prev = NULL;

        node* temp = head;

        if(temp==NULL)
        {
            headc=tailc=newnode;
        }
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        cout<<"\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
}

void disp_list(struct node* head)
{
    node* temp = head;
    if(temp==NULL)
    {
        cout<<"\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }
    else
    {
        cout<<"\n";
        while(temp!=NULL)
        {
            if(temp->quantity==0)
            {
                cout<<"\t\t\t\t\t\t\t"<<temp->data<<"\t"<<temp->name<<"\t"<<temp->price<<"\n";                
            }
            else
            {
                cout<<"\t\t\t\t\t\t\t"<<temp->data<<"\t"<<temp->name<<"\t"<<temp->quantity<<"\t\t"<<temp->price<<"\n";
            }
            temp = temp->next;
        }
        cout<<"\n";
    }
}

void tot_sales(int data, int quantity)
{
    node* newnode = new node();

    node* temp1 = heada;
    while(temp1->data!=data)
    {
        temp1=temp1->next;
    }
    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    newnode->name=temp1->name;
    newnode->next = NULL;
    newnode->prev = NULL;

    node* temp = head_s;

    if(temp==NULL)
    {
        head_s = newnode;
    }
    else
    {
        while(temp->next!=NULL && temp->data!=data)
        {
            temp=temp->next;
        }
        if(temp->data==data)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
            newnode->prev=temp;
        }
    }
}

void calc_tot_sales()
{
    node* temp = headc;
    while(temp!=NULL)
    {
        tot_sales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* del(int num, struct node* head, struct node* tail)
{
    node* temp1=head;
    if(temp1==NULL)
    {
        cout<<"LIST EMPTY!!";
        return head;
    } 
    while(temp1->next!=NULL && temp1->data!=num)
    {
        temp1=temp1->next;
    }
    if(temp1->data==num)
    {
        if(temp1==head)
        {   
            temp1->next->prev=temp1->prev;
            head=temp1->next;
        }
        else
        {
            if(temp1->next!=NULL)
            {
                temp1->next->prev=temp1->prev;
            }
            temp1->prev->next=temp1->next;
            if(temp1->next==NULL)
            {
                tail=temp1->prev;
            }
        }
        cout<<"\n\t\t\t\t\t\t\t   ### Order menu ###\n";
        disp_list(head);
        return head;
    }
    cout<<"\n\t\t\t\t\t\t Item with given serial number doesn't exist!\n\n";
    return head;
}

void del_adm(int num)
{
    heada=del(num, heada, taila);
}

void del_cust(int num)
{
    headc=del(num, headc, tailc);
}

void display_bill()
{
    disp_list(headc);
    node* temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }
    cout<<"\t\t\t\t\t\t\tTotal price : "<<total_price<<"\n";
}

void del_list(struct node* head)
{
    if(head==NULL)
    {
        head=NULL;
    }
    else
    {
        node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }
}

void admin()
{
    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t\t\t\t\t    ADMIN SECTION\n";
    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
    while(1)
    {
        cout<<"\n\t\t\t\t\t\t\t1. View total sales\n";
        cout<<"\t\t\t\t\t\t\t2. Add new items in the order menu\n";
        cout<<"\t\t\t\t\t\t\t3. Delete items from the order menu\n";
        cout<<"\t\t\t\t\t\t\t4. Display order menu\n";
        cout<<"\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
        cout<<"\t\t\t\t\t\t\t   Enter Your Choice : ";

        int opt;
        cin>>opt;

        if(opt==5)
            break;

        switch(opt)
        {
            case 1:
            {
                disp_list(head_s);
                break;
            }
            case 2:
            {
                cout<<"\n\t\t\t\t\t\t\tEnter serial no. of the item: ";
                int num, flag=0;
                string name;
                float price;
                cin>>num;

                node* temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        cout<<"\n\t\t\t\t\t\t item with given serial number already exists!!\n\n";
                        flag=1;
                        break;
                    }
                    temp=temp->next;
                }
                if(flag)
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\tEnter item name: ";
                cin>>name;
                cout<<"\t\t\t\t\t\t\tEnter price: ";
                cin>>price;
                create_adm(heada, num, name, price);
                cout<<"\n\t\t\t\t\t\t\tNew item added to the list!!\n\n";
                cout<<"\n\t\t\t\t\t\t### Updated list of Order menu ###\n";
                disp_list(heada);
                break;
            }
            case 3:
            {
                cout<<"\n\t\t\t\t\tEnter serial no. of the item which is to be Deleted : ";
                int num;
                cin>>num;
                del_adm(num);
                break;
            }
            case 4:
            {
                cout<<"\n\t\t\t\t\t\t\t   ### Order menu ###\n";
                cout<<"\t\t\t\t\t\t\tSr. No.\tItem Name\tPrice\n";
                disp_list(heada);
                break;
            }
            default:
                cout<<"\n\t\t\t\t\t\tInvalid Input!!\n";
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
    while(1)
    {
        cout<<"\n\t\t\t\t\t\t\t1. Place your order\n";
        cout<<"\t\t\t\t\t\t\t2. View your ordered items\n";
        cout<<"\t\t\t\t\t\t\t3. Delete an item from order\n";
        cout<<"\t\t\t\t\t\t\t4. Display final bill\n";
        cout<<"\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
        cout<<"\t\t\t\t\t\t\t   Enter Your Choice : ";

        int opt;
        scanf("%d",&opt);
    
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
            {
                cout<<"\t\t\t\t\t\t\tSr. No.\tItem Name\tPrice\n";
                disp_list(heada);
                cout<<"\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                int n;
                cin>>n;
                cout<<"\t\t\t\t\t\tEnter quantity: ";
                int quantity;
                cin>>quantity;
                headc=NULL;
                create_cust(headc, n, quantity);
                break;
            }

            case 2:
            {
                cout<<"\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
                cout<<"\t\t\t\t\t\t\tSr. No.\tItem Name\tQuantity\tAmount\n";
                disp_list(headc);
                break;
            }

            case 3:
            {
                cout<<"\n\t\t\t\t\tEnter serial no. of the item which is to be Deleted: ";
                int num;
                cin>>num;
                del_cust(num);
                break;
            }

            case 4:
            {
                calc_tot_sales();
                cout<<"\n\t\t\t\t\t\t\t   Final Bill   \n";
                display_bill();
                del_list(headc);
                cout<<"\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                flag=1;
                break;
            }
            default:
                cout<<"\n\t\t\t\t\t\tInvalid Input!!\n";
                break;
        }
        if(flag==1)
            break;
    }
}

void main_menu()
{
    cout<<"\n                                 **************************************************************************\n";
    cout<<"                                                     WELCOME TO CAFE MANAGEMENT SYSTEM\n";
    cout<<"                                 **************************************************************************\n\n\n";
    cout<<"\t\t\t\t\t\t\t1. ADMIN SECTION \n";
    cout<<"\t\t\t\t\t\t\t2. CUSTOMER SECTION \n";
    cout<<"\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout<<"\t\t\t\t\t\t\tEnter Your Choice : ";
}

int main()
{
    create_adm(heada,1,"Cappucino",200);
    create_adm(heada,2,"Tea      ",120);
    create_adm(heada,3,"Coffee   ",150);
    create_adm(heada,4,"ESPRESSO",150);
    create_adm(heada,5,"HOT CHOCOLATE",80);
    create_adm(heada,6,"MilkShake",80);
    create_adm(heada,7,"Cold Coco",95);
    create_adm(heada,8,"Mojito   ",50);
    create_adm(heada,9,"COKE/7UP/LIMCA",20);
    create_adm(heada,10,"Sandwich",180);
    create_adm(heada,11,"Samosa (2 pcs.)",60);
    create_adm(heada,12,"Fries     ",70);
    create_adm(heada,13,"Pastry (2 pcs.)",100);
    create_adm(heada,14,"Cake       ",75);
    while(1)
    {
        main_menu();
        int choice;
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                admin();
                break;

            case 2:
                customer();
                break;

            case 3:
                cout<<"\n\n\t\t\t\t\t\t\t<------------Thanks, Visit Again!!------------>\n";
                return 0;

            default:
                cout<<"\n\t\t\t\t\t\tInvalid Input!!\n";
                break;
        }
    }
}