#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct data {
    char section[30];
    char type[30];
    char brand[30];
    char name[30];
    int price;
    int quantity;
} data;
int strcompare(char str1[],char str2[]);    //compares two strings such that return 0 if found equal(here equal mean length and charaters like str and STR are equal);
void add_to_bill(data customer);            //this function adds user selected products to bill file (called inside buy_product() function)
void update_inventory_customer(data customer);   //this functions reduces the quantity of items from inventory that are added to cart by customer(called inside buy_product())
void display_drawer_cash(int *drawer);      //display cash that is present in the drawer 
void view_inventory();                        //display whole inventory
void search_product();                      //searches for product in inventory and return all details of product
void buy_product();                         //main hero of our game,used by customer to buy product
void delete_product_owner();                //this function  is used by owner to delete product from inventory
void quantity_check();                      //this function returns message to owner if quantity of products are less than 1 and return those products
void generate_bill();                      //called inside buy_product()  this is used to generate the bill from bill file
void update_items_customer();              //called inside generate bill-if customer want to remove item from cart or change the quantity
void remove_everything();                  //empties whole cart//basically customer leaving without buying anything   called inside generate_bill()
void print_bill();                         //simplies print the bill called inside generate_bill()
void final_update_inventory_customer(int updated_quantity,int bill_quantity,char product_name[]);    //called inside update_items_customer() if user decreases quantity from cart then it increases back in inventory this function do that
void withdraw_drawer_cash(int *drawer); //used by shopkeeper to withdraw money from drawer
void deposit_drawer_cash(int *drawer); //used by shopkeeper to deposit money to drawer
void update_inventory_shopkeeper();   //used by shopkeeper to update items in drawer
int drawer_cash;
int main() {      
                      
    int *drawer=&drawer_cash;  
    
    
    char pass[30]="password";
    remove_everything();
   
    int check;
    printf("Enter 1 if you are shopkeerper or enter 0 if you are customer:");
    scanf("%d",&check);
    switch(check){                                                //for checking the user whether shopkeeper or customer
        case 0:{
            printf("Namaste! How can we help you..\n");
            int ch;
            printf("Menu:\n1:buy\n2:Leave\n");
            printf("Enter choice(number):");
            scanf("%d",&ch);
            switch(ch){
                case 1:{
                    buy_product();
                    break;
                }
                case 2:{
                    printf("Thank you for visiting us..");
                    break;
                }
                default:
                printf("Entered invalid choice..");
            }
            break;
        }
        
        

        case 1:
        {

        char user_pass[30];
        printf("Enter password:");                                //to ensure if user is shopkeeper  
        fflush(stdin);     
        gets(user_pass);
        if(strcmp(user_pass,pass)==0){
            quantity_check();
            int ch;
            while(1){
                FILE *ptr;
                ptr=fopen("drawer_cash.txt","r");
                fscanf(ptr,"%d",drawer);
                fclose(ptr);
                printf("How can we help you..\n");
                printf("Menu:\n1:view_inventory\n2:search_product\n3:display_drawer_cash\n4:delete_product\n5:Withdraw Drawer cash\n6:Deposit cash in drawer\n7:Update inventory\nEnter choice:");
                scanf("%d",&ch);
                switch(ch){
                    case 1:{
                        view_inventory();
                        break;
                    }
                    case 2:{
                        search_product();
                        break;
                    }
                    case 3:{
                        display_drawer_cash(drawer);
                        break;
                    }
                    case 4:{
                        delete_product_owner();
                        break;
                    }
                    case 5:{
                        withdraw_drawer_cash(drawer);
                        break;
                    }
                    case 6:{
                        deposit_drawer_cash(drawer);
                        break;
                    }
                    case 7:{
                        update_inventory_shopkeeper();
                        break;
                    }
                    default:
                    printf("No perfect choice..\n");
                } 
                int more;
                printf("Anything else you want to do(if yes enter 1):");
                scanf("%d",&more);
                if(more!=1){
                    printf("Thank you Sir for using our system..");
                    break;
                }
            }
          
        }
        else{
            printf("Hey intruder you are not welcome...");
        }
        
        break;
        }

        default:
        printf("Entered invalid choice...");
    }

    return 0;
}

void buy_product(){
    data customer;
    data choice;
    char header[100];


    while(1){
    FILE *ptr = fopen("data.txt", "r");
    fgets(header, sizeof(header), ptr); // Skip the header line


    
    char temp[30]="temp";
    int x=1;
    printf("Menu:\n");
    // Read each line after the header
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(temp,choice.section)==0){           //to not print repeated values
            continue;
        } 
        
        printf("%d)%s\n",x,choice.section);
        strcpy(temp,choice.section);
        x++;
        
    }
    printf("Enter choice:");
    fflush(stdin);
    gets(customer.section);
   
   

    rewind(ptr);                         //bring pointer to start of file
    
    x=1;
    fgets(header, sizeof(header), ptr);
    strcpy(temp,"temp");
    printf("Menu:\n");
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity))  != EOF) {                          
        if(strcompare(choice.section,customer.section)==0){
            
            if(strcompare(temp,choice.type)==0){
                continue;
            }
            printf("%d)%s\n",x,choice.type);
            strcpy(temp,choice.type);
            x++;
        }  

        
    }
    printf("%d)%s\n",x,"reset");
    printf("Enter your choice:");
    fflush(stdin);
    gets(customer.type);
    if(strcompare(customer.type,"reset")==0){
        continue;
    }

    rewind(ptr);

    x=1;
    fgets(header, sizeof(header), ptr);
    strcpy(temp,"temp");
    printf("Menu:\n");
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        
        if(strcompare(choice.type,customer.type)==0 && strcompare(choice.section,customer.section)==0){
            if(strcompare(temp,choice.brand)==0){
                continue;
            }
            printf("%d)%s\n",x,choice.brand);
            strcpy(temp,choice.brand);
            x++;
        }  
       
    }
    printf("%d)%s\n",x,"reset");
    printf("Enter your choice:");
    fflush(stdin);
    gets(customer.brand);
    if(strcompare(customer.brand,"reset")==0){
        continue;
    }

    rewind(ptr);
    x=1;
    fgets(header, sizeof(header), ptr);
    strcpy(temp,"temp");
    printf("Menu:\n");
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(choice.brand,customer.brand)==0 && strcompare(choice.section,customer.section)==0 && strcompare(choice.type,customer.type)==0){
            if(strcompare(temp,choice.name)==0){
                continue;
            }
            printf("%d)%s\n",x,choice.name);
            strcpy(temp,choice.name);
            x++;
        }  
    }
    printf("%d)%s\n",x,"reset");
    printf("Enter your choice:");
    fflush(stdin);
    gets(customer.name);
    if(strcompare(customer.name,"reset")==0){
        continue;
    }
    rewind(ptr);
    fgets(header, sizeof(header), ptr);
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(choice.brand,customer.brand)==0 && strcompare(choice.section,customer.section)==0 && strcompare(choice.type,customer.type)==0 && strcompare(choice.name,customer.name)==0){
            printf("Quantity availabe:%d\n",choice.quantity);
            printf("Price:%d\n",choice.price);
            while(1){
                printf("Enter quantity you like to purchase:");
                scanf("%d",&customer.quantity);
                if(customer.quantity<=choice.quantity && customer.quantity>=0){
                    break;
                }
                printf("Entered invalid quantity...\n");
            }
            customer.price=choice.price;
            break;    
        }  
    }
    if(customer.quantity!=0){
        add_to_bill(customer);
        update_inventory_customer(customer);
    }
    

    fclose(ptr);
        int ch;
        printf("Do you want to buy anything else(if yes enter 1 ):");
        scanf("%d",&ch);
        if(ch!=1){
            generate_bill();
            break;
        }
    }

}

void display_drawer_cash(int *drawer){
    printf("The drawer cash is %d\n",*drawer);
}
void view_inventory(){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    char ch;
    ch=fgetc(ptr);
    while(ch!=EOF){
        printf("%c",ch);
        ch=fgetc(ptr);
    }
    printf("\n");
    fclose(ptr);
}
int strcompare(char str1[],char str2[]){

    if(strlen(str1)==strlen(str2)){
        for(int i=0;str1[i]!='\0';i++){
            if(str1[i]>='a' && str1[i]<='z'){
                if(str1[i]==str2[i] || (str1[i]-32)==str2[i]){
                }
                else{
                    return 1;
                }
            }
            else if(str1[i]>='A' && str1[i]<='Z')   {
                if(str1[i]==str2[i] || (str1[i]+32)==str2[i]){
                }
                else{
                    return 1;
                }
            }
            else{
                if(str1[i]==str2[i]){

                }
                else{
                    return 1;
                }
            }
        }
        return 0;
        
    }
    else{
        return 1;
    }
    
}
void add_to_bill(data customer){
    FILE *ptr;
    ptr=fopen("bill.txt","a");
    fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",customer.section,customer.type,customer.brand,customer.name,customer.price,customer.quantity);
    fclose(ptr);
}
void update_inventory_customer(data customer){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    data update[200];
    char header[100];
    data choice;
    fgets(header, sizeof(header), ptr);
    int i=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(choice.brand,customer.brand)==0 && strcompare(choice.section,customer.section)==0 && strcompare(choice.type,customer.type)==0 && strcompare(choice.name,customer.name)==0){
           strcpy(update[i].section,choice.section);
           strcpy(update[i].type,choice.type);
           strcpy(update[i].brand,choice.brand);
           strcpy(update[i].name,choice.name);
           update[i].quantity=choice.quantity-customer.quantity;
           update[i].price=choice.price;
        }  
        else{
           strcpy(update[i].section,choice.section);
           strcpy(update[i].type,choice.type);
           strcpy(update[i].brand,choice.brand);
           strcpy(update[i].name,choice.name);
           update[i].quantity=choice.quantity;
           update[i].price=choice.price;

        }
        i++;
    }
 
    fclose(ptr);
    ptr=fopen("data.txt","w");
    fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
  
    for(int j=0;j<i;j++){
        fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",update[j].section,update[j].type,update[j].brand,update[j].name,update[j].price,update[j].quantity);
    }
    fclose(ptr);
    

}

void search_product(){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    char product_name[30];
    char header[100];
    data choice;
    fgets(header,sizeof(header),ptr);
    printf("Enter product name you want to search:");
    fflush(stdin);
    gets(product_name);
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {

        if(strcompare(product_name,choice.name)==0){
            printf("Section:%s\n",choice.section);
            printf("Type:%s\n",choice.type);
            printf("Brand:%s\n",choice.brand);
            printf("Name:%s\n",choice.name);
            printf("Price:%d\n",choice.price);
            printf("Quantity:%d\n",choice.quantity);
            return;
        }
    }
    printf("product not found...\n");

}

void delete_product_owner(){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    char product_name[30];
    char header[100];
    data choice;
    data update[200];
    fgets(header,sizeof(header),ptr);
    printf("Enter product name you want to delete:");
    fflush(stdin);
    gets(product_name);
    int i=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(product_name,choice.name)==0){
            continue;
        }
        strcpy(update[i].section,choice.section);
        strcpy(update[i].type,choice.type);
        strcpy(update[i].brand,choice.brand);
        strcpy(update[i].name,choice.name);
        update[i].quantity=choice.quantity;
        update[i].price=choice.price;
        i++;
    }
    fclose(ptr);
    ptr=fopen("data.txt","w");
    fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
  
    for(int j=0;j<i;j++){
        fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",update[j].section,update[j].type,update[j].brand,update[j].name,update[j].price,update[j].quantity);
    }
    fclose(ptr);
    
}
void quantity_check(){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    char header[100];
    data choice;
    fgets(header,sizeof(header),ptr);
    fflush(stdin);
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(choice.quantity<2){
            printf("Quantity of %s of %s(%s) in %s section is low..and quantity is %d\n",choice.name,choice.brand,choice.type,choice.section,choice.quantity);
        }
    }
    fclose(ptr);
}
void generate_bill(){
    FILE *ptr;
    
    char header[100];
    data choice;
    
    while(1){
        ptr=fopen("bill.txt","r");
        fgets(header,100,ptr);
        printf("Products in your cart are:\n");
        while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
            printf("name:%s  quantity:%d\n",choice.name,choice.quantity);
        }
        int ch;
        printf("Do you want to edit anthing(if yes enter 1):");
        scanf("%d",&ch);
        if(ch==1){
            int ch1;
            printf("Menu:\nEnter 1:Update items\n2:Cart Abandonment\nEnter choice:");
            scanf("%d",&ch1);
            switch(ch1){
                case 1:{
                    update_items_customer();
                    break;
                }
                case 2:{
                    remove_everything();
                    printf("Thank you for visiting! Feel free to stop by again anytime we'd love to assist you in finding exactly what you need!");
                    exit(1);
                    break;
                }
                
            }
        }
        else{
            fclose(ptr);
            print_bill();
            printf("Thank you for visiting! Feel free to stop by again anytime we'd love to assist you in finding exactly what you need!");
            break;
        }
        fclose(ptr);
    }

}
void update_items_customer(){
    FILE *ptr;
    ptr=fopen("bill.txt","r");
    char product_name[30];
    char header[100];
    data choice;
    data update[200];
    fgets(header,sizeof(header),ptr);
    printf("Enter product name you want to update:");
    fflush(stdin);
    gets(product_name);
    int i=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(product_name,choice.name)==0){
            int updated_quantity;
            printf("Quantity in cart:%d\n",choice.quantity);
            printf("Enter quantity you want to update:");
            scanf("%d",&updated_quantity);
            if(updated_quantity<0 || updated_quantity>choice.quantity){
                return;
            }
            
            final_update_inventory_customer(updated_quantity,choice.quantity,product_name);

            if(updated_quantity==0){
                continue;
            }
            
            strcpy(update[i].section,choice.section);
            strcpy(update[i].type,choice.type);
            strcpy(update[i].brand,choice.brand);
            strcpy(update[i].name,choice.name);
            update[i].quantity=updated_quantity;
            update[i].price=choice.price;
            i++;


        }
        else{
            strcpy(update[i].section,choice.section);
            strcpy(update[i].type,choice.type);
            strcpy(update[i].brand,choice.brand);
            strcpy(update[i].name,choice.name);
            update[i].quantity=choice.quantity;
            update[i].price=choice.price;
            i++;
        }
        
    }
    fclose(ptr);
    ptr=fopen("bill.txt","w");
    fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
  
    for(int j=0;j<i;j++){
        fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",update[j].section,update[j].type,update[j].brand,update[j].name,update[j].price,update[j].quantity);
    }
    fclose(ptr);

}
void remove_everything(){
    FILE *ptr;
    ptr=fopen("bill.txt","w");
    fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
    fclose(ptr);
}

void print_bill(){
    data choice;
    char header[100];
    FILE *ptr = fopen("bill.txt", "r");
    fgets(header, sizeof(header), ptr);
    int sum=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        printf("Type:%s\t\tBrand:%s\t\tName:%s\t\tQuantity:%d\t\tprice:%d\n",choice.type, choice.brand, choice.name,choice.quantity,choice.price*choice.quantity);
        sum+=choice.price*choice.quantity;
    }
    printf("Total Amount:%d\n",sum);
    int drawer_amount;
    FILE *ptr1;
    ptr1=fopen("drawer_cash.txt","r");
    fscanf(ptr1,"%d",&drawer_amount);
    fclose(ptr1);
   
    ptr1=fopen("drawer_cash.txt","w");
    fprintf(ptr1,"%d",drawer_amount+sum);
    fclose(ptr1);
    fclose(ptr);
}
void final_update_inventory_customer(int updated_quantity,int bill_quantity,char product_name[]){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    data update[200];
    char header[100];
    data choice;
    fgets(header, sizeof(header), ptr);
    int i=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(product_name,choice.name)==0){
            strcpy(update[i].section,choice.section);
            strcpy(update[i].type,choice.type);
            strcpy(update[i].brand,choice.brand);
            strcpy(update[i].name,choice.name);
            update[i].quantity=choice.quantity+bill_quantity-updated_quantity;
            update[i].price=choice.price;
            i++;
        }
        else{
            strcpy(update[i].section,choice.section);
            strcpy(update[i].type,choice.type);
            strcpy(update[i].brand,choice.brand);
            strcpy(update[i].name,choice.name);
            update[i].quantity=choice.quantity;
            update[i].price=choice.price;
            i++;
        }  
    }

    fclose(ptr);
    ptr=fopen("data.txt","w");
    fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
  
    for(int j=0;j<i;j++){
        fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",update[j].section,update[j].type,update[j].brand,update[j].name,update[j].price,update[j].quantity);
    }
    fclose(ptr);   

}

void withdraw_drawer_cash(int *drawer){
    int amount;
    
    printf("Enter the amount you want to withdraw:");
    scanf("%d",&amount);
    if(*drawer>=amount){
       FILE *ptr;
       ptr=fopen("drawer_cash.txt","w");
       fprintf(ptr,"%d",*drawer-amount);
       fclose(ptr);
    }
    else{
        printf("You dontn have enough cash in drawer..");
    }
}
void deposit_drawer_cash(int *drawer){
    int amount;
    
    printf("Enter the amount you want to deposit:");
    scanf("%d",&amount);
   
       FILE *ptr;
       ptr=fopen("drawer_cash.txt","w");
       fprintf(ptr,"%d",*drawer+amount);
       fclose(ptr);
    
}
void update_inventory_shopkeeper(){
    FILE *ptr;
    ptr=fopen("data.txt","r");
    char product_name[30];
    char header[100];
    data choice;
    data update[200];
    fgets(header,sizeof(header),ptr);
    printf("Enter product name you want to update:");
    fflush(stdin);
    gets(product_name);
    int i=0;
    int flag=0;
    while ((fscanf(ptr, "%s %s %s %s %d %d",choice.section, choice.type, choice.brand, choice.name,&choice.price, &choice.quantity)) != EOF) {
        if(strcompare(product_name,choice.name)==0){
            flag=1;
            int ch;
            printf("Menu:\n1:Update quantity\n2:Update price\n3:Update both:\nEnter choice:");
            scanf("%d",&ch);
            switch(ch){
                case 1:{
                    int qty;
                    printf("Enter new quantity:");
                    scanf("%d",&qty);
                    if(qty<0){
                        strcpy(update[i].section,choice.section);
                        strcpy(update[i].type,choice.type);
                        strcpy(update[i].brand,choice.brand);
                        strcpy(update[i].name,choice.name);
                        update[i].quantity=choice.quantity;
                        update[i].price=choice.price;
                        i++;
                        break;
                    }
                    else if(qty==0){
                        break;
                    }
                    strcpy(update[i].section,choice.section);
                    strcpy(update[i].type,choice.type);
                    strcpy(update[i].brand,choice.brand);
                    strcpy(update[i].name,choice.name);
                    update[i].quantity=qty;
                    update[i].price=choice.price;
                    i++;
                    break;
                }
                case 2:{
                    int price;
                    printf("Enter new price:");
                    scanf("%d",&price);
                    if(price<0){
                        strcpy(update[i].section,choice.section);
                        strcpy(update[i].type,choice.type);
                        strcpy(update[i].brand,choice.brand);
                        strcpy(update[i].name,choice.name);
                        update[i].quantity=choice.quantity;
                        update[i].price=choice.price;
                        i++;
                        break;
                    }
                    strcpy(update[i].section,choice.section);
                    strcpy(update[i].type,choice.type);
                    strcpy(update[i].brand,choice.brand);
                    strcpy(update[i].name,choice.name);
                    update[i].quantity=choice.quantity;
                    update[i].price=price;
                    i++;
                    break;
                }
                case 3:{
                    int qty;
                    printf("Enter new quantity:");
                    scanf("%d",&qty);
                    if(qty<0){
                        strcpy(update[i].section,choice.section);
                        strcpy(update[i].type,choice.type);
                        strcpy(update[i].brand,choice.brand);
                        strcpy(update[i].name,choice.name);
                        update[i].quantity=choice.quantity;
                        update[i].price=choice.price;
                        i++;
                        break;
                    }
                    else if(qty==0){
                        break;
                    }
                    int price;
                    printf("Enter new price:");
                    scanf("%d",&price);
                    if(price<0){
                        strcpy(update[i].section,choice.section);
                        strcpy(update[i].type,choice.type);
                        strcpy(update[i].brand,choice.brand);
                        strcpy(update[i].name,choice.name);
                        update[i].quantity=choice.quantity;
                        update[i].price=choice.price;
                        i++;
                        break;
                    }
                    strcpy(update[i].section,choice.section);
                    strcpy(update[i].type,choice.type);
                    strcpy(update[i].brand,choice.brand);
                    strcpy(update[i].name,choice.name);
                    update[i].quantity=qty;
                    update[i].price=price;
                    i++;
                    break;
                }
                default:
                printf("Entered invalid choice..");
            }
    }
    else{
        strcpy(update[i].section,choice.section);
        strcpy(update[i].type,choice.type);
        strcpy(update[i].brand,choice.brand);
        strcpy(update[i].name,choice.name);
        update[i].quantity=choice.quantity;
        update[i].price=choice.price;
        i++;

    }
}
if(flag==0){
    printf("Enter product section:");
    gets(update[i].section);
    printf("Enter product type:");
    gets(update[i].type);
    strcpy(update[i].name,product_name);
    printf("Enter product quantity:");
    scanf("%d",&update[i].quantity);
    printf("Enter product price:");
    scanf("%d",&update[i].price);
    i++;
}
fclose(ptr);
ptr=fopen("data.txt","w");
fprintf(ptr,"Section\t\tType\t\tBrand\t\tName\t\tPrice\t\tQuantity\n");
  
    for(int j=0;j<i;j++){
        fprintf(ptr,"%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",update[j].section,update[j].type,update[j].brand,update[j].name,update[j].price,update[j].quantity);
    }
    fclose(ptr);

}

