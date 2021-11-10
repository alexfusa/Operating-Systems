/*
Alejandro Fernandez Hernandez


*/

#include <iostream>
#include <fstream>
#include <list>
#include <queue> 


using namespace std;

//global variables
int buf,value=0;
int  freeframes=10;//counter
list<int> frames;//Ten free frames
int array_reference[100];
int counter_array=0;


int FCFO(int);//prototype for FCFO

int optimal(int [],int,int);//prototype for Optimal Page Replacement

int main() {

int  pagefaults_FCFO=0;//counter for FCFO

int  pagefaults_Optimal=0;// counter for Optimal

//Open File .csv
 ifstream fin;

 //Read file
  fin.open("PAGE REPLACEMENT INPUT STRING.csv", ios::in); 
  

cout<<"Where are using First IN First OUT algorithm\n";

//Traverse the File until is empty
while(!fin.eof()){

  fin>>buf;//load the value from the file  

  //fill the array for the optimal page replacement
  array_reference[counter_array]=buf;

  counter_array++;//update array

// Use the FCFO algorithm. Return if there was a page fault
 pagefaults_FCFO+=FCFO(buf);
       
} 

cout<<"\n The Total of pagefaults using FCFO is "<<pagefaults_FCFO<<endl;


cout<<"\nOptimal Page Replacement\n";

freeframes=10; //reset our free frames

// Use the of the Optimal Page Replacement algorithm
pagefaults_Optimal=optimal(array_reference,freeframes,100);

cout<<"\n The Total of pagefaults using OPTIMAL is "<<pagefaults_Optimal<<endl;

//close file
fin.close();

return 0;
}//End of Main


//FCFO algorithm
int FCFO(int buffer){

int pagefaults=0;

for (auto const& it : frames) {

  //Find is the the page is in the table. DO nothing
   if(it==buf){value=1;}
      
  }
  //The page is not in the table
  if(value==0){

    if(freeframes==0){

      //if there is not a free frame Pop the front of the list
      frames.pop_front();

      frames.push_back(buf);

      pagefaults++;
      cout<<"Page #"<<buf<< " trigged a pagefault\n";

      
    }else{
      //if there are free frames just write and pagefault
      frames.push_back(buf);

      freeframes--;//One less free frame

      pagefaults++;//One more page fault

    cout<<"Page #"<<buf<< " trigged a pagefault\n";
  }

  }
  

value=0;//reset the value

return pagefaults;


}

int optimal(int list[],int n,int size)
{
    //Creating array for block storage
    int frames[n];

    //Initializing each block with -1
    for (int i=0;i<n;i++)

        frames[i]=-1;

    //Index to insert element
    int index=-1;

    //Counters for number of page fualts
    int page_faults=0;  

    //Pointer to indicate initially frames filled or not
    int full=0;

    //Traversing each symbol in fifo
    for (int i=0;i<size;i++){

        int symbol=list[i];

        int flag=0;

        for(int j=0;j<n;j++){

            if (symbol==frames[j]){
                flag=1;
                break;
            }
        }

        
        if(flag==0){

            //There is free space in the page table
            if (full==0)
            {
                index=(index+1)%n;

                frames[index]=symbol;

                page_faults+=1;// Trigged a page fault
                cout<<"Page #"<<symbol<< " trigged a pagefault\n";     
                
                //Frames filled or not
                if (i==n-1)
                    full=1;
            }

            //No more Space, apply optimal page replacement
            else
            {
                //First find the index to replace with
                int pos=-1;
                int index=-1;

                //Traversing each symbol and checking their optimal possibility
                for(int j=0;j<n;j++)
                {
                    //Whether symbol in frame found or not in future cached frame
                    int found=0;

                    for (int k=i+1;k<size;k++){
                        //If symbol exists in cached string
                        if (frames[j]==list[k]){
                            found=1;
                            if (pos<k)
                            {
                                pos=k;
                                index=j;
                            }
                            break;
                        } 
                    }
                    //Symbol does not exist in cached frame
                    if (found==0)
                    {
                        pos=size;
                        index=j;
                    }
                }

                //assign symbol
                frames[index]=symbol;                
                
            }
        }
    }
    return page_faults;
    

}
