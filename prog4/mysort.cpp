// Author: Giahuy Thai
// CECS 325-02 Prog 4
// Due 11/04/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>

using namespace std;

// Struct to keep track of segments
struct Segment {
    int* start;  // Pointer to the start of the segment
    int size;    // Number of numbers in the segment
};

long long totalSwaps = 0;
int* threadIDs = nullptr;
long long* threadSwapCounts = nullptr;
int threadCount = 0;
int maxThreads = 0;
mutex locker; // mutex to protect the totalSwaps variable



// Bubble sort function for a segment of the array
void bubble(int* arr, int size, int threadID) {
    long long localSwaps = 0;
    for (int pass = 0; pass < size - 1; pass++) {
        for (int i = 0; i < size - 1 - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                localSwaps++;
            }
        }
    }
    
    // Update global counters once at the end (only one mutex lock per thread)
    locker.lock();
    totalSwaps += localSwaps;
    if (threadCount < maxThreads) {
        threadIDs[threadCount] = threadID;
        threadSwapCounts[threadCount] = localSwaps;
        threadCount++;
    }
    locker.unlock();
}

// Merge all sorted segments using merge from <algorithm>
void mergeSegments(int* arr, Segment* segments, int numSegments, int arrSize) {
    int* temp = new int[arrSize];
    
    // Build segment boundaries from segments
    int* segmentBoundaries = new int[numSegments + 1];
    segmentBoundaries[0] = 0;
    for (int i = 0; i < numSegments; i++) {
        segmentBoundaries[i + 1] = segmentBoundaries[i] + segments[i].size;
    }
    
    // Iteratively merge segments
    for (int step = 1; step < numSegments; step *= 2) {
        for (int i = 0; i < numSegments - step; i += 2 * step) {
            int left = segmentBoundaries[i];
            int mid = segmentBoundaries[i + step];
            int right = segmentBoundaries[min(i + 2 * step, numSegments)];
            
            // Use std::merge from <algorithm>
            merge(arr + left, arr + mid,
                  arr + mid, arr + right,
                  temp + left);
            
            // Copy merged result back to original array
            for (int j = left; j < right; j++) {
                arr[j] = temp[j];
            }
        }
    }
    
    delete[] temp;
    delete[] segmentBoundaries;
}

int main(int argc, char* argv[]) {
    // Check if the arguments are correct
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <inputFile> <outputFile> <numSegments>" << endl;
        return 1;
    }

    // Open the input and output files
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);
    int numSegments = atoi(argv[3]);

    if (!inputFile.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }
    if (numSegments <= 0) {
        cout << "Number of segments must be positive" << endl;
        return 1;
    }

    // First pass: count the numbers in the input file
    int n = 0;
    int number;
    while (inputFile >> number) {
        n++;
    }
    inputFile.close();
    
    // Reopen the file to read the numbers
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        cout << "Error reopening input file" << endl;
        return 1;
    }
    
    // Allocate dynamic array for numbers
    int* numbers = new int[n];
    
    // Read the numbers from the input file
    for (int i = 0; i < n; i++) {
        inputFile >> numbers[i];
    }
    inputFile.close();

    // Calculate segment size
    int segmentSize = n / numSegments;
    int remainder = n % numSegments;

    // Allocate dynamic arrays for threads and segments
    thread* threads = new thread[numSegments];
    Segment* segments = new Segment[numSegments];
    
    // Allocate dynamic arrays for thread tracking
    maxThreads = numSegments;
    threadIDs = new int[numSegments];
    threadSwapCounts = new long long[numSegments];

    int currentPos = 0;

    // Create threads for each segment
    for (int i = 0; i < numSegments; i++) {
        // Distribute remainder among first segments
        int currentSegmentSize = segmentSize + (i < remainder ? 1 : 0);
        
        // Store segment information
        segments[i].start = &numbers[currentPos];
        segments[i].size = currentSegmentSize;
        
        // Create a new thread that will run bubble, starting at position currentPos in the array, 
        // and sorting currentSegmentSize elements. Then add this thread to our list of threads.
        threads[i] = thread(bubble, &numbers[currentPos], currentSegmentSize, i);
        
        // Update the current position to the start of the next segment
        currentPos += currentSegmentSize;
    }

    // Wait for all threads to complete
    for (int i = 0; i < numSegments; i++) {
        threads[i].join();
    }
    
    // Deallocate threads array
    delete[] threads;

    // Merge all sorted segments
    mergeSegments(numbers, segments, numSegments, n);
    
    // Deallocate segments array
    delete[] segments;

    // Write the sorted numbers to the output file
    for (int i = 0; i < n; i++) {
        outputFile << numbers[i] << endl;
    }
    
    // Deallocate numbers array
    delete[] numbers;
    
    // Output swap counts for each thread to stdout
    for (int i = 0; i < threadCount; i++) {
        cout << "Process " << threadIDs[i] << " swap count:" << threadSwapCounts[i] << endl;
    }
    
    // Deallocate thread tracking arrays
    delete[] threadIDs;
    delete[] threadSwapCounts;
    
    // Output total swap count to stdout
    cout << "Total Swaps:" << totalSwaps << endl;
    
    outputFile.close();

    return 0;
}
