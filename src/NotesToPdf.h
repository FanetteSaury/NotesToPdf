#ifndef NOTES_TO_PDF_H
#define NOTES_TO_PDF_H

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <math.h>

// Structure to store application data
typedef struct
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *preview;
    GList *images;         // List of image file paths
    GList *ordered_images; // Ordered list of images
} AppData;

// Function declarations
GList *load_images_from_folder(const char *folder_path);
void display_images(AppData *app);
void on_image_clicked(GtkWidget *widget, GdkEventButton *event, AppData *app);
void generate_pdf(AppData *app);

#endif
