#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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


int put(ring_t *q, void *in_data, int size)
{
  int i = 0;
  if(!q){
    return Failure;
  }

  if((int)((q->head - q->buf)+size) > q->size){
    for(i=0; i<size; i++){
      *(q->head) = *((char *)in_data+i);
      q->head = q->buf + (int)((q->head - q->buf)+sizeof(char)) % q->size;
    }
  }else{
    memcpy(q->head, in_data, size);
  }
  printf("%dbyte\n", size);
  //*(q->head) = in_data;
  /*head refresh
  */
  q->head = q->buf + (int)((q->head - q->buf)+size) % q->size;

  return 0;
}


int get(ring_t *q, char *out_data)
{
  if(!q){
    return Failure;
  }

  memcpy(out_data, q->tail, sizeof(*out_data));
  //  *out_data = *(q->tail);
  q->tail = q->buf + ((q->tail - q->buf) + sizeof(*out_data)) % q->size;

  return 0;
}


int main(void)
{
  ring_t queue;
  const int buf_size = 5;
  int intdata =0x99887766;
  char indata = 0x22;
  char outdata;


  buf_init(&queue, buf_size);
  put(&queue, &indata, sizeof(indata));
  indata = 0x11;
  put(&queue, &indata, sizeof(indata));
  put(&queue, &intdata, sizeof(intdata));
  indata = 0x22;
  put(&queue, &indata, sizeof(indata));
  indata = 0x33;
  put(&queue, &indata, sizeof(indata));
  indata = 0x44;
  put(&queue, &indata, sizeof(indata));
  indata = 0x55;
  put(&queue, &indata, sizeof(indata));

  get(&queue, &outdata);
  printf("%x\n", outdata);
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
