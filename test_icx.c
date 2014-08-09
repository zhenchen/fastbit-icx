#include<stdio.h>
#include<stdlib.h>

int WAH_TYPE = 3;
int COMPAX_TYPE = 6;
int SECOMPAX_TYPE = 19;
int ICX_TYPE = 25;

int main()
{
	
	/*ofstream result_wah;
	result_wah.open("codebook.txt");
	ifstream idxin;
	idxin.open("x.idx",ios::binary);
	char tmp;
	for(int i=0 ; i<6 ; i++)
	{
		idxin>>tmp;
	}*/
	int base_num;
	int total_column;
	unsigned int *offset;
	int *type = (int *)malloc(sizeof(unsigned int)* ICX_TYPE);
	int begin,end;
	char tmp;
	unsigned int codeword;
	int j,i;
	FILE * fin;
	FILE * fout;
	for(j =0 ;j<2 ;j++)
	{
		for(i = 0 ;i <ICX_TYPE; i++)
	{
		type[i] = 0;
	}
		if(j==0)
		{
			fin = fopen("start_t.idx","rb");
			fout = fopen("result_start_icx.txt", "w");
		}
		else
		{
			fin = fopen("end_t.idx","rb");
			fout = fopen("result_end_icx.txt", "w");
		}
	
	
	for(i=0 ;i<3;i++)
	fread(&codeword, sizeof(unsigned int), 1, fin);
	fread(&total_column, sizeof(unsigned int), 1, fin);
	offset = (unsigned int *)malloc(sizeof(unsigned int) * (total_column + 1));
	for(i = 0;i<= total_column ; i++)
	{
		fread(&offset[i], sizeof(unsigned int), 1, fin);
	}
	fread(&codeword, sizeof(unsigned int), 1, fin);
	while(!feof(fin))
	{
		if((codeword & 0x80000000) ==0)
		{
			type[24]++;
		}
		else
		{
			switch((codeword & 0xfc000000) >> 26)
			{
			case 32:type[1]++;break;   //0-fill
			case 33:type[0]++;break;   //1-fill
			default:switch ((codeword & 0xf0000000)>>28)
			{
			case 12: 
			{ //0L-F-1L
				if(codeword & 0x00800000) //0L-1F-1L
				{
					type[3]++;
				}
				else
				{//0L-0F-1L
					type[2]++;
				}
				break;
			}
			case 13:
			{//1L-F-0L
				if(codeword & 0x00800000) //1L-1F-0L
				{
					type[5]++;
				}
				else
				{//1L-0F-0L
					type[4]++;
				}
				break;
			}
			case 10:
			{//0L-F-0L
				if(codeword & 0x00800000) //0L-1F-0L
				{
					type[7]++;
				}
				else
				{//0L-0F-0L
					type[6]++;
				}
				break;
			}
			case 11:
			{//1L-F-1L
				if(codeword & 0x00800000) //1L-1F-1L
				{
					type[9]++;
				}
				else
				{//1L-0F-1L
					type[8]++;
				}
				break;
			}
			case 14:
				{
					switch((codeword & 0x0c000000)>> 26)
					{
					case 0:type[10]++;break;	//0F-0L-0F
					case 1:type[12]++;break;	//0F-0L-1F
					case 2:type[11]++;break;	//0F-1L-0F
					case 3:type[13]++;break;	//0F-1L-1F
					}
					break;
				}
			case 15:
				{
					switch((codeword & 0x0c000000)>> 26)
					{
						case 0:type[14]++;break;	//1F-0L-0F
						case 1:type[16]++;break;	//1F-0L-1F
						case 2:type[15]++;break;	//1F-1L-0F
						case 3:type[17]++;break;	//1F-1L-1F
					}
					break;
				}
				
			case 9:
				{
					if(codeword & 0x00800000)
					{//0NL2-1F
						type[18]++;
					}
					else
					{//0NL2-0F
						type[19]++;
					}
					break;
				}
			default:
				{
					switch((codeword & 0x06000000)>>25)
					{
					case 0:type[20]++;break;   //L0-F0
					case 1:type[21]++;break;   //L0-F1
					case 2:type[22]++;break;   //L1-F0
					default:type[23]++;break;   //L1-F1
					}
					break;
				}
					}
			}
		}
		fread(&codeword, sizeof(unsigned int), 1, fin);
	}
	
	fclose(fin);
	for(i=0; i<ICX_TYPE; i++)
	{
		switch(i)
		{
		case 0:fprintf( fout,"1-Fill:");break;
		case 1:fprintf( fout,"0-Fill:");break;
		case 2:fprintf( fout,"0L-0F-1L:");break;
		case 3:fprintf( fout,"0L-1F-1L:");break;
		case 4:fprintf( fout,"1L-0F-0L:");break;
		case 5:fprintf( fout,"1L-1F-0L:");break;
		case 6:fprintf( fout,"0L1-0F-0L2:");break;
		case 7:fprintf( fout,"0L1-1F-0L2:");break;
		case 8:fprintf( fout,"1L1-0F-1L2:");break;
		case 9:fprintf( fout,"1L1-1F-1L2:");break;
		case 10:fprintf( fout,"0F1-0L-0F2:");break;
		case 11:fprintf( fout,"0F1-1L-0F2:");break;
		case 12:fprintf( fout,"0F1-0L-1F2:");break;
		case 13:fprintf( fout,"0F1-1L-1F2:");break;
		case 14:fprintf( fout,"1F1-0L-0F2:");break;
		case 15:fprintf( fout,"1F1-1L-0F2:");break;
		case 16:fprintf( fout,"1F1-0L-1F2:");break;
		case 17:fprintf( fout,"1F1-1L-1F2:");break;
		case 18:fprintf( fout,"0NL2-1F:");break;
		case 19:fprintf( fout,"0NL2-0F:");break;
		case 20:fprintf( fout,"0L-0F:");break;
		case 21:fprintf( fout,"0L-1F:");break;
		case 22:fprintf( fout,"1L-0F:");break;
		case 23:fprintf( fout,"1L-1F:");break;
		case 24:fprintf( fout, "literal:");break;
		}
		fprintf(fout, "%d\n", type[i]); 
	}
	fclose(fout);
	}
	return 0;

}

