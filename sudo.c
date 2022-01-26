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



int checkfeasibility(const int i, const int j, const int k) {
  // Check row,column
  int q=i/3;
  int w=j/3;
  int l, li, lj;
  iter_count++;
  for (l=0; l<9; l++) {
    // Chec row
     if (l!=i) {
       //printf("Row feasibility check, [%i,%i] %i = [%i,%i] %i\n", i,j,sudo[i][j], l,j,sudo[l][j]); 
       if (k == sudo[l][j]) {//printf("Column feasibility check failed\n"); 

	 return false;}
    }
    //check column
    if (l!=j) {
      if (k == sudo[i][l]) {//printf("Row feasibility check failed, [%i,%i] %i = [%i,%i] %i\n", i,j,sudo[i][j], i,l,sudo[i][l]); 
	return false;}
    }
    // Check Quadrant
    li = l/3 +q*3;
    lj = l%3 + w*3;

    if (li!=i && lj!=j) {
      if (k == sudo[li][lj]) {//printf("Submatrix feasibility check failed\n"); 
	return false;}
    }    
  }
  //  printf("Checkfeasibility return TRUE\n");
  return true;
}
    
int nOpt[9][9];
int maxOpt;
int minOpt;

int updateNumOptions() {
  int numOpt;
  int i,j,k;
  maxOpt = 0;
  minOpt = 9;
 for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (sudo[i][j]) {
	nOpt[i][j] = 0;
	continue;
      }
      numOpt = 0;
      for (k=1; k<=9; k++) {
	numOpt += checkfeasibility(i,j,k);
	//printf("3. Checkfeasi %i %i %i: %i\n",i,j,k,checkfeasibility(i,j,k));
	//printf("2. Num options %i, Max options %i\n", numOpt, maxOpt);
      }
      nOpt[i][j] = numOpt;
      maxOpt = numOpt>maxOpt?numOpt:maxOpt;
      if (numOpt) minOpt = numOpt<minOpt?numOpt:minOpt;
      // printf("Num options %i, MinOpt %i, Max options %i\n", numOpt, minOpt, maxOpt);
    }
 }
 // printf("Min options %i, Max options %i\n", minOpt, maxOpt);
}

int getNextIter(int pos) {
  int i,j,l;
  //  return (pos+1);
  if (maxOpt == 0) return -1;
  for (l=0; l<81; l++) {
    int i=l/9;
    int j=l%9;
    //printf("Testing num options %i,%i: %i\n", i,j, nOpt[i][j]);
    if (nOpt[i][j]>0 && nOpt[i][j] <= minOpt) {printf("Next to work on; %i\n", l); return l; }
  }
  printf("ERROR: did not find next to work on,....\n");
  return -1;
}

int sudoiter(int pos) {
  int i=pos/9;
  int j=pos%9;
  int k;
  if (pos>=81) return true;
  updateNumOptions();

  if (maxOpt==0) return true;
  if (sudo[i][j]) return sudoiter(getNextIter(pos));
  // Update selection options 
  /* 
  for (k=1; k<=9;k++) {
    optnum += opt[k] = checkfeasibility(i,j,k);
  }
 
  if (optnum == 1) {sudo[i][j] = k; return true;}
  */

  for (k=1; k<=9;k++) {
    sudo[i][j] = k;
    //printf("Testing with %i at postion [%i][%i]\n", k,i,j);
    if (checkfeasibility(i,j,k)) {
      //printf("%i at postion [%i][%i] possible, iterating\n", k,i,j);
      //updateNumOptions();
      if (sudoiter(getNextIter(pos))) {
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

