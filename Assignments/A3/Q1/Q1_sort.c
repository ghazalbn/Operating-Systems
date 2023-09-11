// Q1 Bakhshande
// just type make in shell and see the resault
// 10 numbers produced randomly
// you can see the sorted array at the end

#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/shm.h>

#define IN_LEN 10
#define FINISH -999
#define PROC_NO 4
#define SIZE 1024
#define NAME "my_shr_mem"
#define SEM_NAME "my_sem1"
#define LENGTH 10


void merge(int arr[], int startIndex, int mid, int endIndex)
{
	int fIndex, sIndex, idx;

	int leftArr[mid - startIndex + 1], rightArr[endIndex - mid];

	int leftLen = mid - startIndex + 1;
	int rightLen = endIndex - mid;

	for (fIndex = 0; fIndex < leftLen; fIndex++)
	{
		leftArr[fIndex] = arr[startIndex + fIndex];
	}
	for (sIndex = 0; sIndex < rightLen; sIndex++)
	{
		rightArr[sIndex] = arr[mid + 1 + sIndex];
	}

	fIndex = 0;
	sIndex = 0;
	idx = startIndex;
	while (fIndex < leftLen && sIndex < rightLen)
	{
		if (leftArr[fIndex] <= rightArr[sIndex])
		{
			arr[idx] = leftArr[fIndex];
			fIndex++;
		}
		else
		{
			arr[idx] = rightArr[sIndex];
			sIndex++;
		}
		idx++;
	}

	while (fIndex < leftLen)
	{
		arr[idx] = leftArr[fIndex];
		fIndex++;
		idx++;
	}
	while (sIndex < rightLen)
	{
		arr[idx] = rightArr[sIndex];
		sIndex++;
		idx++;
	}
}

void MergeSort(int arr[], int startIndex, int endIndex)
{
	int state;
	pid_t leftChild = 0;
	pid_t rightChild = 0;

	int mid = (startIndex + startIndex) / 2;
	if (endIndex - startIndex <= 0)
	{
		return;
	}
	else
	{
		leftChild = fork();
		if (leftChild == 0)
		{
			MergeSort(arr, startIndex, mid);
			exit(0);
		}
		else if (leftChild < 0)
		{
			perror("bache naghes shod\n");
			exit(1);
		}
		else if (leftChild > 0)
		{
			rightChild = fork();
			if (rightChild == 0)
			{
				MergeSort(arr, mid + 1, endIndex);
				exit(0);
			}
			else if (rightChild < 0)
			{
				perror("bache naghes shod\n");
				exit(1);
			}
		}
		pid_t tempPIDLeft = waitpid(leftChild, &state, WUNTRACED);
		pid_t tempPIDRight = waitpid(rightChild, &state, WUNTRACED);
	}
	merge(arr, startIndex, mid, endIndex);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int shm_fd;
	int *arr;
	shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
	if (shm_fd < 0)
	{
		perror("Failed to open shared memory");
		return 1;
	}
	ftruncate(shm_fd, SIZE);
	arr = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	for (int i = 0; i < LENGTH; i++)
	{
		arr[i] = rand() % 101;
	}
	for (int i = 0; i < LENGTH; i++)
		printf("%d ", arr[i]);

	printf("\n");

	MergeSort(arr, 0, LENGTH - 1);

	for (int i = 0; i < LENGTH; i++)
		printf("%d ", arr[i]);

	printf("\n");

	munmap(arr, SIZE);
	close(shm_fd);
	return 0;
}