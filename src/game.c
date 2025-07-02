// This test shader and user interface support

#include "game.h"
#include "weaver/metafont.h"
static struct user_interface *game;


void main_loop(void){ // The game loop
 LOOP_INIT: // Code executed during loop initialization
  game = W.new_interface(NULL, "game.mf",
		      W.width / 2, W.height / 2, 1.0,
		      W.width, W.height);
  if(game == NULL)
    exit(1);
 LOOP_BODY: // Code executed every loop iteration
  if(W.keyboard[W_ESC])
    Wexit_loop();
  else if(W.keyboard[W_UP]){
    _Wwrite_numeric_variable(game -> _internal_data, "control", 1.0);
  }
  else if(W.keyboard[W_DOWN]){
    _Wwrite_numeric_variable(game -> _internal_data, "control", -1.0);
  }
 LOOP_END: // Code executed at the end of the loop
    return;
}

int main(void){
  Winit(); // Initializes Weaver
  Wloop(main_loop); // Enter a new game loop
  return 0;
}
