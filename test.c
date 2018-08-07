#include<stdio.h>
#include<stdlib.h>


#define Failure -1
#define True 0

typedef struct ring_buf{
  char *buf;
  char *head;
  char *tail;
  int   size;
} ring_t;


int buf_init(ring_t *q , int b_size)
{
  q->size = b_size;
  q->buf= (char *)malloc(sizeof(char *)*b_size);
  q->head=q->buf;
  q->tail=q->buf;

}



int buf_state(ring_t *q)
{
  if(q->head == q->tail){
    return Failure;
  }else if(q->tail+1 == q->head){
    return Failure;
  }
  return 0;
}


int put(ring_t *q, char in_data)
{
  if(!q){
    return Failure;
  }
  *(q->head) = in_data;
  /*head refresh
   *
   */
  q->head = (q->head+sizeof(in_data)) % q->size;
  q->head = q->head+1;
  return 0;

}


int get(ring_t *q, char out_data)
{
  if(!q){
    return Failure;
  }

  out_data = *(q->tail);
 //memcpy使う？？
  q->tail = (q->tail+sizeof(out_data)) % q->size;
  q->tail = q->tail+1;
  return 0;

}
