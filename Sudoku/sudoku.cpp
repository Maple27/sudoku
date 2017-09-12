#include <stdio.h>  
#include <time.h>  
#include <stdlib.h> 
/**
* Coder : Maple27
* Date : 2017-09-08
* ApplicationName : sudoku
*/

int sudoku[9][9];
FILE *fp; 

/*检查数独棋盘内数字是否符合规则（即同行同列同九宫格内没有重复数字）*/
int check(int sudoku[][9], int i, int j){
	int p,q,m,n;
	int t = sudoku[i][j];
	
	//横向检查
	for (p = 0; p<9; p++)
		if (p != i && sudoku[p][j] == t)
			return 0;
	//纵向检查
	for (p = 0; p<9; p++)
		if (p != j && sudoku[i][p] == t)
			return 0;

    //九宫格内检查 
	p = i / 3;
	q = j / 3;
	for (m = p * 3; m<p * 3 + 3; m++)
		for (n = q * 3; n < q * 3 + 3; n++)
			if (m != i && n != j && sudoku[m][n] == t)
				return 0;

	//符合条件返回1 
	return 1;
}

/*输出9*9的数独棋盘*/
void sudokuPrint(int sudoku[][9]){
	int i, j; 
	for (i = 0; i < 9; i++){
		//printf("%4d", sudoku[i][0]);  
		fprintf(fp,"%d",sudoku[i][0]);  
		for (j = 1; j < 9; j++){
			//printf("%4d", sudoku[i][j]);  
    		fprintf(fp," %d",sudoku[i][j]);  
		}
		fprintf(fp,"\n");  
		printf("\n");
	}
}

/*用回溯法获取N个数独棋盘*/
int getSudoku(int N){
	int k = 0, num = 0;
	fp=fopen("sudoku.txt","w");
	while (1){
		int i = k / 9;
		int j = k % 9;
		while (1){
			sudoku[i][j]++;
			if (sudoku[i][j] == 10){
				sudoku[i][j] = 0;
				k--;
				break;
			}
			else if (check(sudoku, i, j) == 1){
				k++;
				break;
			}
		}

		if (k == 81){
			//printf("第%d个数独棋盘: \n", ++num);
			fp=fopen("sudoku.txt","a");
			sudokuPrint(sudoku);
			fprintf(fp,"\n");  
			if (num >= N){
				//printf("over!\n");
				fclose(fp);
				return 0;
			}
			k--;
		}
	}

}

int main(int argc, char ** argv){
	int i, j, t = 0, r = 1;
	char* arg1 = argv[1]; 
	int N = atoi(argv[2]);
	//错误处理 
	if(!(arg1[0] == '-' && arg1[1] == 'c')){
		printf("输入有误，请重新运行.\n");
		return 0;
	}
	if(N == 0){
		printf("输入有误，请重新运行.\n");
		return 0;
	}
	/*int N; 
	while(1){
			int l = scanf("%d",&N);
			if(l == 0){
				printf("输入有误，请重新输入.\n");
				fflush(stdin);
				continue;
			} else {
				break;
			}
	}*/
	//用当前时间使rand()获取的随机数更具有随机性 
	srand(time(0));
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			sudoku[i][j] = 0;
	sudoku[0][0]=(1+0)% 9;
	for (i = 0; i < 9; i++){
		t = (rand() + r) % 81;
		if(t == 0)
			t++;
		sudoku[t / 9][t % 9] = i + 1;
	}
	getSudoku(N);
	return 0;
}

