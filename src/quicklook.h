#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const char *USAGE = "" \
"usage: %s file\n";

const char *PROGNAME = NULL;
const char *FILENAME = NULL;

GtkWidget *window;
GtkWindow *gwindow;

GtkWidget *textarea;
GtkTextBuffer *buffer;
GtkWidget *scrollarea;
