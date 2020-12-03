#pragma once

extern "C"
{
    inline void asmbubblesort(float* data, int length, int delay);
    inline void asmrecursivesort(float* sortedData, float* readData, int start, int end);
    inline void asmmerge(float* sortedData, float* readData, int leftStart, int rightStart, int leftEnd, int rightEnd);
    inline int asmpartition(float* arr, int left, int right);
    inline void asmswap(void* value1, void* value2);
    inline void asminsertionsort(float* data, int length, int intDelay);
    inline void asmtests();
}