#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

char memory[25000];

typedef struct node{
	bool index;
	int size;
}node;

int isMemoryNew = 1;


node* FindLocation(int n){

node* ptr=memory;
	while( !(ptr->index==0 && ptr->size>=n) ){
		
	  if( ptr<&memory[24999] && (ptr->index!=0 && ptr->index!=1) ){
	    printf("\nSomething Went Wrong !! ( UnAuthorised use of memory ) \n");
		exit(404);  }
		
	  if(ptr>&memory[24999]){
	    return NULL; }
	    
	  else{
		ptr=(void*)ptr + sizeof(node) + ptr->size; }
	}
	return ptr;

}

void Partition(node* ptr,int n){
	
	  node* restPart =(void*)ptr + sizeof(node) + n;
	  
	  restPart->index=0;
	  restPart->size=(ptr->size-n)-sizeof(node);
	  ptr->size=n;
	  
}

void* MyMalloc(int n){
	if(n<=0){
	  printf("\nInvalid Memory Requestion !! \n");	
	  return NULL; }
	  
	else if(n>24992){
	  printf("\nMemory Limit Exceeded !! \n");
	  return NULL; }
	  
	else{
		
	  if( isMemoryNew ) {
	    node* start = memory;
          start->index=0;
          start->size=24992;
		isMemoryNew=0; }
	
  	  node* newLocation=FindLocation(n);
  	  
  	  if(newLocation){
  	    newLocation->index=1;
  	    if( newLocation->size - n >= sizeof(node) )
  	      Partition(newLocation,n);
	    return( newLocation+1 ); }  // newLocation+1 , means location of after sizeof(node) bytes from newLocation
	    
	  else{
	    printf("\nNo Memory Availale !! \n");
	    return NULL; }
	  
	}
	
}

void MyFree(void* freePtr){
  	
if(freePtr==NULL){
    return; }
    
else{
	
  node* ptr= freePtr - sizeof(node);
  
  ptr->index=0;
  
  ptr = memory;
  
  while( (void*)ptr + sizeof(node) + ptr->size < &memory[24999] ){
  	  node* ptrNext =(void*)ptr + sizeof(node) + ptr->size;
  	  
	  if(  ptr->index==0 && ptrNext->index==0 ){
	    ptr->size += ptrNext->size + sizeof(node) ;
	    
	    if( (void*)ptr + sizeof(node) + ptr->size < &memory[24999] ){
	    
	      ptrNext = (void*)ptr + sizeof(node) + ptr->size;
	    	
	  	  if(  ptr->index==0 && ptrNext->index==0 ){
	        ptr->size += ptrNext->size + sizeof(node) ; }          }
	  	  
	  	return;  
	  	  
		  }
	  ptr=ptrNext;  }
	  
    }
}

