#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FACTORS 64 //Maximum value of uint64_t is 2^64

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t l = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t n = PTHREAD_MUTEX_INITIALIZER;

typedef struct node
{
    uint64_t number;   //number itself
    int k;  //number of factors
    struct node *next;  //link to next number
    uint64_t factors[MAX_FACTORS]; //array of factors
} node_t;

struct arg_struct
{
    FILE *arg1;
    node_t *arg2;
};

void push(node_t *new_node, node_t **root, uint64_t number, int k, uint64_t factors[])
{
    new_node->number = number;
    new_node->k = k;
    int i;
    for (i=0; i<k; i++)
    {
        new_node->factors[i]=factors[i];
    }
    new_node->next = *root;
    *root = new_node;
}

node_t *check_in_list(uint64_t num, node_t *root)
{
    node_t *current = root;
    while (current!=NULL)
    {
        if (current->number==num)
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

int get_prime_factors(uint64_t num, uint64_t *dest)
{
    int count=0;

    if (num==1)
    {
        dest[count]=1;
        count++;
    }

    while (num%2==0)
    {
        dest[count]=2;
        count++;
        num=num/2;
    }

    uint64_t sqroot = 1;

    //Find the square root
    while (sqroot*sqroot<=num)
    {
        sqroot+=1;
    }

    uint64_t i=3;
    for (; i<=sqroot; i=i+2)
    {
        while (num%i==0)
        {
            dest[count]=i;
            count++;
            num/=i;
        }
    }
 
    if (num>2)
    {
        dest[count]=num;
        count++;
    }
    return count;
}

void print_prime_factors(uint64_t num, uint64_t *dest, int k)
{
    int j;
    printf("%ju: ",  num);
    
    for (j=0; j<k; j++)
    {
        printf("%ju ", dest[j]);
    }
    printf("\n");
}

void *read_from_file(void *arguments)
{
    //Parsing from void to appropriate types
    struct arg_struct *args = arguments;
    FILE *nums = (FILE*) args -> arg1;
    node_t *root = (node_t*) args -> arg2;
    node_t **rootadd = &root;
    
    int k;
    uint64_t num;
    char str[100];
    pthread_mutex_lock(&m);
    while (fgets (str, sizeof(str), nums)!=NULL)
    {
        pthread_mutex_unlock(&m);
        num = atoll(str);
        node_t *checker = check_in_list(num, root);
        
        //Found in list
        if (checker!=NULL)
        {
            pthread_mutex_lock(&l);
            print_prime_factors(num, checker->factors, checker->k);
            pthread_mutex_unlock(&l);
        }

        //Not in list
        else
        {
            uint64_t factors[MAX_FACTORS];
            node_t *new_node;
            new_node = malloc(sizeof(node_t));
            k = get_prime_factors(num, factors);
            
            pthread_mutex_lock(&n);
            push(new_node, rootadd, num, k, factors);
            pthread_mutex_unlock(&n);

            pthread_mutex_lock(&l);
            print_prime_factors(num, new_node->factors, k);
            pthread_mutex_unlock(&l);
        }
        pthread_mutex_lock(&m);
    }
    pthread_mutex_unlock(&m);
    return 0;
}

int main(void)
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.
    FILE *numbers;
    void *status;
    node_t *root;
    root = malloc(sizeof(node_t));
    root->factors[MAX_FACTORS] = (uint64_t)malloc(sizeof(uint64_t)*MAX_FACTORS);
    numbers = fopen ("small.txt", "r");
    struct arg_struct args;
    args.arg1 = numbers;
    args.arg2 = root;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, read_from_file, (void*) &args);
    pthread_create(&thread2, NULL, read_from_file, (void*) &args);
    pthread_join(thread1, &status);
    pthread_join(thread2, &status);

    return 0;
}