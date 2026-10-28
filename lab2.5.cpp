#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
  

// ===Node data declared===

 struct Node{
  int itemNum;
  char itemName[40];
  double unit; //for pound or number of unit
  double unitprice;
  double tax;
  double subtotal;
  Node*next;
};

// ===Create new node funtion===

  Node* createNode(ifstream &infile){

    Node *newitem= new Node;

    int userInum;
    
    cout << "Enter item number: ";
    cin >> userInum;
    
    // Rewind file to start
    infile.clear();     // clear eof flag
    infile.seekg(0, ios::beg);
    

    int inum;
    string name;
    char taxtype, selltype;
    double price;
    bool found = false;
    
    // Check for item number
   while(infile >> inum >> name >> taxtype >> selltype >> price){
         if(inum == userInum){
           found = true;
           break;
 }

}
    if (found){
           
    // ===Recive data from keyboard===
    
      double quantity=1.0;
    if(selltype=='p'){
       cout<<"Enter weight in pounds: ";
       cin>>quantity;
}

     else if(selltype == 'n'){
             int countQty;
             cout << "Enter quantity: ";
             cin >> countQty;
             quantity = static_cast<double>(countQty);
          }

     double subtotal = price * quantity;
     double tax = (taxtype == 't') ? subtotal * 0.06 : 0.0;
     
   
    //===Set data into the node===
     
    newitem->itemNum=inum;
    newitem->unit=quantity;
    newitem->unitprice=price;
    newitem->tax=tax;
    newitem->subtotal=subtotal;
    
  for (int i=0;i<name.length();i++){
      newitem->itemName[i]=name[i];
}
   newitem->itemName[name.length()]='\0';

   newitem->next=nullptr;
} 
  // == if !found then delete the node and stet pointer to null==
  
   else{
    delete newitem;
    newitem=nullptr;
}
   return newitem;

}//end functionC


//=== Insert node funtion ===

 Node *insertNode(Node *head,Node *newitem){
    
   Node *temp=head;    

    if (head==nullptr){
        head=newitem;
} 
    else if(newitem->itemNum < head->itemNum) {
            newitem->next=head;
            head=newitem;

}
    else {
            while(temp->next!=nullptr&& temp->next->itemNum < newitem->itemNum){
                  temp=temp->next;                
  }
            // == Update current node in the list if there is a duplicate==

               if(temp->next!=nullptr && temp->next->itemNum == newitem->itemNum){
                  temp->next->unit+=newitem->unit;
                  temp->next->subtotal= temp->next->unit *  temp->next->unitprice;
                  if (temp->next->tax>0){
                     temp->next->tax= temp->next->subtotal *0.06;  
}
                  else {
                      temp->next->tax=0.0;
}
                  delete newitem; // we dont need beacuse we are updating the existing node
}
               else {
              // ==Insert node in the correct location==
               
                   newitem->next=temp->next;
                   temp->next=newitem;
}
}
    return head;
}


//=== Detete node funtion===

 Node *deleteitem(Node *head,int userInum){
     Node *temp=head;

    if (head==nullptr){
        cout <<"There are no items to delete."<<endl;
        cout<<endl;
} 
    else if (head->itemNum==userInum){
        Node *tem=head->next;
        delete head;
        head=tem;
        cout<<"item has been deleted"<<endl;
         cout<<endl;
}
     else {
         while(temp->next!=nullptr&& temp->next->itemNum!=userInum){
               temp=temp->next;
}
         if (temp->next!=nullptr&& temp->next->itemNum==userInum){
             Node *rm=temp->next;
             temp->next=rm->next;
             delete rm;
             cout<<"Item# "<<userInum<<" has been removed from cart."<<endl;

}        else {
            cout<<"Item# "<<userInum<<" is not found.Please try agian"<<endl;
            cout<< endl;
}
}
return head; 
}

 //=== Print current list funtion===

 void print(Node *head){

 cout<<"====Shopping Cart===="<<endl;
 cout<<endl;
 cout<<"-------------------------------------------------------------------------------"<<endl;

  if(head==nullptr){
     cout<<"There are no item(s) in cart."<<endl;
     cout<<endl;
     cout<<"-------------------------------------------------------------------------------"<<endl;
}
  else {
       
       Node *temp=head;
       double total;
       double grandtotal=0.0;

            cout<< left << setw(6) << "Item#"
                << setw(30) << "Name"
                << right << setw(5) << "Qty"
                << setw(8) << "Price"
                << setw(7) << "Tax"
                << setw(10) << "Subtotal"
                << setw(10) << "Total" << endl;
             cout<<"-------------------------------------------------------------------------------"<<endl;
             while(temp!=nullptr){
 
              total= temp->subtotal+temp->tax;         

             cout<<left<<setw(6)<<temp->itemNum
                 <<setw(30)<<temp->itemName
                 <<right<<setw(5)<<temp->unit
                 <<setw(8)<< fixed<<setprecision(2) <<temp->unitprice
                 <<setw(7)<<temp->tax
                 <<setw(10)<<temp->subtotal
                 <<setw(10)<<total<<endl;

             grandtotal+=total;             
             temp=temp->next;
}
             cout<<"-------------------------------------------------------------------------------"<<endl;
             cout<<left<<setw(30)<<"Final total:"<<fixed<<setprecision(2)<<grandtotal<<endl;
             cout<<endl;
             cout<<endl;
}

}//end



 int main() {
 
   //== set the head for the link list==
   Node *head=nullptr;
   
  //== Open both txt file/database ==

      ifstream infile("item.txt");  // Open database file
      if(!infile.is_open()){
          cerr << "Cannot open database file\n";
          return 1;
     }
  
      ofstream outfile("Olu.txt");  // open receipt file
      if(!outfile.is_open()){
          cerr << "Cannot open receipt file\n";
          return 1;
      }
  
      //==  Receipt header ==
      outfile << "----GROCERY RECEIPT SYSTEM----\n\n";
  

         cout<<endl;
         cout<<endl;
         cout<<"Welcome To The Grocery System Menu!"<<endl;
         cout<<"-------------------------------------------------"<<endl;
         cout<<endl;
         cout <<"Please select one of the menu options below"<<endl;
         cout <<"-------------------------------------------------"<<endl;
         int num=0;

   //== The main menu ==

 while(num!=4){
        cout<<"1) Add new item to cart"<<endl;
        cout<<"2) Print current selected item(s)"<<endl;
        cout<<"3) Remove item from cart"<<endl;
        cout<<"4) Receive receipt"<<endl;
        cin>>num;
         
 switch(num){

// == Calling eeach funtion(s) based on the intructions from keyboard == 
        
    case 1:{   
      Node *newitem=createNode(infile);
      
     if(newitem!=nullptr){
        head=insertNode(head,newitem);
        cout<<endl;
        cout<<"This item has been added to cart!"<<endl;
        cout<<endl;
  }  
     else { 
        cout<<endl;
        cout<<"Item number not found. Please try again."<<endl;
        cout<<endl;
 }
    break;   
}
    case 2:
      print(head);
      break;
          
    case 3:{
     int userInum;
     cout<<"Which item number would you like to delete from cart?"<<endl;
     cin>>userInum;
     head=deleteitem(head,userInum); 
     break;
}
    case 4:{

     outfile<<endl;
     outfile <<"-------------------------------------------------------------------------------"<<endl;    
 
   if(head==nullptr){
      outfile<<"There are no item(s) in cart."<<endl;
      outfile<<endl;
      outfile <<"-------------------------------------------------------------------------------"<<endl;
 }
   else {

      Node *temp=head;
      double total;
      double grandtotal=0.0;
 
             outfile<< left << setw(6) << "Item#"
                << setw(30) << "Name"
                << right << setw(5) << "Qty"
                << setw(8) << "Price"
                << setw(7) << "Tax"
                << setw(10) << "Subtotal"
                << setw(10) << "Total" << endl;
              outfile <<"-------------------------------------------------------------------------------"<<endl; 

              while(temp!=nullptr){
  
               total= temp->subtotal+temp->tax;
 
             outfile<<left<<setw(6)<<temp->itemNum
                  <<setw(30)<<temp->itemName
                  <<right<<setw(5)<<temp->unit
                  <<setw(8)<< fixed<<setprecision(2) <<temp->unitprice
                  <<setw(7)<<temp->tax
                  <<setw(10)<<temp->subtotal
                  <<setw(10)<<total<<endl;

             grandtotal+=total;
             temp=temp->next;
}
              outfile <<"-------------------------------------------------------------------------------"<<endl;
              outfile<<left<<setw(30)<<"Final total:"<<fixed<<setprecision(2)<<grandtotal<<endl;
              
}
 break;
}     
     default : {   //== default case for vailidation check from user ==
      
      cout<<"Invalid choice, please try again"<<endl;
      break;
}
} 
}
    // == Close both files ==
    infile.close();
    outfile.close();
 
  cout << "Thank you for shopping! Please check your receipt file.\n";
return 0;
}
