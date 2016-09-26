#include "multi_matrix.h"
vector<vector<int> > multi_matrix(vector<vector<int> > &MatrixA, vector<vector<int> > & MatrixB)
{
        int nraw=MatrixA.size();
        int ncol=MatrixB[0].size();
        vector<vector<int> > MatrixC(nraw,vector<int>(ncol,0));
        for (int i = 0; i < nraw; ++i)
	{
		for (int j = 0; j < ncol; ++j)
			MatrixC[i][j] = 0;
	}
	for (int i = 0; i < nraw; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			for (int k = 0; k < ncol; k++)
			{
				MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
			}
		}
	}
	for (int i = 0; i < nraw; ++i)
	{
		for (int j = 0; j < ncol; ++j)
			cout << MatrixC[i][j]<<'\t';
		cout << endl<<endl;
	}
	return MatrixC;
}
/*
int main(){
	vector<vector<int> >MatrixA(3,vector<int>(3,1));
	vector<vector<int> >MatrixB(3,vector<int>(3,1));	
	multi_matrix(MatrixA,MatrixB);
}*/
