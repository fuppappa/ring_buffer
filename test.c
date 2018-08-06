#include<stdio.h>
#include<stdlib.h>


typedef struct ring_buf{
  char *buf;
  char *head;
  char *tail;
  int   size;
} ring_t;


void buf_init(ring_t *q , int b_size)
{
  q->size = b_size;
  q->buf= (char *)malloc(sizeof(char *)*b_size);
  q->head=q->buf;
  q->tail=q->buf;

}



int buf_state(ring_t *q)
{
  if(q->head == q->tail){
    return -1;
  }else if(q->tail+1 == q->head){
    return -2;
  }
  return 0;
}


int put(ring_t *q, char in_data)
{
  if(!q){
    return -1;
  }

  q->head = (q->tail)+1
  *(q->head) = in_data;
  /*head refresh
   *
   */
  q->head = (q->head+sizeof(in_data)) % q->size;
  return 0;

}


int get(ring_t *q, char out_data)
{
  if(!q){
    return -1;
  }

  out_data = *(q->head);


 //memcpy使う？？
  q->head = q->head+(sizeof(out_data));

  return 0;

}
