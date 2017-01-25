//Aluno: George Nunes de Moura Filho
//Matrícula: 11328786
//Disciplina: Análise e Projeto de Algoritmo
//Período: 2016.2
//Trabaho Extra

#include <iostream>
#include <vector>
#include <stdlib.h>

void print_vector(std::vector<int>);
void fail();

std::vector<int> insertionSort(std::vector<int> vec){
	
	int len = vec.size();

    for(int i = 1; i < len; i++) {
		int choose = vec[i];
		int j = i - 1;
		while((j >= 0)&&(vec[j] > choose)){
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = choose;
	}
	return vec;
}

std::vector<int> selectionSort(std::vector<int> vec){ 

  int len = vec.size(), min, aux, i, j;

  for (i = 0; i < (len-1); i++){
     min = i;
     for (j = (i+1); j < len; j++)
       if(vec[j] < vec[min])min = j;
     
     if (i!=min) {
       aux = vec[i];
       vec[i] = vec[min];
       vec[min] = aux;
     }
  }
  return vec;
}

void merge_array(std::vector<int> first, std::vector<int> second, std::vector<int>* fim){

    int fim_len = first.size()+second.size();
    int fir_cont=0, sec_cont=0;
 
 
    for(int i=0; i<fim_len; i++){
 
        if(fir_cont<first.size() && sec_cont<second.size()){
 
            if(first[fir_cont] < second[sec_cont])
                (*fim)[i]=first[fir_cont++];
            else
                (*fim)[i]=second[sec_cont++];
        }else{
 
            if(fir_cont<first.size())
                (*fim)[i]=first[fir_cont++];
            if(sec_cont<second.size())
                (*fim)[i]=second[sec_cont++];
        }
    }
}

std::vector<int> mergeSort(std::vector<int> vec){

    int middle=vec.size()/2;
 
    if(vec.size()==1)return vec;
    else{
        std::vector<int> first(vec.begin(), vec.begin()+middle);
        std::vector<int> second(vec.begin()+middle, vec.end());
        std::vector<int> fim(vec.size());
 
        first=mergeSort(first);
        second=mergeSort(second);
 
        merge_array(first, second, &fim);
       
        return fim;
    }
}

void quick(std::vector<int> *vec, int left, int right){

    int pivo = left,k,j;     
    for(int i=left+1; i<=right; i++){        
        j = i;                      
        if((*vec)[j] < (*vec)[pivo]){     
         k = (*vec)[j];               
         while(j > pivo){           
            (*vec)[j] = (*vec)[j-1];      
            j--;                    
         }
         (*vec)[j] = k;               
         pivo++;                    
        }
    }
    if(pivo-1 >= left){              
        quick(vec,left,pivo-1);      
    }
    if(pivo+1 <= right){              
        quick(vec,pivo+1,right);      
    }
 }

 std::vector<int> quickSort(std::vector<int> vec){
	int len = vec.size();
	quick(&vec, 0, len-1);
	return vec;
}

void buildMaxH(std::vector<int> &vec, int start , int end){
    int max = 2 * start + 1;

    if(max < end){
       if((max+1) < end && vec.at(max) < vec.at(max+1))++max;
       
       if(vec.at(max) > vec.at(start)){
          std::swap(vec[max], vec[start]);
          buildMaxH(vec, max, end);
       }
    }
}

void heapSort(std::vector<int> &vec){
    int tam = static_cast<int>(vec.size()), i;

    for(i=tam/2-1; i>=0; --i)
       buildMaxH(vec, i , tam );
    
    std::vector<int>::reverse_iterator elem;

    for(elem=vec.rbegin(); elem!=vec.rend(); elem++){
       std::iter_swap( elem, vec.begin() );
       buildMaxH(vec,0,--tam);
    }
}

int main(int argc, char* argv[]){
	
	int in;
	std::vector<int> vec;
	
	while(std::cin >> in){vec.push_back(in);}
	
	if(argc==2){

		int param = atoi(argv[1]);
		if(param==1){
			vec = insertionSort(vec);
		}else if(param==2){
			vec = selectionSort(vec);
		}else if(param==3){
			vec = mergeSort(vec);
		}else if(param==4){
			vec = quickSort(vec);
		}else if(param==5){
			heapSort(vec);
		}else{
			fail();
			return 1;
		}
		print_vector(vec);
 	}else{
		fail();
	}

	return 0;
}

void print_vector(std::vector<int> vec){
	int len = vec.size();
	for(int i=0; i<len; i++)
		std::cout << vec[i] << std::endl;
}

void fail(){
	std::cout << "Selecione um algoritmo como argumento:\n" << std::endl;
	std::cout << "1 - Insertion Sort" << std::endl;
	std::cout << "2 - Selection Sort" << std::endl;
	std::cout << "3 - Merge Sort" << std::endl;
	std::cout << "4 - Quick Sort" << std::endl;
	std::cout << "5 - Heap Sort" << std::endl;
}