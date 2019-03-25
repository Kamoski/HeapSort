#include <iostream>
#include <fstream>

class Cell
{
public:
	Cell() : value(0), sorted(false) {};
	~Cell() {};

	void setValue(long _value) { value = _value; }
	void setSorted(bool _sorted) { sorted = _sorted; }

	long getValue() { return value; }
	bool getSorted() { return sorted; }

private:
	long value;
	bool sorted;
};

class Heap{
public:
	Heap() :
		dataLength(0)
		, lastIndex(0)
		, values(nullptr)
		, valuesTemp(nullptr)
	{

	}

	~Heap()
	{
		delete[]values;
		delete[]valuesTemp;
	}

	Heap(const Heap& copy) :
		dataLength(copy.dataLength)
		, lastIndex(copy.lastIndex)
	{
		this->values = new Cell[copy.dataLength];
		this->valuesTemp = new Cell[copy.dataLength];

		for (int i = 0; i < dataLength; ++i) {
			values[i] = copy.values[i];
			valuesTemp[i] = copy.valuesTemp[i];
		}
	}
	Heap& operator = (const Heap& equals) 
	{
		dataLength = equals.dataLength;
		lastIndex = equals.lastIndex;

		delete[]values;
		delete[]valuesTemp;

		this->values = new Cell[equals.dataLength];
		this->valuesTemp = new Cell[equals.dataLength];

		for (int i = 0; i < dataLength; ++i) {
			values[i] = equals.values[i];
			valuesTemp[i] = equals.valuesTemp[i];
		}

	}

	void pushData(long _value) {
		values[lastIndex].setValue(_value);					// Add data to table and
		++lastIndex;										// set last index added
	}

	void setDataLength(long _value) {
		values = new Cell[_value];
		valuesTemp = new Cell[_value];
		dataLength = _value;
	}


	void displayHeap(int help) {
		for (int i = 0; i < dataLength-help; ++i) {		// Help is deducted so less operations are required 
														// As sorted values are on the end of table

			if (!valuesTemp[i].getSorted())							// Display only values that are not already sorted 
			std::cout << valuesTemp[i].getValue() << " ";
		}
		std::cout << std::endl;
	}

	void displayFinal() {
		for (int i = 0; i <dataLength; ++i) {						// Display sorted nums
			std::cout << values[i].getValue() << " ";
		}
		std::cout << std::endl;
	}


	void sort() {
		for (int j = 0; j < dataLength; ++j) {					// Loop by all elements in table

			for (int i = 0; i < dataLength-j; ++i) {			// Loop by all elements - elements allready sorted
				buildHeap(values[i], i);					// Add one element to Heap
			}
			if (j!=dataLength-1)						// Security measure added to make sure that
														// last element won't be displayed

			displayHeap(j);								// Display each heap created during sorting process

			values[lastIndex].setSorted(true);			// To make sure that value won't be displayed next

			swapCells(values[lastIndex], values[dataLength - j - 1]);	// So less operations is required
		}
	}

private:
	void buildHeap(const Cell& obj , int index) {
		int temp = index;					// If this cell will be one sorted to top
											// remember it's index

		valuesTemp[index] = obj;			// Add number passed to temporary heap table

		if (index == 0) {					// For first index do nothing
		}
		else {
			while 
			(
			valuesTemp[index].getValue()			// If child is greater than father 
			> 
			valuesTemp[(index - 1) / 2].getValue()
			)
			
			
			{
				swapCells(valuesTemp[index], valuesTemp[(index - 1) / 2]);		// Swap child with father	
				index = (index - 1) / 2;									// Father's index is new child index

			}
		}

		if (index == 0)					// If number added landed on top of heap, top index is index of
										// number added
			lastIndex = temp;
	}

	void swapCells( Cell& cellOne,  Cell& cellTwo) {
		Cell temp;
		temp = cellOne;
		cellOne = cellTwo;
		cellTwo = temp;
	}

	long dataLength;
	Cell *values;
	Cell *valuesTemp;
	int lastIndex;

};

int main()
{
	std::ifstream inf;
	//std::istream&in = inf;				// Section dealing with console/file i/o
	std::istream&in = std::cin;
	
	long numOfCases, numsInCase;
	long oneNum;

	std::cin >> numOfCases;					// Read number of cases

	Heap* sortUS = new Heap[numOfCases];	// Create proper amout of Heap instances

	for (long i = 0; i < numOfCases; ++i) {

		std::cin >> numsInCase;					// Number of values in case
		sortUS[i].setDataLength(numsInCase);		// Set proper data length

		for (long j = 0; j < numsInCase; ++j) {

			std::cin >> oneNum;
			sortUS[i].pushData(oneNum);			// Add one element from one data set do Heap

		}
		sortUS[i].sort();						// After all nums from case are added, sort them

		sortUS[i].displayFinal();				// Display finally sorted values
		std::cout << std::endl;
	}
}


