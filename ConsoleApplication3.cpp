﻿// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int forHelpingPerpose[1000][1000];
int oneDHelp[10][100];
// simple segment tree

/*
	fun (pos ,s ,e pos ){
	
	}
*/


void twoDsegUitl(int s, int e, int pos, int(*arr)[100][100], int x, int y,int z, int(*seg)[1000][1000]) {
	if (s == e) {
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < z; j++)
			{
				seg[pos][i][j] = arr[s][i][j];
			}
			
		}
		return;
	}
	int mid = (s + e) / 2;  
	twoDsegUitl(s, mid, 2 * pos + 1, arr, x,y,z, seg);
	twoDsegUitl(mid + 1, e, 2 * pos + 2, arr, x,y,z, seg);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < z; j++)
		{
			seg[pos][i][j] = seg[2 * pos + 1][i][j] + seg[2 * pos + 2][i][j];
		}
	}
}
void twoDseg(int(*testt)[100], int n, int m) {

	int temp = 1;
	while (temp < n) {
		temp *= 2;
	}
	temp = 2 * temp - 1;

	twoDsegUitl(0, n - 1, 0, testt, n, m, forHelpingPerpose);
}

void oneDsegUitl(int s, int e, int pos, int (*arr)[100],int n, int m,int(*seg)[1000]) {
	if (s == e) {
		for (int i = 0; i < m; i++)
		{
			seg[pos][i] = arr[s][i];
		}
		return;
	}
	int mid = (s + e) / 2;
	oneDsegUitl(s, mid, 2 * pos + 1, arr, n, m, seg);
	oneDsegUitl(mid+1,e, 2 * pos + 2, arr, n, m, seg);
	for (int  i = 0; i < m; i++)
	{
		seg[pos][i] = seg[2 * pos + 1][i] + seg[2 * pos + 2][i];
	}
}
void oneDseg(int (*testt)[100], int n, int m) {

	int temp = 1;
	while (temp < n) {
		temp *= 2;
	}
	temp = 2 * temp - 1;
	
	oneDsegUitl(0, n - 1, 0, testt, n, m, forHelpingPerpose);
}
void createUtil(int s, int e , int pos,int **arr,int *seg,int num) {
	if (s==e)
	{
		seg[pos] = arr[num][s];
		return;
	}
	int mid = (s + e) / 2;
	createUtil(s, mid, 2 * pos + 1, arr, seg,num);
	createUtil(mid+1, e, 2 * pos + 2, arr, seg,num);
	seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
}

void createSegTreeforOne(int **arr,int n , int m) {
	
	int size = 1;
	while (size<m)
	{
		size *= 2;
	}
	size = 2 * size - 1;
	for (int i = 0; i < n; i++)
	{
		createUtil(0, m - 1, 0, arr, oneDHelp[i],i);
	}
	oneDseg(oneDHelp, n, size);
}
///////

int find(int qs, int qe, int s, int e,int pos,int (*arr)[1000],int row) {

	if (qs<=s && qe>=e)
	{
		return arr[row][pos];
	}
	if (e < qs || s > qe)
		return 0;
	int mid = (s + e) / 2;
	return find(qs, qe, s, mid, 2 * pos + 1, arr,row) + find(qs, qe, mid + 1, e, 2 * pos + 2, arr,row);
}
int find2D(int qs, int qe, int s, int e, int pos, int(*arr)[1000],int qqs,int qqe,int ee) {

	if (qs <= s && qe >= e)
	{
		return find(qqs, qqe, 0, ee, 0, arr,pos);
	}
	if (e < qs || s > qe)
		return 0;
	int mid = (s + e) / 2;
	return find2D(qs,qe,s,mid,2*pos+1,arr,qqs,qqe,ee) + find2D(qs, qe, mid + 1, e, 2 * pos + 2, arr,qqs, qqe, ee);
}





int main()
{
	int temp,n,m;
	cin >> n>>m;
	int **arr = new int*[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}
	createSegTreeforOne(arr, n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			cout << forHelpingPerpose[i][j]<< " ";
		}
		cout << endl;
	}
	cout << find2D(2,4,0,n-1,0,forHelpingPerpose,2,4,m-1) <<endl;
    return 0;
}

