#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting
{

  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right); // Worst-Case: O(n�) | Nicht Stabil
  void InsertionSort(vector<int>& arr); // Worst-Case: O(n�/2) | Stabil und nat�rlich
  void HybridQuickSort(vector<int>& arr, int left, int right);
  
  //************
  // MergeSort *
  //************
  void Merge(vector<int> &a, vector<int> &b,int low, int pivot, int high);	// Worst-Case: O(n log n) | Stabil und nat�rlich
  void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

  //************************
  // Natuerliche Mergesort *
  //************************
  void natMerge(vector<int>& a, vector<int>& b, int low, int pivot, int high);
  void natMergeSort(vector<int> &a, vector<int> &b);

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n); // Worst-Case: O(n log n) | Nicht stabil aber nat�rlich
  void percUp(vector<int>& a, int p, int r);

  //************
  // Shellsort *
  //************
  void ShellSort_2n(vector<int> &a, int n); // Kleiner als O(n�) [O(n^1.25)] aber gr��er als O(n log n) | Nicht Stabil
  void ShellSort_3n(vector<int> &a, int n);

  //*******************
  // Helper functions *
  //*******************
  void randomizeVector(vector<int> &array, int n);
  
 }
#endif 
