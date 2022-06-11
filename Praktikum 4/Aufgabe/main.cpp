#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include <omp.h>
#include"hashtable.h"
#include "sorting.h"

using namespace std;

//benchmark functions
void benchmark_quicksort();
void benchmark_hybridquicksort();
void benchmark_mergesort();
void benchmark_heapsort();
void benchmark_shellsort_2n();
void benchmark_shellsort_3n();

void aufgabe6()
{
	int strategie = 0;
	double faktor = 0.6;

	cout << "Bitte wähle eine Kollisionsstrategie aus: " << endl
		<< "0 = Lineares Sondieren." << endl
		<< "1 = Quadratisches Sondieren." << endl
		<< "2 = Doppeltes Hashing." << endl
		<< "> ";
	cin >> strategie;

	cout << "Bitte Belegungsfaktor eingeben: ";
	cin >> faktor;

	HashTable H(10, faktor);

	H.setStrategie(strategie);

	int wert = 0;
	while (wert != -1)
	{
		cout << "Bitte den Wert eingeben [-1 = Abbruch]: ";
		cin >> wert;
		
		if (wert != -1)
		{
			H.insert(wert);
		}
	}

	cout << endl;
	H.print();
	cout << endl;
}

int main(int argc, char** argv)
{
	Catch::Session().run();


	/*std::cout << "\nPress Enter to run measurement" << std::endl;
	std::cin.get();

	benchmark_quicksort();
	benchmark_hybridquicksort();
	benchmark_mergesort();
	benchmark_heapsort();
	benchmark_shellsort_2n();
	benchmark_shellsort_3n();*/

	std::cout << "\nDruecke Enter fuer Aufgabe 6" << std::endl;
	std::cin.get();
	aufgabe6();

	/*std::cout << "\nDruecke Enter fuer Aufgabe 7" << std::endl;
	std::cin.get();
	HashTable H{1000};
	for (int i = 0; i < 200; i++)
	{
		int zahl = H.insert(rand() % 501 + 1000);
	}
	std::cout << "Kollisionen: " << H.getCollisionCount() << std::endl;*/

	system("PAUSE");
	return 0;
}


//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    dtime = omp_get_wtime();
    
	//execzute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

void benchmark_hybridquicksort() {

	//file stream
	ofstream hybridquicksort_measurement;
	hybridquicksort_measurement.open("hybridquicksort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running HybridQuicksort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::HybridQuickSort(V, 0, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		hybridquicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	hybridquicksort_measurement.close();
}

void benchmark_mergesort() {

	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> a;
	vector<int> b;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running MergeSort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(a, n/2);
		sorting::randomizeVector(b, n/2);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::MergeSort(a, b, 0, a.size()-1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	mergesort_measurement.close();
}

void benchmark_heapsort() {

	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running HeapSort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::HeapSort(V, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	heapsort_measurement.close();
}

void benchmark_shellsort_2n() {

	//file stream
	ofstream shellsort_2n_measurement;
	shellsort_2n_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running ShellSort_2n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::ShellSort_2n(V, n);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_2n_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_2n_measurement.close();
}

void benchmark_shellsort_3n() {

	//file stream
	ofstream shellsort_3n_measurement;
	shellsort_3n_measurement.open("shellsort_3n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running ShellSort_3n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::ShellSort_3n(V, n);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_3n_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_3n_measurement.close();
}