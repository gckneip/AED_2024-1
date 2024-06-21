#include <stdio.h>
#include<stdlib.h>

int *twoSum( int* nums, int numsSize, int target, int* returnSize );

int main(void){
    int nums[10] = {0,1,2,3,4,5,6,7,8,9};
    int i = 0;
    int *returnSize = (int*)calloc(1,sizeof(int));
    int *result = twoSum(nums,10,5,returnSize);

    while(i > *returnSize){
        printf("%d",result[i]);
        i++;
    }
    free(returnSize);
    free(result);
    return 0;
}

int *twoSum( int* nums, int numsSize, int target, int* returnSize ) {
    int i = 0, j = 0, *array =  '\0';
    *returnSize = 2;
    array = ( int* )malloc( sizeof( int )*2 );
    while( i < numsSize ){
        j = i ;
        while( j < numsSize ){
            if( ( nums[i] + nums[j] ) == target && i != j ){
                array[0] = i;
                array[1] = j;
                return array;
            }
            j++;
        }
        i++;
    }
    return array;
}