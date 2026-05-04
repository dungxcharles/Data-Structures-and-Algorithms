#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 100005
#define MAX_LEN_OF_INPUT 15
#define MAX_LEN_OF_CMD 30
#define MOD 10007

typedef struct Data{
    char* customerID;
    char* productID;
    int price;
    char* shopID;
    char* timePoint;

    int timeInSec;
}Data;

Data inforList[MAX];
int totalOrder = 0;
long long unsigned int totalRevenue = 0;


int toSec(const char* timePoint){
    return ((timePoint[0]-'0')*10+(timePoint[1]-'0')) * 3600 + ((timePoint[3]-'0')*10+(timePoint[4]-'0')) * 60
                + ((timePoint[6]-'0')*10+(timePoint[7]-'0'));
}

Data makeInfor(const char* customerID, const char* productID, int price, const char* shopID, const char* timePoint){
    // init
    Data newInf;
    newInf.customerID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    newInf.productID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    newInf.shopID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    newInf.timePoint = malloc(MAX_LEN_OF_INPUT * sizeof(char));

    // assign fields
    strcpy(newInf.customerID, customerID);
    strcpy(newInf.productID, productID);
    newInf.price = price;
    strcpy(newInf.shopID, shopID);
    strcpy(newInf.timePoint, timePoint);

    newInf.timeInSec = toSec(timePoint);
    return newInf;
}

// ------------------- hashset and hashmap -------------------------//

typedef struct Node{
    char* customerID;
    char* shopID;
    int totalShopRevenue;
    int totalConsumeRevenue;
    struct Node* next;
}Node;

// I make 2 constructor here to avoid allocating redundant space also for not messing up
Node* makeNodeInSet(Data infor){
    Node* p = malloc(sizeof(Node));

    p->shopID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    strcpy(p->shopID, infor.shopID); 

    p->totalShopRevenue = infor.price;
    p->next = NULL;
    return p;
}

Node* makeNodeInMap(Data infor){
    Node* p = malloc(sizeof(Node));

    p->shopID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    strcpy(p->shopID, infor.shopID); 

    p->customerID = malloc(MAX_LEN_OF_INPUT * sizeof(char));
    strcpy(p->customerID, infor.customerID);

    p->totalConsumeRevenue = infor.price;
    p->next = NULL;
    return p;
}

Node* hashset[MOD];
Node* hashmap[MOD];
void init(){
    for (int i = 0; i < MOD; i++){
        hashset[i] = NULL;
        hashmap[i] = NULL;
    }
}

int hash(const char* s){        // a way to hash a string efficiently
    unsigned long hash = 5381;
    int c;
    while ((c = *s++)){
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % MOD;
}

// hash set
void putToSet(Data infor){          // put a node to set
    int idx = hash(infor.shopID);
    Node* p = hashset[idx];
    while (p!=NULL){
        if (!strcmp(p->shopID, infor.shopID)){
            p->totalShopRevenue += infor.price;
            return;
        }
        p=p->next;
    }

    p = makeNodeInSet(infor);
    p->next = hashset[idx];
    hashset[idx] = p;
}

int getRevenueOfShop(const char* shopID){           // find node in hashset
    int idx = hash(shopID);
    Node* p = hashset[idx];
    while (p){
        if (!strcmp(p->shopID, shopID)){
            return p->totalShopRevenue;
        }
        p=p->next;
    }
    return 0;
}

// hash map
void putToMap(Data infor){      // put a node to map
    int idx = hash(infor.shopID);

    Node* p = hashmap[idx];
    while (p!=NULL){
        if (!strcmp(p->shopID, infor.shopID) && !strcmp(p->customerID, infor.customerID)){
            p->totalConsumeRevenue += infor.price;
            return;
        }
        p=p->next;
    }

    p = makeNodeInMap(infor);
    p->next = hashmap[idx];
    hashmap[idx] = p;
}

int getTotalConsumeOfShop(const char* customerID, const char* shopID){      // find node in hashmap
    int idx = hash(shopID);
    Node* p = hashmap[idx];
    while (p){
        if (!strcmp(p->shopID, shopID) && !strcmp(p->customerID, customerID)){
            return p->totalConsumeRevenue;
        }
        p=p->next;
    }
    return 0;
}

// --------------------------- HEAP SORT ------------------------------------//
// Sorting input by heap sort to minimize the space used and for prefix Sum

bool cmp(Data a, Data b){
    return a.timeInSec < b.timeInSec;
}

void swap(Data* a, Data* b){
    Data tmp = *a; *a = *b; *b = tmp;
}

void heapify(int i, int n){
    int left = 2*i+1, right = 2*i+2, maxIdx = i;
    if (left < n && cmp(inforList[maxIdx], inforList[left])){
        maxIdx = left;
    }
    if (right < n && cmp(inforList[maxIdx], inforList[right])){
        maxIdx = right;
    }
    if (maxIdx!=i){
        swap(&inforList[i], &inforList[maxIdx]);
        heapify(maxIdx, n);
    }
}
void heapSort(int n){
    for (int i = n/2-1; i >= 0; i--){
        heapify(i, n);
    }
    for (int i = n-1; i >= 0; i--){
        swap(&inforList[i], &inforList[0]);
        heapify(0, i);
    }
}

int prefixSum[MAX] = {0};

void input(){
    init();
    char inf1[MAX_LEN_OF_INPUT], inf2[MAX_LEN_OF_INPUT], inf3[MAX_LEN_OF_INPUT], inf4[MAX_LEN_OF_INPUT];
    int price;
    while (1){
        scanf("%s",inf1);
        if (inf1[0] == '#') break;

        scanf("%s %d %s %s", inf2, &price, inf3, inf4);
        inforList[totalOrder++] = makeInfor(inf1, inf2, price, inf3, inf4);
        totalRevenue += price;
        putToSet(inforList[totalOrder-1]);
        putToMap(inforList[totalOrder-1]);
    }
    heapSort(totalOrder);
    prefixSum[0] = inforList[0].price;
    for (int i = 1; i < totalOrder; i++){
        prefixSum[i] = prefixSum[i-1] + inforList[i].price;
    }
}

int getSum(int left, int right){        // Prefix sum
    return prefixSum[right] - prefixSum[left] + inforList[left].price;
}

int revenueOfShop(const char* shopID){  // Apply hashset
    return getRevenueOfShop(shopID);
}

// Find the first index where timeInSec >= target
// Return -1 if all value < target 
int findLeft(int target) {
    int left = 0, right = totalOrder - 1, result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (inforList[mid].timeInSec >= target) {
            result = mid;
            right = mid - 1;  // Find the left
        } else {
            left = mid + 1;
        }
    }
    return result;
}

// Find last index where timeInSec <= target
// Return -1 if all value > target
int findRight(int target) {
    int left = 0, right = totalOrder - 1, result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (inforList[mid].timeInSec <= target) {
            result = mid;
            left = mid + 1;  // Find the right
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int totalRevenueInPeriod(const char* start, const char* end){ // Apply prefixSum
    int tStart = toSec(start);
    int tEnd = toSec(end);

    int left = findLeft(tStart);
    int right = findRight(tEnd);

    if (left == -1 || right == -1 || left>right)  return 0;
    return getSum(left, right);
}

int totalConsume(const char* customerID, const char* shopID){   // Apply hashmap
    return getTotalConsumeOfShop(customerID, shopID);
}

void test(){
    printf("%d\n",totalOrder);
    for (int i = 0; i < totalOrder; i++){
        printf("%s %s %d %s %s %d\n",inforList[i].customerID, inforList[i].productID, 
                inforList[i].price, inforList[i].shopID, inforList[i].timePoint, inforList[i].timeInSec);
    }
}

void solution(){
    char cmd[MAX_LEN_OF_CMD];
    while (1){
        scanf("%s",cmd);
        if (cmd[0] == '#')  break;

        if (!strcmp(cmd, "?total_number_orders")){
            printf("%d\n",totalOrder);
        }
        else if (!strcmp(cmd, "?total_revenue")){
            printf("%llu\n",totalRevenue);
        }
        else if (!strcmp(cmd, "?revenue_of_shop")){
            char shopID[MAX_LEN_OF_INPUT];
            scanf("%s",shopID);
            printf("%d\n", revenueOfShop(shopID));
        }
        else if (!strcmp(cmd, "?total_consume_of_customer_shop")){
            char customerID[MAX_LEN_OF_INPUT], shopID[MAX_LEN_OF_INPUT];
            scanf("%s %s",customerID, shopID);
            printf("%d\n",totalConsume(customerID, shopID));
        }
        else if (!strcmp(cmd, "?total_revenue_in_period")){
            char startT[MAX_LEN_OF_INPUT], endT[MAX_LEN_OF_INPUT];
            scanf("%s %s",startT, endT);
            printf("%d\n",totalRevenueInPeriod(startT, endT));
        }
    }
}

int main(){
    input();
    //test();
    solution();
    return 0;
}