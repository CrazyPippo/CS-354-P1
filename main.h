//
//  main.h
//  p1
//
//  Created by Pippo on 2/15/16.
//  Copyright © 2016 Pippo. All rights reserved.
//

#ifndef main_h
#define main_h

struct node* create_list(int intarray[], int len);

struct node* add_item_at_start(struct node *head, int data);

int search_array(int integers[], int numints, int element);

int search_list(struct node *head, int element);

struct node* create_sorted_list(struct node *head);

struct node* add_item_sorted(struct node *head, int data);

int copy_list_to_array(struct node *head, int *array);

void print_list(struct node *head);

void print_array(int integers[], int len);

FILE* openFileForRead(FILE *input, char* fillName);

FILE* openFileForWrite(FILE* output);

int readFile(FILE *output, int myArray[]);

void search_element(struct node* head, int myArray[], int size);

int write_to_file(FILE* output, int myArray[], int size);
#endif /* main_h */
