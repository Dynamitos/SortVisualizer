#pragma once

extern "C"
{
    void asmbubblesort(float* data, int length, int delay);
    void asmmerge(float* sortedData, float* readData, int leftStart, int rightStart, int leftEnd, int rightEnd);
    int asmpartition(float* arr, int left, int right);
    void asmswap(void* value1, void* value2);
}