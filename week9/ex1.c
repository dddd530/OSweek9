#include <stdio.h>
#include <stdlib.h>



struct page{
  //id and counter of page
  int id;
  unsigned int c;
};


//function for searching page in page table
struct page* find_page(struct page *pgs, int id, int pgs_n){
  for(int i = 0; i < pgs_n; i++){
    if (pgs[i].id == id){
      return pgs + i;
    }
  }
  return NULL;
};


//function for finding avaliable place for page in page table
struct page* page_avaliable(struct page *pgs, int pgs_n){
  int low_i, low_c;
  low_i = 0;
  low_c = 1<<31;
  for(int i = 0; i < pgs_n; i++){
    if(pgs[i].id == 0){
      return pgs + i;
    }

    if (pgs[i].c < low_c){
      low_c = pgs[i].c;
      low_i = pgs[i].id;
    }
  }
  return pgs + low_i;
};


int main() {

  //number of frames in page table
  int frames_number;
  printf("Enter number of pages\n");
  scanf("%d", &frames_number);

  //page table
  struct page *pages = calloc(frames_number, sizeof(struct page));


  FILE *input_file = fopen("input.txt", "r");

  //checking if file opened correctly
  if(input_file == NULL)
	{
		printf("Error with file opening");
		return 1;
	}


  int id;
  int hit, miss;
  hit = 0;
  miss = 0;

  //while there is next reference in sequence
  while(fscanf(input_file, "%d", &id) == 1){
    //checking if reference is in page table
    struct page* pg = find_page(pages, id, frames_number);

    //increasing number of hits if yes
    if (pg != NULL){
      hit++;
    }

    //increasing number of misses and placing page in page table if no
    else{
      miss++;

      pg = page_avaliable(pages, frames_number);

      pg->id = id;
      pg->c = 0;

    }
    //moving bits in counter
    for (int i = 0; i < frames_number; i++){
      pages[i].c >>= 1;
    }


  }
  fclose(input_file);

  int all = hit + miss;
  double hit_to_miss = (double)hit/miss, hit_to_all = (double)hit/all, miss_to_all = (double)miss/all;


  //result of program
  printf("Number of hits: %d\n", hit);
  printf("Number of misses: %d\n", miss);
  printf("Hit/Miss: %lf\n",hit_to_miss);
  printf("Hit/All: %lf\n",hit_to_all);
  printf("Miss/All: %lf\n",miss_to_all);
  free(pages);



  return 0;
}