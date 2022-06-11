#include "sorting.h"

namespace sorting {

	//************
	// QuickSort *
	//************   

	template<typename T>
	int partition(std::vector<T>& A, int p, int r)	// Hier teilen/sortieren wir so gesagt
	{
		int x = A[r];
		int i = p - 1;
		for (auto j = p; j < r; j++)
		{
			if (A[j] <= x)
			{
				++i;
				std::swap(A[i], A[j]);
			}
		}
		std::swap(A[i + 1], A[r]);
		return i + 1;
	}

	void QuickSort(vector<int>& arr, int left, int right)
	{
		if (left < right)
		{
			int q = partition(arr, left, right);
			QuickSort(arr, left, q - 1);
			QuickSort(arr, q + 1, right);
		}
	}

	void InsertionSort(vector<int>& arr)
	{
		for (int i = 1; i < arr.size(); ++i)
		{
			int temp = arr[i];	// Element was eingefügt werden soll.
			
			// Wir suchen die einzufügende Stelle.
			int j = i-1;
			while (j >= 0 && arr[j] > temp)
			{
				arr[j + 1] = arr[j];
				j--;
			}

			arr[j + 1] = temp;	// Wir fügen das Element an der richtigen Stelle ein.
		}
	}

	void HybridQuickSort(vector<int>& arr, int left, int right)		// Für kleine n lieber InsertionSort, sonst QuickSort
	{
		size_t n = arr.size();
		if (n >= 10)	// "Cross-Over-Point"
		{
			QuickSort(arr, left, right);
		}
		else
		{
			InsertionSort(arr);
		}
	}

	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int i, j, k;

		//Wir füllen b auf, mit Inhalt aus a.
		for (i = low; i <= high; i++)
		{
			b[i] = a[i];
		}

		i = low;
		j = pivot + 1;
		k = low;
		//Wir überprüfen beide Seiten von i und j. Das kleine kommt in a[k] rein.
		while (i <= pivot && j <= high)
		{
			if (b[i] <= b[j])
			{
				a[k++] = b[i++];
			}
			else
			{
				a[k++] = b[j++];
			}
		}

		//Falls im ersten Array noch Inhalt ist, dann kopieren wir das in a rein.
		while (i <= pivot)
		{
			a[k++] = b[i++];
		}
	}

	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if (low < high)
		{
			int mitte = (low + high) / 2;

			MergeSort(a, b, low, mitte);
			MergeSort(a, b, mitte + 1, high);
			Merge(a, b, low, mitte, high);
		}
	}

	void natMerge(vector<int>& a, vector<int>& b, int low, int pivot, int high)	// Beachtet bereits vorsortierte Folgen.
	{
		int links = low;
		int rechts = pivot + 1;
		for (int i = low; i <= high; i++)
		{
			if (rechts > high || (links <= pivot && a[links] <= a[rechts])) // Links < als Rechts
			{
				b[i] = a[links++];
			}
			else if (links > pivot || (rechts <= high && a[rechts] <= a[links])) // Rechts ist kleiner als Links
			{
				b[i] = a[rechts++];
			}
		}

		for (int i = low; i <= high; i++) // Einfach kopiere was wir sortiert haben
		{
			a[i] = b[i];
		}
	}

	void natMergeSort(vector<int>& a, vector<int>& b)
	{
		int links = 0;
		int rechts = a.size() - 1;
		bool sortiert = false;
		int l = 0;
		int r = rechts;

		while (!sortiert)
		{
			sortiert = true;
			links = 0;
			while (links < rechts)
			{
				l = links;
				while (l < rechts && a[l] <= a[l + 1]) // So lange eine Reihenfolge bereits sortiert ist.
				{
					l++;
				}

				r = l + 1;
				while (r == rechts - 1 || r < rechts && a[r] <= a[r + 1]) // Erneut runs finden.
				{
					r++;
				}

				if (r <= rechts)
				{
					natMerge(a, b, links, l, r); // Sortieren zwischen durch.
					sortiert = false;
				}
				links = r + 1;
			}
		}
	}

	/*
	########## Beispiel ##########
	#	Start -> 6 4 2 1 7		 #
	#		  -> 4 6 2 1 7		 #
	#		  -> 4 6 1 2 7		 #
	#	Ende  -> 1 2 4 6 7		 #
	##############################
	*/


	//************
	// Heapsort  *
	//************


	void percUp(vector<int>& a, int p, int r)	// MaxHeap
	{
		int links = 2 * p + 1;
		int rechts = 2 * p + 2;

		//Tausche das Maximum in den Kindern mit der Wurzel. [Falls dies groesser ist]
		if (rechts < r && a[rechts] >= a[links] && a[rechts] > a[p])
		{
			swap(a[rechts], a[p]);
			percUp(a, rechts, r);	//Ich percup den Teilbaum rekursiv. Da sich dieser geändert hat.
		}
		else if (rechts < r && a[links] > a[rechts] && a[links] > a[p])
		{
			swap(a[links], a[p]);
			percUp(a, links, r);
		}
		else if (links < r && a[links] > a[p])	//Wenn ich nur Linken Nachfolger habe, tausche ich nur wenn er groesser ist.
		{
			swap(a[links], a[p]);
			percUp(a, links, r);
		}
	}

	void HeapSort(vector<int>& a, int n)
	{
		int i = n / 2;
		while (i >= 0)
		{
			percUp(a, i, n);
			--i;
		}
		int j = n - 1;
		while (j > 0)
		{
			swap(a[0], a[j]);
			percUp(a, 0, j);
			--j;
		}
	}

	//************
	// Shellsort *
	//************
	void ShellSort_2n(vector<int>& a, int n)	// Hibbard Folge
	{
		// Bestimmte den Abstand
		int nhoch2 = 0;
		while (nhoch2 <= n)
		{
			nhoch2 = 2 * nhoch2 + 1;
		}
		for (int abstand = nhoch2 / 2; abstand > 0; abstand /= 2)	// Insertion Sort der Elemente mit Abstand.
		{
			for (int i = abstand; i < n; i++)
			{
				int temp = a.at(i);
				int j = i;

				for (; j >= abstand && temp < a.at(j - abstand); j -= abstand)
				{
					a.at(j) = a.at(j - abstand);
				}
				a.at(j) = temp;
			}
		}
	}


	void ShellSort_3n(vector<int>& a, int n)	// Abstandsfolge
	{
		// Bestimmte den Abstand
		int nhoch3 = 0;
		while (nhoch3 <= n)
		{
			nhoch3 = 3 * nhoch3 + 1;
		}

		for (int abstand = nhoch3 / 2; abstand > 0; abstand /= 2)	 // Insertion Sort der Elemente mit Abstand.
		{
			for (int i = abstand; i < n; i++)
			{
				int temp = a.at(i);
				int j = i;
				
				for (; j >= abstand && temp < a.at(j - abstand); j -= abstand)
				{
					a.at(j) = a.at(j - abstand);
				}
				a.at(j) = temp;
			}
		}
	}


	void randomizeVector(vector<int>& array, int n)
	{
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}
}