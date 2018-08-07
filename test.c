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
  q->buf= (char *)malloc(sizeof(char *) * b_size);
  q->head=q->buf;
  q->tail=q->buf;

  return 0;

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
  q->head = q->buf + (int)((q->head - q->buf)+sizeof(in_data)) % q->size;
  return 0;

}


int get(ring_t *q, char *out_data)
{
  if(!q){
    return Failure;
  }

  *out_data = *(q->tail);

  q->tail = q->buf + ((q->tail - q->buf) + sizeof(*out_data)) % q->size;
  return 0;

}


int main(void)
{
  ring_t queue;
  const int buf_size = 3;

  char indata = 0x22;
  char outdata;


  buf_init(&queue, buf_size);

  put(&queue, indata);
  indata = 0x23;
  put(&queue, indata);
  indata = 0x24;
  put(&queue, indata);
  indata = 0x25;
  put(&queue, indata);
  get(&queue, &outdata);
  printf("%x\n", outdata);
  get(&queue, &outdata);
  printf("%x\n", outdata);
  get(&queue, &outdata);
  printf("%x\n", outdata);
  get(&queue, &outdata);
  printf("%x\n", outdata);
  return 0;
}
