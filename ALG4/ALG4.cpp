#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node
{
	float num;
	char sign;
	Node* left;
	Node* right;
};


int Prior(char a)
{
	switch (a)
	{
	case '*':
	case '/':
		return 3;
	case '-':
	case '+':
		return 2;
	default: return 10;
	}

}

Node* New(float data, char ch) {
	Node* V;
	V = (Node*)malloc(sizeof(Node));
	V->num = data;
	V->sign = ch;
	V->left = V->right = NULL;
	return V;
};

Node* MakeTree(int first, int last, char* mass) {
	int MinPrior = 10, i, k = -1, prt;
	int nest = 0; 
	Node* Tree = New(-1, '0');
	if (first == last) {
		Tree->num = atof(&mass[first]);
		Tree->left = NULL;
		Tree->right = NULL;
		return Tree;
	}
	for (i = first; i < last; i++){
		if (mass[i] == '(')
			nest++;
		if (mass[i] == ')')
			nest--;
		if (nest == 0) {
			prt = Prior(mass[i]);
			if (prt <= MinPrior) {
				MinPrior = prt;
				k = i;
			}
		}
	}
	if (k == -1)
		return MakeTree(first + 1, last - 1, mass);
	if (MinPrior == 10)
		Tree->num = mass[k];
	else {
		Tree->sign = mass[k];
	}
	Tree->left = MakeTree(first, k - 1, mass);
	Tree->right = MakeTree(k + 1, last, mass);
	return Tree;
}

float CalcTree(Node* Tree)
{
	float num1, num2;
	if (Tree->left == NULL)
		return Tree->num;
	num1 = CalcTree(Tree->left);
	num2 = CalcTree(Tree->right);
	switch (Tree->sign) {
	case '+':
		return num1 + num2;
		break;
	case '-':
		return num1 - num2;
		break;
	case '*': 
		return num1 * num2;
		break;
	case '/':
		return num1 / num2;
	}
}

void Print_pre(Node* v) {
	if (v) {
		if (v->num != -1)
			printf("%1.0f ", v->num);
		else
			printf("%c ", v->sign);
		Print_pre(v->left);
		Print_pre(v->right);
	}
}

void Print_in(Node* v) {
	if (v) {
		Print_in(v->left);
		if (v->num != -1)
			printf("%1.0f ", v->num);
		else
			printf("%c ", v->sign);
		Print_in(v->right);
	}
}

void Print_post(Node* v) {
	if (v) {
		Print_post(v->left);
		Print_post(v->right);
		if (v->num != -1)
			printf("%1.0f ", v->num);
		else
			printf("%c ", v->sign);
	}
}


int main() {
	setlocale(LC_ALL, "Rus");
	FILE* fp;
	fp = fopen("Text.txt", "r");
	char str[30];
	fgets(str, 30, fp);
	printf("Введённое выражение: %s\n", str);
	int i = 0;
	while (str[i]) {
		i++;
	}
	struct Node* root = NULL;
	root = MakeTree(0, i-1, str);
	Print_pre(root);
	printf("\n");
	Print_in(root);
	printf("\n");
	Print_post(root);
	float res = CalcTree(root);
	printf("\nРезультат вычисления = %2.1f", res);
}