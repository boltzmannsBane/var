#include <notcurses/notcurses.h>
#include <unistd.h> // for sleep

int main() {
  struct notcurses_options opts = {
    .loglevel = NCLOGLEVEL_ERROR, // Set log level to see errors
  };
  struct notcurses* nc = notcurses_init(&opts, NULL);
  if (!nc) {
    return 1;
  }

  struct ncplane* stdplane = notcurses_stdplane(nc);
  if(ncplane_putstr(stdplane, "Hello World!") < 0){
    notcurses_stop(nc);
    return 2;
  }
  if(notcurses_render(nc) < 0){
    notcurses_stop(nc);
    return 3;
  }
  sleep(2); // Wait for 2 seconds before exiting

  notcurses_stop(nc);
  return 0;
}
