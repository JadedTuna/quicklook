#include "quicklook.h"

void quicklook_print_usage(void) {
    fprintf(stderr, USAGE, PROGNAME);
    exit(EXIT_FAILURE);
}

void quicklook_textarea_init(void) {
    scrollarea = gtk_scrolled_window_new(NULL, NULL);

    textarea = gtk_text_view_new();
    PangoFontDescription *font = \
        pango_font_description_from_string("monospace 11");

    gtk_widget_override_font(textarea, font);
    pango_font_description_free(font);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textarea));

    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        fprintf(stderr, "%s: fopen(null): %s\n",
                PROGNAME,
                strerror(errno));
        fclose(fp);

        exit(EXIT_FAILURE);
    }

    char *buf;
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buf = malloc(fsize + 1);
    fread(buf, fsize, 1, fp);
    buf[fsize] = '\0';

    gtk_text_buffer_set_text(buffer, buf, -1);

    free(buf);
    fclose(fp);

    gtk_text_view_set_editable(GTK_TEXT_VIEW(textarea), FALSE);

    gtk_container_add(GTK_CONTAINER(scrollarea), textarea);
    gtk_container_add(GTK_CONTAINER(window), scrollarea);
}

void quicklook_init(void) {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gwindow = GTK_WINDOW(window);
    gtk_window_set_default_size(gwindow, 480, 360);
    gtk_window_set_title(gwindow, FILENAME);

    quicklook_textarea_init();

    g_signal_connect(window, "destroy",
                    (GCallback) gtk_main_quit, NULL);

    gtk_widget_show_all(window);
}

void quicklook_main(void) {
    gtk_main();
}

int main(gint argc, gchar* argv[]) {
    PROGNAME = argv[0];

    if (argc != 2) {
        quicklook_print_usage();
        return EXIT_FAILURE;
    }

    FILENAME = argv[1];

    gtk_init(&argc, &argv);
    quicklook_init();
    quicklook_main();

    return EXIT_SUCCESS;
}
