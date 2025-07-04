// This test shader and user interface support

#include "game.h"
#include "weaver/metafont.h"
static struct user_interface *game;
static struct sound *hit;

#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];
static bool reload = false;

char *get_source(void){
  FILE *fp;
  size_t newLen;
  char filename[20];
  strcpy(filename, "image/game.mf");
  if(filename[0] != '\0'){
    fp = fopen(filename, "r");
    if(fp == NULL)
      return NULL;
    newLen = fread(buffer, sizeof(char), BUFFER_SIZE-1, fp);
    if(ferror(fp) != 0){
      return NULL;
    } else {
      buffer[newLen++] = '\0';
    }
    fclose(fp);
    return buffer;
  }
  else return NULL;
}

void put_source(char *source){
  FILE *fp;
  char filename[20];
  strcpy(filename, "image/game.mf");
  if(filename[0] != '\0'){
    size_t ret, size;
    fp = fopen(filename, "w");
    if(fp == NULL){
      perror(filename);
      return;
    }
    size = strlen(source);
    ret = fwrite(source, 1, size, fp);
    if(ret != size){
      perror(filename);
      return;
    }
    fclose(fp);
    reload = true;
  }
}


void main_loop(void){ // The game loop
 LOOP_INIT: // Code executed during loop initialization
  game = W.new_interface(NULL, "game.mf",
		      W.width / 2, W.height / 2, 1.0,
		      W.width, W.height);
  hit = W.new_sound("nutfall.wav");
  if(game == NULL || hit == NULL)
    exit(1);
 LOOP_BODY: // Code executed every loop iteration
#if !defined(__EMSCRIPTEN__)
  if(W.keyboard[W_ESC])
    Wexit_loop();
#endif
  if(W.keyboard[W_UP] || W.mouse.dy > 0){
    _Wwrite_numeric_variable(game -> _internal_data, "control", 1.0);
  }
  else if(W.keyboard[W_DOWN] || W.mouse.dy < 0){
    _Wwrite_numeric_variable(game -> _internal_data, "control", -1.0);
  }
  if(_Wread_numeric_variable(game -> _internal_data, "sound") == 1.0){
    W.play_sound(hit);
    _Wwrite_numeric_variable(game -> _internal_data, "sound", 0.0);
  }
  if(reload){
    reload = false;
    Wloop(main_loop);
  }
 LOOP_END: // Code executed at the end of the loop
    return;
}

int main(void){
  Winit(); // Initializes Weaver
  Wloop(main_loop); // Enter a new game loop
  return 0;
}
