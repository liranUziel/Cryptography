
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>
#define ROUND 4
#define _CRT_SECURE_NO_WARNINGS
//globals
typedef union
{
	struct
	{
		unsigned int a1 : 1;
		unsigned int a2 : 1;
		unsigned int a3 : 1;
		unsigned int a4 : 1;
		unsigned int a5 : 1;
		unsigned int a6 : 1;
		unsigned int a7 : 1;
		unsigned int a8 : 1;
	}bit;
	unsigned char a;
}bit_8;

typedef union
{
	struct
	{
		unsigned int a1 : 1;
		unsigned int a2 : 1;
		unsigned int a3 : 1;
		unsigned int a4 : 1;
		unsigned int a5 : 1;
		unsigned int a6 : 1;
	}bit;
	unsigned char a : 6;
}bit_6;

typedef union
{
	struct
	{
		unsigned int a1 : 1;
		unsigned int a2 : 1;
		unsigned int a3 : 1;
		unsigned int a4 : 1;
		unsigned int a5 : 1;
		unsigned int a6 : 1;
		unsigned int a7 : 1;
		unsigned int a8 : 1;
		unsigned int a9 : 1;
		unsigned int a10 : 1;
		unsigned int a11 : 1;
		unsigned int a12 : 1;
	}bit;
	unsigned int a : 12;
}bit_12;

typedef union
{
	struct
	{
		unsigned int a1 : 1;
		unsigned int a2 : 1;
		unsigned int a3 : 1;
		unsigned int a4 : 1;
		unsigned int a5 : 1;
		unsigned int a6 : 1;
		unsigned int a7 : 1;
		unsigned int a8 : 1;
		unsigned int a9 : 1;
		unsigned int a10 : 1;
		unsigned int a11 : 1;
		unsigned int a12 : 1;
		unsigned int a13 : 1;
		unsigned int a14 : 1;
		unsigned int a15 : 1;
		unsigned int a16 : 1;
	}bit;
	unsigned int a : 16;
}bit_16;

int shift_vercor[] = { 1,1,2,2 };

int IP_MATRIX[] = { 8, 13, 4, 9,
16, 5, 12, 1,
7, 14, 3, 10,
15, 6, 11, 2 };

int IP_INV_MATRIX[] = { 8, 16, 11, 3,
6, 14, 9, 1,
4, 12, 15, 7,
2, 10, 13, 5 };

int S_BOX[] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 };

//functions
char* subText(char* text, int start, int end);
char * CBC_encryption(char * plaintext_str, int k, char *IV);
char* block_encryption(char * plaintext, int k);
unsigned int get_bit8(bit_8 a, int index);
void set_bit8(bit_8* x, int index, unsigned int num);
unsigned int get_bit6(bit_6 a, int index);
void set_bit6(bit_6* x, int index, unsigned int num);
unsigned int get_bit12(bit_12 a, int index);
void set_bit12(bit_12* x, int index, unsigned int num);
unsigned int get_bit16(bit_16 a, int index);
void set_bit16(bit_16* x, int index, unsigned int num);
void IP(bit_16 x, bit_16 *y,int type);
void split_R_L(bit_8 *R, bit_8 *L, bit_16 to_split);
void Extend(bit_8 orignal, bit_12 *Extend);
void s_box(bit_6 L, bit_6 R, bit_8 *s_output);
void split_6(bit_6 *R, bit_6 *L, bit_12 to_split);
void feistel(bit_8 R, bit_12 k, bit_8 *to_save);

//program

void main()
{
	char ret_msg[2] = "tu";
	int key = 3524;
	

	printf("this is the orignal text (2 letters) is :%c%c\n", ret_msg[0], ret_msg[1]);
	//CBC_encryption("liran", 12, "tr");
	block_encryption(ret_msg, key);
	system("pause");
}

void IP(bit_16 x, bit_16 *y, int type)
{
	int index;
	int i;
	if (type == 1)
	{
		for (i = 0; i < 16; i++)
		{
			index = get_bit16(x, IP_MATRIX[i]);
			set_bit16(y, i + 1, index);
		}
	}
	else
	{
		for (i = 0; i < 16; i++)
		{
			index = get_bit16(x, IP_INV_MATRIX[i]);
			set_bit16(y, i + 1, index);
		}
	}

}

unsigned int get_bit8(bit_8 a, int index)
{
	switch (index)
	{
	case 8:
		return a.bit.a1;
		break;
	case 7:
		return a.bit.a2;
		break;
	case 6:
		return a.bit.a3;
		break;
	case 5:
		return a.bit.a4;
		break;
	case 4:
		return a.bit.a5;
		break;
	case 3:
		return a.bit.a6;
		break;
	case 2:
		return a.bit.a7;
		break;
	case 1:
		return a.bit.a8;
		break;
	default:
		break;
	}
}

void set_bit8(bit_8* x, int index, unsigned int num)
{
	switch (index)
	{
	case 8:
		(*x).bit.a1 = num;
		break;
	case 7:
		(*x).bit.a2 = num;
		break;
	case 6:
		(*x).bit.a3 = num;
		break;
	case 5:
		(*x).bit.a4 = num;
		break;
	case 4:
		(*x).bit.a5 = num;
		break;
	case 3:
		(*x).bit.a6 = num;
		break;
	case 2:
		(*x).bit.a7 = num;
		break;
	case 1:
		(*x).bit.a8 = num;
		break;
	default:
		break;
	}
}

unsigned int get_bit6(bit_6 a, int index)
{
	switch (index)
	{
	case 6:
		return a.bit.a1;
		break;
	case 5:
		return a.bit.a2;
		break;
	case 4:
		return a.bit.a3;
		break;
	case 3:
		return a.bit.a4;
		break;
	case 2:
		return a.bit.a5;
		break;
	case 1:
		return a.bit.a6;
		break;
	default:
		break;
	}
}

void set_bit6(bit_6* x, int index, unsigned int num)
{
	switch (index)
	{
	case 6:
		(*x).bit.a1 = num;
		break;
	case 5:
		(*x).bit.a2 = num;
		break;
	case 4:
		(*x).bit.a3 = num;
		break;
	case 3:
		(*x).bit.a4 = num;
		break;
	case 2:
		(*x).bit.a5 = num;
		break;
	case 1:
		(*x).bit.a6 = num;
		break;
	default:
		break;
	}
}

unsigned int get_bit12(bit_12 a, int index)
{
	switch (index)
	{
	case 12:
		return a.bit.a1;
		break;
	case 11:
		return a.bit.a2;
		break;
	case 10:
		return a.bit.a3;
		break;
	case 9:
		return a.bit.a4;
		break;
	case 8:
		return a.bit.a5;
		break;
	case 7:
		return a.bit.a6;
		break;
	case 6:
		return a.bit.a7;
		break;
	case 5:
		return a.bit.a8;
		break;
	case 4:
		return a.bit.a9;
		break;
	case 3:
		return a.bit.a10;
		break;
	case 2:
		return a.bit.a11;
		break;
	case 1:
		return a.bit.a12;
		break;
	default:
		break;
	}
}

void set_bit12(bit_12* x, int index, unsigned int num)
{
	switch (index)
	{
	case 12:
		(*x).bit.a1 = num;
		break;
	case 11:
		(*x).bit.a2 = num;
		break;
	case 10:
		(*x).bit.a3 = num;
		break;
	case 9:
		(*x).bit.a4 = num;
		break;
	case 8:
		(*x).bit.a5 = num;
		break;
	case 7:
		(*x).bit.a6 = num;
		break;
	case 6:
		(*x).bit.a7 = num;
		break;
	case 5:
		(*x).bit.a8 = num;
		break;
	case 4:
		(*x).bit.a9;
		break;
	case 3:
		(*x).bit.a10;
		break;
	case 2:
		(*x).bit.a11;
		break;
	case 1:
		(*x).bit.a12;
		break;
	default:
		break;
	}
}

unsigned int get_bit16(bit_16 a, int index)
{
	switch (index)
	{
	case 16:
		return a.bit.a1;
		break;
	case 15:
		return a.bit.a2;
		break;
	case 14:
		return a.bit.a3;
		break;
	case 13:
		return a.bit.a4;
		break;
	case 12:
		return a.bit.a5;
		break;
	case 11:
		return a.bit.a6;
		break;
	case 10:
		return a.bit.a7;
		break;
	case 9:
		return a.bit.a8;
		break;
	case 8:
		return a.bit.a9;
		break;
	case 7:
		return a.bit.a10;
		break;
	case 6:
		return a.bit.a11;
		break;
	case 5:
		return a.bit.a12;
		break;
	case 4:
		return a.bit.a13;
		break;
	case 3:
		return a.bit.a14;
		break;
	case 2:
		return a.bit.a15;
		break;
	case 1:
		return a.bit.a16;
		break;
	default:
		break;
	}
}

void set_bit16(bit_16* x, int index, unsigned int num)
{
	switch (index)
	{
	case 16:
		(*x).bit.a1 = num;
		break;
	case 15:
		(*x).bit.a2 = num;
		break;
	case 14:
		(*x).bit.a3 = num;
		break;
	case 13:
		(*x).bit.a4 = num;
		break;
	case 12:
		(*x).bit.a5 = num;
		break;
	case 11:
		(*x).bit.a6 = num;
		break;
	case 10:
		(*x).bit.a7 = num;
		break;
	case 9:
		(*x).bit.a8 = num;
		break;
	case 8:
		(*x).bit.a9 = num;
		break;
	case 7:
		(*x).bit.a10 = num;
		break;
	case 6:
		(*x).bit.a11 = num;
		break;
	case 5:
		(*x).bit.a12 = num;
		break;
	case 4:
		(*x).bit.a13 = num;
		break;
	case 3:
		(*x).bit.a14 = num;
		break;
	case 2:
		(*x).bit.a15 = num;
		break;
	case 1:
		(*x).bit.a16 = num;
		break;
	default:
		break;
	}
}

void split_R_L(bit_8 *R, bit_8 *L, bit_16 to_split)
{
	int i;
	for (i = 1; i <= 8; i++)
	{
		set_bit8(L, i, get_bit16(to_split, i));
	}
	for (i = 9; i <= 16; i++)
	{
		set_bit8(R, i - 8, get_bit16(to_split, i));
	}
}

void Extend(bit_8 orignal, bit_12 *Extend)
{
	(*Extend).a = orignal.a;
	(*Extend).a = (*Extend).a * 4;
	(*Extend).bit.a1 = orignal.bit.a2;
	(*Extend).bit.a2 = orignal.bit.a8;
	(*Extend).bit.a11 = orignal.bit.a7;
	(*Extend).bit.a12 = orignal.bit.a1;
}

void split_6(bit_6 *R, bit_6 *L, bit_12 to_split)
{
	int i;
	for (i = 1; i <= 6; i++)
	{
		set_bit6(L, i, get_bit12(to_split, i));
	}
	for (i = 7; i <= 12; i++)
	{
		set_bit6(R, i - 6, get_bit12(to_split, i));
	}

}

void s_box(bit_6 L, bit_6 R, bit_8 *s_output)
{
	int row, col;
	row = L.bit.a6 * 2 + L.bit.a1;
	col = L.bit.a2 + L.bit.a3 * 2 + L.bit.a4 * 4 + L.bit.a5 * 8;
	(*s_output).a = S_BOX[row * 16 + col] << 4;
	row = R.bit.a6 * 2 + R.bit.a1;
	col = R.bit.a2 + R.bit.a3 * 2 + R.bit.a4 * 4 + R.bit.a5 * 8;
	(*s_output).a = (*s_output).a + S_BOX[row * 16 + col];
}

void feistel(bit_8 R, bit_12 k, bit_8 *to_save)
{
	bit_12 eR;
	bit_6 sL, sR;
	Extend(R, &eR);
	eR.a = eR.a ^ k.a;
	split_6(&sR, &sL, eR);
	s_box(sL, sR, to_save);
}

char* block_encryption(char * plaintext_str, int key)
{
	bit_16 IP_X, to_ret, joint_16,plaintext;
	bit_8 left, right, next_left, next_right;
	bit_8 fR;
	bit_12 sh_key,k;
	char letter[3];
	int i,j;
	//Convert string to int/bit represantion
	plaintext.a = plaintext_str[0];
	plaintext.a = plaintext.a << 8;
	plaintext.a = plaintext.a + plaintext_str[1];

	//Conver the Key in a bit represantion
	k.a = key;

	// first part of encryption - initial permutation
	IP(plaintext, &IP_X, 1);
	//second part - take the 2 half and work with each one differently
	split_R_L(&right, &left, IP_X);

	sh_key.a = k.a;//work on the key and keep the changes

	//Start of DES we can make more round by changing the ROUND number
	for (i = 0; i < ROUND; i++)
	{
		//make a ciclyc shift to the left by shift_vector[i] times
		for (j = 0; j < shift_vercor[i]; j++)
		{
			if (sh_key.a & 2048) // to check the MSB of 12 digit value if one we add 1 in the start
			{
				sh_key.a = sh_key.a << 1;
				sh_key.a++;
			}
			else
			{
				sh_key.a = sh_key.a << 1;
			}
		}
		//call to - feistel
		feistel(right, sh_key, &fR);
		if (i == ROUND - 1)
		{
			//final iteration doesnt need replacement
			next_left.a = left.a ^ fR.a;
			next_right.a = right.a;
			right.a = next_right.a;// next left and next right were used to ensure no data lose occured
			left.a = next_left.a;
		}
		else
		{
			//every other iteration does not need replacement
			next_left.a = right.a;
			next_right.a = left.a ^ fR.a;
			right.a = next_right.a;
			left.a = next_left.a;
		}
	}
	to_ret.a = left.a;
	to_ret.a = to_ret.a << 8;
	to_ret.a = to_ret.a + right.a;
	//finaly invert initial permutation IP^-1
	IP(to_ret, &joint_16, -1);
	split_R_L(&right, &left, joint_16);
	letter[0] = left.a;
	letter[1] = right.a;
	letter[2] = '\0';
	printf("end %c%c\n",letter[0],letter[1]);
	//return "ok";
	return letter;
}

char * CBC_encryption(char * plaintext_str, int k,char *IV)
{
	int len = strlen(plaintext_str);
	int Iteration = len / 2;
	int i;
	char *ptext = "";
	
	bit_16 iv,plaintext;
	bit_8 high, low;
	
	iv.a = IV[0];
	iv.a = iv.a << 8;
	iv.a = iv.a + IV[1];
		
	for (i = 0; i < Iteration; i++) 
	{
		ptext = subText(plaintext_str, i, i + 2);
		plaintext.a = ptext[0];
		plaintext.a = plaintext.a << 8;
		plaintext.a = plaintext.a + ptext[1];
		plaintext.a = plaintext.a ^ iv.a;
		split_R_L(&low, &high, plaintext);
		ptext[0] = high.a;
		ptext[0] = low.a;
		ptext = block_encryption(ptext, k);
		iv.a = ptext[0];
		iv.a = iv.a << 8;
		iv.a = iv.a + ptext[0];
	}

	

	return "ok";
}

char* subText(char* text, int start, int end)
{
	int i, k = 0;
	char *sub = (char*)malloc((end - start + 1) * sizeof(char));
	for (i = start; i < end; i++)
	{
		sub[k] = *(text + i);
		k++;
	}
	sub[k] = '\0';
	return sub;
}