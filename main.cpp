#include <iostream>

using namespace std;

int Max(int a, int b){
  return a>b?a:b;
}

int cover(int **arr, int length, int *iCover, int *jCover){
  int sum = 0;
  int arrcopy[length][length];
  int assignCol[length];
  int assignRow[length];
  for(int i=0;i<length;i++){
    for(int j=0;j<length;j++){
      arrcopy[i][j] = arr[i][j];
    }
  }
  for(int i=0;i<length;i++){
    assignRow[i] = -1;
    assignCol[i] = -1;
    iCover[i] = 1;
    jCover[i] = 0;
  }
  for(int i = 0;i<length;i++){
    for(int j=0;j<length;j++){
      if(arrcopy[i][j]==0 && assignCol[j]==-1){
	assignCol[j]=i;
	assignRow[i]=j;
	arrcopy[i][j]=-1;
      }
    }
  }
  for(int i=0;i<length;i++){
    if(assignRow[i]==-1){
      iCover[i]=0;
      for(int j=0;j<length;j++){
	if(arrcopy[i][j]==0){
	  jCover[j]=1;
	  for(int a=0;a<length;a++){
	    if(arrcopy[a][j]==-1){
	      iCover[a]=0;
	      break;
	    }
	  }
	}
      }
    }
  }
  for(int i=0;i<length;i++){
    sum+=iCover[i] + jCover[i];
    //    cout << iCover[i] << " " << jCover[i] << endl;
  }
  return sum;
}

void assign(int **arr, int *assign){
}

void hungarian(int **arr, int length){
  while(true){
    //i sub
    for(int i=0;i<length;i++){
      int min = arr[i][0];
      for(int j=0;j<length;j++){
	if(arr[i][j] < min){
	  min = arr[i][j];
	}
      }
      for(int j=0;j<length;j++){
	arr[i][j] -= min;
      }
    }
    //j sub
    for(int j=0;j<length;j++){
      int min = arr[0][j];
      for(int i=0;i<length;i++){
	if(arr[i][j] < min){
	  min = arr[i][j];
	}
      }
      for(int i=0;i<length;i++){
	arr[i][j] -= min;
      }
    }
    int *iCover = new int [length];
    int *jCover = new int [length];
    int covers = cover(arr, length, iCover, jCover);
    if(covers>=length)
      return;
    //findmin
    int min = arr[0][0] + 1;
    for(int i=0;i<length;i++){
      for(int j=0;j<length;j++){
	min = (arr[i][j] < min && arr[i][j] > 0)?arr[i][j]:min;
      }
    }
    for(int i=0;i<length;i++){
      for(int j=0;j<length;j++){
	if(jCover[j]==1 && iCover[i]==1){
	  arr[i][j] += min;
	}else if(jCover[j]==0 && iCover[i]==0){
	  arr[i][j] -= min;
	}
      }
    }
  }
  int *assigns = new int [length];
  //assign(arr,assigns);
}
int main(){
  int **arr;
  int length = 4;
  arr = new int *[length];
  for(int i=0;i<length;i++){
    arr[i] = new int [length];
  }
  arr[0][0] = 64;
  arr[0][1] = 29;
  arr[0][2] = 25;
  arr[0][3] = 71;
  arr[1][0] = 9;
  arr[1][1] = 51;
  arr[1][2] = 0;
  arr[1][3] = 32;
  arr[2][0] = 50;
  arr[2][1] = 43;
  arr[2][2] = 52;
  arr[2][3] = 80;
  arr[3][0] = 8;
  arr[3][1] = 10;
  arr[3][2] = 2;
  arr[3][3] = 16;
  hungarian(arr, length);
  for(int i=0;i<length;i++){
    for(int j=0;j<length;j++){
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
