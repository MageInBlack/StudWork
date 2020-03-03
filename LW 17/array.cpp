#include "array.h"
using namespace std;
void input_keyboard(double** array,const int& lines,const int& columns)
{
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			cout <<"["<<i<<"]["<<j<<"] =\n" ;
			cin >> array[i][j];
		}
	}
	return;
}

int input_file_old(double** array,const int& lines,const int& columns)
{
	FILE* input;
	int i=0;
	int n=lines*columns;
	if (input=fopen("input.txt","r")) for (i=0;!feof(input)&&i<n;i++) fscanf(input,"%lf",&array[i/lines][i%columns]);
	else {fclose(input);return -1;}
	fclose(input);
	if (i!=n) return -2;
	return 0;
}
int input_file_old_binary(double** array,const int& lines,const int& columns)
{
	FILE* input;
	int i=0;
	int n=lines*columns;
	if (input=fopen("input.bin","rb")) for (i=0;!feof(input)&&i<n;i++) fread(&array[i/columns][i%columns],sizeof(array[0][0]),1,input);
	else {fclose(input);return -1;}
	fclose(input);
	if (i!=n) return -2;
	return 0;
}
int input_file(double** array,const int& lines,const int& columns)
{
	ifstream input;
	int i=0,n=lines*columns;
	input.open("input.txt");
	if (input.good()) for (i=0;(input.peek()!=EOF)&&(i<n);i++) input >> array[i/lines][i%columns];
	else {input.close();return -1;}
	input.close();
	if (i!=n) return -2;
	return 0;
}
int input_file_binary(double** array,const int& lines,const int& columns)
{
	ifstream input;
	int i=0,n=lines*columns;
	input.open("input.bin", ios::binary|ios::in);
	if (input.good()) for (i=0;(input.peek()!=EOF)&&(i<n);i++) input.read((char*)&array[i/columns][i%columns], sizeof(array[0][0]));
	else {input.close();return -1;}
	input.close();
	if (i!=n) return -2;
	return 0;
}
void input_random(double** array,const int& lines,const int& columns)
{
	int left,right;
	do
	{
		cout<< "Введите левый и правый интервалы (целые)\n";
		cin>> left>>right;
	} while (left>=right);
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			array[i][j]=rand()%(right-left+1)+left;
		}
	}
	return;
}
void input_formula(double** array,const int& lines,const int& columns)
{
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			if (i!=j)
			{
				if (i<j) array[i][j]=1./(i+j-1);
				else array[i][j]=1./(1-i-j);
			}
			else array[i][j]=0;
		}
	}
	return;
}

void output_file_old(double** array,const int& lines,const int& columns)
{
	FILE* output;
	if (output=fopen("output.txt","w"))
	{
		for (int i=0;i<lines;i++)
		{
			for (int j=0;j<columns;j++)
			{
				fprintf(output,"%10.4lf ",array[i][j]);
			}
			fprintf(output,"\n");
		}
	}
	fclose(output);
	return;
}
void output_file_old_binary(double** array,const int& lines,const int& columns)
{
	FILE* output;
	if (output=fopen("output.bin","wb"))
	{
		for (int i=0;i<lines;i++)
		{
			for (int j=0;j<columns;j++)
			{
			fwrite(&array[i][j],sizeof(array[0][0]),1,output);
			}
		}
	}
	fclose(output);
	return;
}
void output_file(double** array,const int& lines,const int& columns)
{
	ofstream output;
	output.open("output.txt");
	
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			output.width(10);
			output <<array[i][j]<<" ";
		}
		output <<endl;
	}
	output.close();
	return;
}
void output_file_binary(double** array,const int& lines,const int& columns)
{
	ofstream output;
	output.open("output.bin",ios::binary|ios::out);
	
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			output.write((char*)&array[i][j],sizeof(array[0][0]));
		}
	}
	output.close();
	return;
}


void work_array()
{
	int lines,columns,sw,error=0,sum,max_sum;
	
	do
	{
		cout<< "Введите размер двумерного массива\n";
		cin >> lines>>columns;
	} while (lines<1||columns<1);
	double** array = new double*[lines];
	double* lines_sum = new double[lines];
	for(int i=0;i<lines;i++) array[i] = new double[columns];
	
	
	do
	{
		cout<<"Введите режим ввода\n1.С клавиатуры\n2.Файл (старый)\n3.Файл\n4.Рандом из диапазона\n5.по формуле\n6.Файл (старый бинарный)\n7.Файл (бинарный)\n";
		cin >> sw;
	}while (sw<1||sw>7);
	
	switch(sw)
	{
		case 1:input_keyboard(array,lines,columns);break;
		case 2:error=input_file_old(array,lines,columns);break;
		case 3:error=input_file(array,lines,columns);break;
		case 4:input_random(array,lines,columns);break;
		case 5:input_formula(array,lines,columns);break;
		case 6:error=input_file_old_binary(array,lines,columns);break;
		case 7:error=input_file_binary(array,lines,columns);break;
	}
	
	switch (error)
	{
		case -1:cout<<"Файл не найден\n";return;
		case -2:cout<<"недостаточно данных\n";return;
	}
	for (int i=0;i<lines;i++)
	{
		for (int j=0;j<columns;j++)
		{
			cout.width(10);
			cout <<array[i][j]<<" ";
		}
		cout <<endl;
	}
	/*5.	Найти сумму каждой строки. 
	Среди полученных сумм найти максимальное значение.*/
	max_sum=INT_MIN;
	for (int i=0;i<lines;i++)
	{
		sum=0;
		for (int j=0;j<columns;j++)
		{
			sum+=array[i][j];
		}
		lines_sum[i]=sum;
		if (sum>max_sum) max_sum=sum;
	}
	cout <<endl;
	for (int i=0;i<lines;i++) cout << lines_sum[i]<< endl;
	cout <<endl;
	cout << "Наибольшая сумма элементов строки: "<< max_sum<< endl;
		
	do
	{
		cout<< "Вы хотите вывести массив в файл?\n1.Да (старый)\n2.Да\n3.Да (старый бинарный)\n4.Да (бинарный)\n5.Нет\n";
		cin >> sw;
	} while (sw<1||sw>5);
	
	switch (sw)
	{
		case 1:output_file_old(array,lines,columns);break;
		case 2:output_file(array,lines,columns);break;
		case 3:output_file_old_binary(array,lines,columns);break;
		case 4:output_file_binary(array,lines,columns);break;
		default: break;
	}
	delete[] lines_sum;
	for (int i=0;i<lines;i++) delete[] array[i];
	delete[] array;
}
