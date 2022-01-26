#include <stdio.h>
#define false 0
#define true 1
/*
int sudo[9][9]= {
  { 9,3,4,8,0,0,0,0,5 },
  { 0,2,0,0,7,1,0,0,0 },
  { 1,0,8,0,0,0,2,0,4 },
  { 0,0,0,0,9,4,6,5,0 },
  { 5,6,0,0,0,0,9,0,3 },
  { 0,0,2,3,6,0,0,0,0 },
  { 0,0,1,0,0,3,0,2,0 },
  { 0,4,0,9,0,0,0,3,0 },
  { 0,8,0,0,4,2,0,0,0 }

};

int sudo[9][9]= {
 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 },

 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 },

 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 },
 { 0,0,0  0,0,0, 0,0,0 }
}

*/

int sudo[9][9]= {
  { 0,9,2,  0,0,0, 3,0,7 },
  { 0,4,0,  0,2,0, 0,5,8 },
  { 7,0,0,  0,0,0, 0,9,0 },

  { 2,0,0,  1,0,6, 0,0,0 },
  { 0,1,0,  0,0,3, 9,8,0 },
  { 0,0,4,  8,0,0, 0,0,0 },

  { 0,2,0,  0,7,4, 0,0,0 },
  { 0,0,0,  3,0,0, 0,0,1 },
  { 9,0,0,  2,0,0, 0,0,0 }
};
int iter_count=0;



int checkfeasibility(const int i, const int j, int k) {
  // Check row,column
  int q=i/3;
  int w=j/3;
  int l, li, lj;
  for (l=0; l<9; l++) {
    // Chec row
     if (l!=i) {
       if (sudo[i][j] == sudo[l][j]) {//printf("Column feasibility check failed\n"); 
	 return false;}
    }
    //check column
    if (l!=j) {
      if (sudo[i][j] == sudo[i][l]) {//printf("Row feasibility check failed, [%i,%i] %i = [%i,%i] %i\n", i,j,sudo[i][j], i,l,sudo[i][l]); 
	return false;}
    }
    // Check Quadrant
    li = l/3 +q*3;
    lj = l%3 + w*3;

    if (li!=i && lj!=j) {
      if (sudo[i][j] == sudo[li][lj]) {//printf("Submatrix feasibility check failed\n"); 
	return false;}
    }    
  }
  return true;
}
    

int sudoiter(int pos) {
  int i=pos/9;
  int j=pos%9;
  int k;
  if (pos>=81) return true;
  if (sudo[i][j]) return sudoiter(pos+1);
  for (k=1; k<=9;k++) {
    iter_count++;
    sudo[i][j] = k;
    //printf("Testing with %i at postion [%i][%i]\n", k,i,j);
    if (checkfeasibility(i,j,k)) {
      //printf("%i at postion [%i][%i] possible, iterating\n", k,i,j);
      if (sudoiter(pos+1)) {
	return true;
      }
    }
    sudo[i][j] = 0;
  }
  return false;
}
			 

int main() {
  int i, j;
  printf("Starting iteration\n");
  if ( !sudoiter(0)) {
    printf("No solution found\n");
  }
  printf("\n\nSOLUTION (%i iterations) =================\n  ", iter_count);
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      printf("%i ", sudo[i][j]); if (!((j+1)%3)) printf(" ");
    }
    printf("\n  "); if (!((i+1)%3)) printf("\n  ");
  }
}

