#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);															//배열 initialize
			break;
		case 'q': case 'Q':
			freeArray(array);															//배열 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array);														//선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array);														//삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array);															//버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array);															//쉘 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);											//퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);													//해싱
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);												//hashtable에서 key값 찾아서 인덱스 값 리턴 받아옴
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;								//0부터 12까지의 랜덤 숫자를 배열에 초기화

	return 0;
}

int freeArray(int *a)													//배열 메모리 해제
{
	if(a != NULL)	
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");									//배열이 NULL이면 출력할게 없다는 문구 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;															//minindex를 i로 초기화
		min = a[i];																//min을 a[i]로 초기화
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])														//min보다 a[j]가 작다면
			{
				min = a[j];														//min을 a[j]값으로 초기화
				minindex = j;													//아직까지 a[j]가 작은 값이므로 minindex을 인덱스 j로 초기화
			}
		}
		a[minindex] = a[i];														//제일 작은 값을 가진 칸에 a[i]값을 넣고
		a[i] = min;																//a[i]에 제일 작은 값 넣기(a[minindex]와 a[i] 값을 서로 교환)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];																	//t에 a[i]값 넣어줌
		j = i;																		//j를 i로 초기화
		while (a[j-1] > t && j > 0)													//a[j-1]이 t보다 작거나 j가 0보다 작을때까지 반복
		{
			a[j] = a[j-1];															//a[j-1]값이 t 값보다 크기 때문에 a[j]에 a[j-1]을 넣음
			j--;																	//j--
		}
		a[j] = t;																	//a[j]에 t값을 넣어줌
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)										
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])														//자기 오른쪽 값과 비교해서 오른쪽 값이 자기 값보다 작으면
			{
				t = a[j-1];															//swap 하듯이 값 서로 교환
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)							//h를 MAX_ARRAY_SIZE의 절반 값으로 설정 후 h를 계속 2로 나눈 몫이 되게함 그렇게 h가 0과 같거나 작을때까지 반복
	{
		for (i = 0; i < h; i++)											//i가 0부터 h값이 되기 전까지 반복	
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)					//j를 i+h값으로 설정후 MAX_ARRAY_SIZE보다 작을때까지 반복 j는 j+h를 해서 j에 넣어줌
			{
				v = a[j];												//v 값을 a[j]로 초기화
				k = j;													//k를 j로 초기화
				while (k > h-1 && a[k-h] > v)							//k가 h-1보다 작아지거나 a[k-h] 값이 v 보다 작아질때까지 반복
				{
					a[k] = a[k-h];										//a[k]를 a[k-h]로 초기화
					k -= h;												//k를 k-h값으로 초기화
				}	
				a[k] = v;												//a[k]값을 v값으로 초기화
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)																	//n이 1보다 크다면
	{
		v = a[n-1];																//v를 a[n-1]값으로 초기화
		i = -1;																	//i를 -1로 초기화
		j = n - 1;																//j를 n-1 값으로 초기화

		while(1)																//무한반복
		{
			while(a[++i] < v);													//i값을 1씩 올려주면서 v 값보다 커지는 순간까지 i값 증가
			while(a[--j] > v);													//j값을 1씩 줄여주면서 v 값보다 작아지는 순간까지 j값 감소

			if (i >= j) break;													//i가 j보다 크거나 같을 경우 while문 탈출
			t = a[i];															//아니라면 a[i]값과 a[j]값을 swap 해줌
			a[i] = a[j];														
			a[j] = t;
		}
		t = a[i];																//a[i]의 값과 a[n-1]의 값을 swap
		a[i] = a[n-1];															
		a[n-1] = t;																

		quickSort(a, i);														//a와 i를 가지고 다시 함수 자신을 호출 (재귀)
		quickSort(a+i+1, n-i-1);												//a+i+1과 n-i-1을 가지고 재귀함수 호출
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;											//key값을 MAX_HASH_TABLE_SIZE로 나눈 나머지가 되게 함
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;														//*hashtable을 NULL 값으로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  // 할당된 메모리의 주소를 복사 main에서도 배열을 쓸 수 있게 함
	} else {
		hashtable = *ht;	// hash table이 NULL이 아닌경우 table 재활용 reset to -1
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;														//hashtable의 모든 값을 -1로 초기화	

	int key = -1;																
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];																//key값을 a[i]값으로 초기화
		hashcode = hashCode(key);												//hashcode를 hashCode(key)값으로 초기화

		if (hashtable[hashcode] == -1)											//hashtable의 hashcode번째 값이 -1일 경우
		{
			hashtable[hashcode] = key;											//hashtable의 hashcode번째 값을 key값으로 초기화
		} else 	{

			index = hashcode;													//아니면 index를 hashcode값으로 초기화

			while(hashtable[index] != -1)										//hashtable의 index번째 값이 -1이 될때까지 반복(hashtable의 빈 곳을 찾을때까지)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;						//index값을 1씩 증가시킴
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;												//빈 곳을 찾아서 나오면 그 빈곳에 key값을 초기화해줌
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);													//index를 hashCode(key)값으로 초기화

	if(ht[index] == key)														//해시테이블의 index번째 값이 key값과 같으면
		return index;															//index값 리턴

	while(ht[++index] != key)													//아니면 key값과 같은 해시테이블이 나올때까지 index 증가
	{
		index = index % MAX_HASH_TABLE_SIZE;									//index가 MAX를 넘지않도록 조정
	}
	return index;																//index값 리턴
}



