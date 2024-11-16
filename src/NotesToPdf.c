#include "NotesToPdf.h"
#include <stdlib.h>
#include <stdio.h>

// Function to load images from a folder
GList *load_images_from_folder(const char *folder_path)
{
    GList *file_list = NULL;
    GDir *dir = g_dir_open(folder_path, 0, NULL);
    if (!dir)
    {
        g_printerr("Could not open folder: %s\n", folder_path);
        return NULL;
    }

    const gchar *file_name;
    while ((file_name = g_dir_read_name(dir)))
    {
        if (g_str_has_suffix(file_name, ".jpg") ||
            g_str_has_suffix(file_name, ".png") ||
            g_str_has_suffix(file_name, ".jpeg"))
        {
            gchar *file_path = g_build_filename(folder_path, file_name, NULL);
            file_list = g_list_append(file_list, file_path);
        }
    }
    g_dir_close(dir);
    return file_list;
}

// Function to display images
void display_images(AppData *app)
{
    GList *l;
    int col = 0, row = 0;
    for (l = app->images; l != NULL; l = l->next)
    {
        gchar *image_path = (gchar *)l->data;

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 300, 300, TRUE, NULL); // Change size to 300x300
        GtkWidget *image_widget = gtk_image_new_from_pixbuf(pixbuf);
        g_object_unref(pixbuf);

        GtkWidget *event_box = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(event_box), image_widget);

        g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_image_clicked), app);

        gtk_grid_attach(GTK_GRID(app->grid), event_box, col, row, 1, 1);
        col++;
        if (col >= 2) // Adjust the number of columns to fit larger images
        {
            col = 0;
            row++;
        }
    }
    gtk_widget_show_all(app->grid);
}

// Callback for image clicks
void on_image_clicked(GtkWidget *widget, GdkEventButton *event, AppData *app)
{
    (void)event; // To remove unused parameter warning
    GtkWidget *image = gtk_bin_get_child(GTK_BIN(widget));
    const gchar *file_path = gtk_widget_get_name(image);
    app->ordered_images = g_list_append(app->ordered_images, g_strdup(file_path));

    g_print("Image clicked: %s\n", file_path);
}

// Generate PDF from ordered images
void generate_pdf(AppData *app)
{
    if (!app->ordered_images)
    {
        g_print("No images selected for PDF.\n");
        return;
    }

    cairo_surface_t *surface = cairo_pdf_surface_create("output.pdf", 595, 842);
    cairo_t *cr = cairo_create(surface);

    GList *l;
    for (l = app->ordered_images; l != NULL; l = l->next)
    {
        const gchar *file_path = (const gchar *)l->data;
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(file_path, NULL);

        double img_width = gdk_pixbuf_get_width(pixbuf);
        double img_height = gdk_pixbuf_get_height(pixbuf);
        double scale = fmin(595.0 / img_width, 842.0 / img_height);

        img_width *= scale;
        img_height *= scale;

        cairo_save(cr);
        cairo_translate(cr, (595 - img_width) / 2, (842 - img_height) / 2);
        gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);

        g_object_unref(pixbuf);
        cairo_show_page(cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    g_print("PDF generated as 'output.pdf'.\n");
}
