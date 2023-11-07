#include <notcurses/notcurses.h>
#include <unistd.h> // for usleep()

#define BOX_CHAR "▄" // This is a Unicode block character

int main(void) {
    struct notcurses_options options = {
        .flags = NCOPTION_NO_ALTERNATE_SCREEN | NCOPTION_SUPPRESS_BANNERS,
    };
    struct notcurses* nc = notcurses_core_init(&options, NULL);
    if(nc == NULL) {
        return -1;
    }

    struct ncplane* stdplane = notcurses_stdplane(nc);

    // Get the dimensions of the plane
    unsigned rows, cols;
    ncplane_dim_yx(stdplane, &rows, &cols);

    // Create a new plane for the box with a size of 3x6 characters
    struct ncplane_options nopts = {
        .y = 1,
        .x = 1,
        .rows = 3,
        .cols = 6,
        .userptr = NULL,
        .name = "box",
        .resizecb = NULL,
        .flags = 0
    };
    struct ncplane* boxplane = ncplane_create(stdplane, &nopts);
    if(boxplane == NULL) {
        notcurses_stop(nc);
        return -1;
    }

    // Set the box's background color to blue and foreground to white
    uint64_t channels = 0;
    ncchannels_set_fg_rgb(&channels, 0xffffff);
    ncchannels_set_bg_rgb(&channels, 0x0000ff);
    ncplane_set_base(boxplane, BOX_CHAR, 0, channels);

    for(unsigned y = 1; y < rows - 3; ++y) {
        for(unsigned x = 1; x < cols - 6; ++x) {
            // Move the boxplane's origin
            ncplane_move_yx(boxplane, y, x);

            // Render the scene
            if(notcurses_render(nc)) {
                notcurses_stop(nc);
                return -1;
            }

            // Sleep for a bit to slow down the movement
            usleep(50000); // 50ms
        }
    }

    // Wait for user input
    notcurses_get_blocking(nc, NULL);

    // Clean up
    ncplane_destroy(boxplane);
    notcurses_stop(nc);

    return 0;
}
