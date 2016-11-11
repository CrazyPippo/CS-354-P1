
/* Title:            (P1: list.c)
 * Description:	    (File I/0 & Linked-list)
 *
 * Author:           (Chenyuan Zhang)
 * Email:            (czhang356@wisc.edu)
 * CS Login:         (chenyuan)
 * Section:  	    (Lecture 1  -> 9:55 am - 10:45am)
*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#define MAX_INTS 1000
#define FILE_NAME_SIZE 100

/* A node in the linked list */
struct node {
    int data;
    struct node *next;
};



int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;
    struct node* head = NULL;
    struct node* sorted_head = NULL;
    int myArray [MAX_INTS];
    int sorted_array [MAX_INTS];
    int size;
    int sorted_size;
    
    /* TODO: Complete the main method according to the steps outlined */
    if (argc != 2) {
        printf("Usage: ./list <input_file>\n");
        exit(1);
    }
    /* Open a file for reading */
    input = openFileForRead(input,argv[1]);
    /* Read the numbers from the file, into an array */
    size =  readFile(input, myArray);
    /* Print the array */
    print_array(myArray, size);
    /* Create a linked list with the integers from the array */
    head = create_list(myArray, size);
    /* Print the linked list */
    print_list(head);
    /* Repeatedly prompt the user for a number to be searched.
     *  Search the array for the number and print out the result as shown in the specs.
     *  Search the linked list for the number and print out the result as shown in the specs.
     *  Stop prompting when the user enters 'q' (just the character q without the single quotes).
     */
    search_element(head, myArray, size);
    
    /* Create a sorted list(in ascending order) from the unsorted list */
    sorted_head = create_sorted_list(head);
    /* Print the sorted list */
    print_list(sorted_head);
    /* Copy the sorted list to an array with the same sorted order */
    sorted_size = copy_list_to_array(sorted_head, sorted_array);
    /* Print out the sorted array */
    print_array(sorted_array, sorted_size);
    /* Print the original linked list again */
    print_list(head);
    /* Print the original array again */
    print_array(myArray, size);
    /* Open a file for writing */
    output = openFileForWrite(output);
    /* Write the sorted array to a file named "sorted_numbers.txt" */
    int number_of_integers_wriiten = write_to_file(output, sorted_array, sorted_size);
    /* Print out the number of integers written to the file */
    printf("Number of integers from a sorted array to a file = %d\n", number_of_integers_wriiten);
}

/**
 create a linked list from a known array
 
 @param: (intarray): known array
 @param: (len): the size of the known array
 @return: a pointer to the head of the linked list
 
*/
struct node* create_list(int intarray[], int len)
{
    // initialize head pointer
    struct node* head = NULL;
    
    
    // assgin values to each node and connect them together
    int i;
    for(i = 0; i < len; i++)
        head = add_item_at_start(head, intarray[i]);
    
    
    return head;
}

/**
 Add the new node at the start of the linked list
 
 @param: (head): pointer to the head node
 @param: (data): the integer value that is stoted in the node
 @return: pointer to the head node
 
 */
struct node* add_item_at_start(struct node *head, int data)
{
    
    // case 1: empty list
    if(head == NULL){
        head = (struct node*)malloc(sizeof(struct node));
        head -> data = data;
        head -> next = NULL;
        return head;
    }
    
    // case 2: general case
    struct node* newNode = NULL;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> data = data;
    newNode -> next = head;
    head = newNode;
   
    
    return head;
}

/**
 search the integer value in the linked list
 
 @param: (head): pointer to the head node
 @param: (element): the integer value to be searched
 @return: the index of the searced int value
 
 */
int search_list(struct node *head, int element)
{
    int index = 0;
    
    if(head == NULL){
        printf("The list is empty\n");
        exit(1);
    }
    // search the element
    do{
         // if found, return the index
        if(element == head -> data){
            printf("Element %d found in the linked list at position %d \n", element, index);
            return index;
        }
        index ++;
        head = head -> next;
    }while(head != NULL);
    
    printf("Element %d not found in the linked list\n", element);
    return -1;
}

/**
 search the integer value in the array
 
 @param: (integers): known array
 @param: (numints): the size of the known array
 @param: (element): the int value to be searched
 @return: the index of the searched element
 
 */

int search_array(int integers[], int numints, int element)
{
    int index;
    
    if(numints == 0){
        printf("the array is empty");
        exit(1);
    }
    
    for(index = 0; index < numints; index++){
        if(integers[index] == element){
            printf("Element %d found in the array at index %d\n", element, index);
            return  index;
        }
    }
    
    printf("Element %d not found in array\n", element);
    return -1;
}

/**
 copy all int values from the linked list to an array
 
 @param: (head): pointer to the head node
 @param: (array): pointer to the first element of the array
 @return: the size of the array
 
 */

int copy_list_to_array(struct node *head, int *array)
{
    int size = 0;
    while (head != NULL) {
        *array = head -> data;
        size++;
        array++;
        head = head -> next;
    }
    return size;
}

/**
 create a sorted linked list from a unsorted linked list
 
 @param: (head): the pointer to the head node of the undorted list
 @return: a pointer to the head of the sorted list
 
 */

struct node* create_sorted_list(struct node *head)
{
    struct node* sorted_head = NULL;
    
    while (head != NULL) {
        sorted_head = add_item_sorted(sorted_head, head -> data);
        head = head -> next;
    }
    
    return sorted_head;
}

/**
 add int value to the sorted list
 
 @param: (sorted_head): pointer to the head node of the sorted list
 @param: (data): the int value to be added
 @return: pointer to the head node of the sorted list
 */

struct node* add_item_sorted(struct node *sorted_head, int data)
{
    // case 1: head is empty
    if(sorted_head == NULL) {
        sorted_head = (struct node*)malloc(sizeof(struct node));
        sorted_head -> data = data;
        sorted_head -> next = NULL;
        return sorted_head;
    }
    
    // initialize new node and tracking variables
    struct node* newNode =(struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("something goes wrong when allocating memory for new node\n");
    }
    newNode -> data = data;
    struct node* runner = sorted_head;
    struct node* previous_node = NULL;
    
    // general case
    while (runner != NULL) {
        // swap at the appropriate position
        if(data < runner -> data){
            // swap with head if new node is smaller than head
            if(runner == sorted_head){
                newNode -> next = runner;
                runner = newNode;
                return runner;
            }
            // general swap (in the middle)
            previous_node -> next = newNode;
            newNode -> next = runner;
            return sorted_head;
        }
        // update tracking variables
        previous_node = runner;
        runner = runner -> next;
    }
    // tail case
    previous_node -> next = newNode;
    newNode -> next = NULL;
    return sorted_head;
    
    
}

/**
 display all int value in the list
 @param (head): pointer to the head node of the list
 
 */

void print_list(struct node *head)
{
    if (head == NULL) {
        printf("Linked List is Empty.\n");
    } else {
        struct node *temp = head;
        printf("head->");
        while (temp != NULL) {
            printf("|%d|->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/**
 display all int value in the array
 
 @param (integers): pointer to the head node of the list
 @param (len): the size of the array
 
 */

void print_array(int integers[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("| %d ", integers[i]);
    }
    printf("|\n");
}

/**
 open the file and get ready to scan
 
 @param(input): file to be scanned
 @param (file_name_ptr): pointer to the file name
 
 @return: the open file
 */


FILE* openFileForRead(FILE* input, char* file_name_ptr){
    
    // create the file name string based on file_name pointer
    char fileName[FILE_NAME_SIZE];
    int counter = 0;
    while (*file_name_ptr != '\0') {
        fileName[counter] = *file_name_ptr;
        counter++;
        file_name_ptr++;
    }
    fileName[counter] = '\0';
    
    // open the file
    input = fopen(fileName, "r");
    if(input == NULL){
        printf("ERROR: Cannot open file for reading!\n");
        exit(1);
    }
   printf("open file succeed!\n");
    return input;
}

/**
 open the file and get ready to write
 
 @param(output): file to be written

 @return: the written file
 */

FILE* openFileForWrite(FILE* output){
    char fileName [FILE_NAME_SIZE] = "sorted_numbers.txt";
    output = fopen(fileName, "w");
    if(output == NULL){
        printf("Cannot open %s", fileName);
        exit(1);
    }
    return output;
}

/**
 read the int values of the file and store them in the array
 
 @param (input): file to be scanner
 @param (myArray): array to store all int values
 
 @return: the size of the array
 
 */

int readFile(FILE* input, int myArray[]) {
    printf("Reading integrs from a file to an array\n");
    int counter = 0;
    
    if(input == NULL){
        printf("file pointer is null\n");
        exit(1);
    }
    // loop the numbers in the file
    do{
        fscanf(input, "%d", &myArray[counter]);
       
        // once reached the last line, scanning completed
        if(feof(input))
            break;
        
        counter++;
    }while(1);
    
    printf("Total %d numbers scanned\n", counter);
    fclose(input);
    return counter;
}

/**
 read an int to be searched from the user and search it in the list and array
 
 @param(head): pointer to the head node of the linked list
 @param (myArray): array in which int is searched
 @param (size): the size of the array
 
 */

void search_element (struct node* head, int myArray[], int size){
    while(1){
        int array_index;
        int list_index;
        int element;
        // promot
        printf("Enter an element to be searched in the list and array: ");
        
        // read input and break the loop if user enters "q"
        if(scanf("%d", &element) == 0){
            fseek(stdin,0,SEEK_END); // clean input buffer
            break;
        }
        
        // search
        array_index = search_array(myArray, size, element);
        list_index = search_list(head, element);
        
    }
}

/**
 write all int values to a file
 
 @param (output): file to be written
 @param (myArray): array that has all int values to be written
 @param (size): the size of the array
 
 @return: the number of int written to the file
 
 */

int write_to_file(FILE* output, int myArray[], int size){
    printf("Writing integers from a sorted array to a file...\n");
    int counter;
    for(counter = 0; counter < size; counter++)
        fprintf(output, "%d\n", myArray[counter]);
    
    fclose(output);
    return counter;
}
