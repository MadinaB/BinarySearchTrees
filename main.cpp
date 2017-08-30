#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <iostream>
 
using namespace std;

int main()
{
	typedef Entry<int, float> EntryType;

	LinkedBinaryTree<EntryType> t;
	
	std::cout << "Size : " << t.size() << std::endl;
	
	t.addRoot();
	
	std::cout << "Size : " << t.size() << std::endl;
	
	
	//
	// Binary Search Tree test
	//
	SearchTree<EntryType>	st;
	
	std::cout << "Size : " << st.size() << std::endl;
	st.insert(1, 2.5);
	st.insert(3, 4.5);
	st.insert(7, 5.5);
	st.insert(2, 1.5);
	st.insert(3, 8.5);
	std::cout << "Size : " << st.size() << std::endl;

	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
		
	st.erase(3);
	std::cout << "Size : " << st.size() << std::endl;
	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}	
	
	
	
	//
	// AVL Tree test
	//
	AVLTree<EntryType>	avl;
	
	std::cout << "Size : " << avl.size() << std::endl;
	avl.insert(1, 2.5);
	avl.insert(3, 4.5);
	avl.insert(7, 5.5);
	avl.insert(2, 1.5);
	avl.insert(3, 8.5);
	std::cout << "Size : " << avl.size() << std::endl;

	for(AVLTree<EntryType>::Iterator it = avl.begin(); it != avl.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
		
	avl.erase(3);
	std::cout << "Size : " << avl.size() << std::endl;
	for(AVLTree<EntryType>::Iterator it = avl.begin(); it != avl.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}




    fstream myfileIn("PerformanceComparison.txt", ios::in|ios::out|ios::trunc);
    myfileIn<<"Perfomance Comparison:" <<'\n';
    clock_t start, stop;
    
    for(int setSize = 100; setSize <= 1000000; setSize = setSize *10){
	typedef Entry<unsigned int, float> MyEntryType;
        
	SearchTree<MyEntryType>	MySt;
	AVLTree<MyEntryType>	MyAvl;
        
        // generation of diffent random sets with size = setSize for insertion, find and erase
        fstream randomSetIn("RandomSet.txt", ios::in|ios::out|ios::trunc); 
        fstream randomSetFind("RandomSetFind.txt", ios::in|ios::out|ios::trunc);
        fstream randomSetErase("RandomSetEraseFind.txt", ios::in|ios::out|ios::trunc);
        for(int i = 0; i <= setSize; i++){
            
            // generating random set for insertion
            srand(time(NULL)/(i+1)*setSize); // trying random numbers
            unsigned int key = rand()%setSize + 1;
            
            srand((i*i*setSize));
            float value = static_cast <float> (rand())/static_cast<float> (RAND_MAX);

            randomSetIn<<key;
            randomSetIn<<" ";
            randomSetIn<<value;
            randomSetIn<<'\n';
            
            // generating random set for find
            srand(time(NULL)*time(NULL)/(i+1)*setSize);
            unsigned int keyToFind = rand()%setSize + 1;
            
            srand((i*i*i*setSize));
            float valueToFind = static_cast <float> (rand())/static_cast<float> (RAND_MAX);

            randomSetFind<<keyToFind;
            randomSetFind<<" ";
            randomSetFind<<valueToFind;
            randomSetFind<<'\n';

            // generating random set for erase

            srand(time(NULL)*time(NULL)*time(NULL)/(i+1)*setSize);
            unsigned int keyToErase = rand()%setSize + 1;
            
            srand((i*setSize));
            float valueToErase = static_cast <float> (rand())/static_cast<float> (RAND_MAX);

            randomSetErase<<keyToErase;
            randomSetErase<<" ";
            randomSetErase<<valueToErase;
            randomSetErase<<'\n';

        }
        randomSetIn.close();
        randomSetFind.close();
        randomSetErase.close();
        
        if (myfileIn.is_open())
        {  
            myfileIn<<"Test set:" <<setSize<<"."<<'\n';
            

            /* Performance of Insertion */
            float randomKey;
            float randomValue;
            

            myfileIn<<" a) Insertion:" <<'\n';
            //Search Tree
            fstream randomSetOut("RandomSet.txt", ios::in|ios::out);
            myfileIn<<"Insertion to SearchTree a dataset of random numbers with size "<<setSize<<" takes "; // "this amount"<< " of time."<<'\n';
            start = clock();
            while (randomSetOut >> randomKey) 
            {
                randomSetOut >> randomValue;
                //insertion 
	        MySt.insert(randomKey, randomValue);
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetOut.close();
            
            //AVL Tree
            fstream randomSetOut2("RandomSet.txt", ios::in|ios::out);
            myfileIn<<"Insertion to  AVLTree  a  dataset of random numbers with size "<<setSize<<" takes " ; //"this amount"<< " of time."<<'\n';

            start = clock();
            while (randomSetOut2 >> randomKey) 
            {
                randomSetOut2 >> randomValue;
                //  insertion 
                MyAvl.insert(randomKey, randomValue);
            }
            stop = clock();
            myfileIn<<(stop-start)<< " clocks."<<'\n';
            randomSetOut2.close();

            /* Performance of Find*/
            float randomKeyFind;
            float randomValueFind;
            
            myfileIn<<" b) Find:" <<'\n';
            //Search Tree
            fstream randomSetFindOut("RandomSetFind.txt", ios::in|ios::out);
            myfileIn<<"Find in SearchTree elements from dataset of random numbers with size "<<setSize<<" takes "; 
            start = clock();
            while (randomSetFindOut >> randomKeyFind) 
            {
                randomSetFindOut >> randomValueFind;
                //find 
	        MySt.find(randomKeyFind);
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetFindOut.close();
            
            //AVL Tree
            fstream randomSetFindOut2("RandomSetFind.txt", ios::in|ios::out);
            myfileIn<<"Find in   AVLTree  elements from dataset of random numbers with size "<<setSize<<" takes " ; 

            start = clock();
            while (randomSetFindOut2 >> randomKeyFind) 
            {
                randomSetFindOut2 >> randomValueFind;
                //  find
                MyAvl.find(randomKeyFind);
            }
            stop = clock();
            myfileIn<<( stop-start)<< " clocks."<<'\n';
            randomSetFindOut2.close();



            /* Performance of Erase and Find*/

            /*  30/70  */
            float randomKeyEF;
            float randomValueEF;
            
            myfileIn<<" c) Erase and Find:" <<'\n';
            //Search Tree
            fstream randomSetEF("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in SearchTree elements from dataset of random numbers with size "<<setSize<<" and ratio 30/70 takes "; 
            start = clock();
            int STseed = 0;
            while (randomSetEF >> randomKeyEF) 
            {
                randomSetEF >> randomValueEF;
                // Erase and find
                srand(STseed);
                int choice = rand() % 10;
                if(choice <=2){
                    // 30 % erase
                    if(MySt.find(randomKeyEF)!= MySt.end())
                    {
                         MySt.erase(randomKeyEF);
                    }
                }
                else{
                    MySt.find(randomKeyEF);
                }
                STseed++;
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetEF.close();
           
            //AVL Tree
            fstream randomSetEF2("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in   AVL Tree elements from dataset of random numbers with size "<<setSize<<" and ratio 30/70 takes "; 
            start = clock();
            int AVLseed = 0;
            while (randomSetEF2 >> randomKeyEF) 
            {
                randomSetEF2 >> randomValueEF;
                // Erase and find
                srand(AVLseed);
                int choice2 = rand() % 10;
                if(choice2 <=2){
                    // 30 % erase
                    if(MyAvl.find(randomKeyEF)!= MyAvl.end())
                    {
                            MyAvl.erase(randomKeyEF);
                    }
                }
                else{
                    MyAvl.find(randomKeyEF);
                }
                AVLseed++;
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetEF2.close();




            /*  50/50  */
            //Search Tree
            fstream randomSetEF3("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in SearchTree elements from dataset of random numbers with size "<<setSize<<" and ratio 50/50 takes "; 
            start = clock();
             STseed = 0;
            while (randomSetEF3 >> randomKeyEF) 
            {
                randomSetEF3 >> randomValueEF;
                // Erase and find
                srand(STseed);
                int choice = rand() % 10;
                if(choice <=4){
                    // 50 % erase
                    if(MySt.find(randomKeyEF)!= MySt.end())
                    {
                         MySt.erase(randomKeyEF);
                    }
                }
                else{
                    MySt.find(randomKeyEF);
                }
                STseed++;
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetEF3.close();
           
            //AVL Tree
            fstream randomSetEF4("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in   AVL Tree elements from dataset of random numbers with size "<<setSize<<" and ratio 50/50 takes "; 
            start = clock();
            AVLseed = 0;
            while (randomSetEF4 >> randomKeyEF) 
            {
                randomSetEF4 >> randomValueEF;
                // Erase and find
                srand(AVLseed);
                int choice2 = rand() % 10;
                if(choice2 <=4){
                    // 50 % erase
                    if(MyAvl.find(randomKeyEF)!= MyAvl.end())
                    {
                            MyAvl.erase(randomKeyEF);
                    }
                }
                else{
                    MyAvl.find(randomKeyEF);
                }
                AVLseed++;
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetEF4.close();



            /*  60/40  */
            //Search Tree
            fstream randomSetEF5("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in SearchTree elements from dataset of random numbers with size "<<setSize<<" and ratio 60/40 takes "; 
            start = clock();
            STseed = 0;
            while (randomSetEF5 >> randomKeyEF) 
            {
                randomSetEF5 >> randomValueEF;
                // Erase and find
                srand(STseed);
                int choice = rand() % 10;
                if(choice <=5){
                    // 60 % erase
                    if(MySt.find(randomKeyEF)!= MySt.end())
                    {
                         MySt.erase(randomKeyEF);
                    }
                }
                else{
                    MySt.find(randomKeyEF);
                }
                STseed++;
            }
            stop = clock();
            myfileIn<< ( stop-start )<< " clocks."<<'\n';
            randomSetEF5.close();
           
            //AVL Tree
            fstream randomSetEF6("RandomSetEraseFind.txt", ios::in|ios::out);
            myfileIn<<"Erase and Find in   AVL Tree elements from dataset of random numbers with size "<<setSize<<" and ratio 60/40 takes "; 
            start = clock();
            AVLseed = 0;
            while (randomSetEF6 >> randomKeyEF) 
            {
                randomSetEF6 >> randomValueEF;
                // Erase and find
                srand(AVLseed);
                int choice2 = rand() % 10;
                if(choice2 <=5){
                    // 60 % erase
                    if(MyAvl.find(randomKeyEF)!= MyAvl.end())
                    {
                            MyAvl.erase(randomKeyEF);
                    }
                }
                else{
                    MyAvl.find(randomKeyEF);
                }
                AVLseed++;
            }
            stop = clock();
            myfileIn<< (stop -start)<< " clocks."<<'\n';
            randomSetEF6.close();
        }
    }
    
    myfileIn.close();


   fstream myfileOut("PerformanceComparison.txt", ios::in|ios::out);
   string line; 
   if (myfileOut.is_open())
    {
        while (myfileOut>>line)
        {
            if(line[line.size()-1]=='.'){
                cout << line << '\n';
            }
            else{
                cout << line << ' ';
            }
        }
        myfileOut.close();
    }
    


	return 0;
}
