#include <notcurses/notcurses.h>

int main(void) {
  struct notcurses_options options = {
    .flags = NCOPTION_NO_ALTERNATE_SCREEN | NCOPTION_SUPPRESS_BANNERS,
  };
  struct notcurses* nc = notcurses_core_init(&options, NULL);
  if (nc == NULL) {
    return -1;
  }

  struct ncplane* stdplane = notcurses_stdplane(nc);

  // Use unsigned int for dimensions
  unsigned rows, cols;
  ncplane_dim_yx(stdplane, &rows, &cols);

  const char* message = "Hello, World!";
  int message_len = strlen(message);
  unsigned y = rows / 2;
  unsigned x = (cols - message_len) / 2;

  if (ncplane_putstr_yx(stdplane, y, x, message) < 0) {
    notcurses_stop(nc);
    return -1;
  }

  notcurses_render(nc);

  // Use notcurses_get_blocking to wait for key press
  ncinput ni; // Declare the ncinput struct
  notcurses_get_blocking(nc, &ni); // Correct function call

  notcurses_stop(nc);

  return 0;
}
