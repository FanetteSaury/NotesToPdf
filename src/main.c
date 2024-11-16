#include "NotesToPdf.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    if (argc < 2)
    {
        g_print("Usage: %s <folder_path>\n", argv[0]);
        return 1;
    }

    AppData app = {0};
    app.images = load_images_from_folder(argv[1]);

    if (!app.images)
    {
        g_print("No images found in the folder.\n");
        return 1;
    }

    GtkBuilder *builder = gtk_builder_new_from_file("src/layout/layout.ui");
    app.window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    app.grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));
    GtkWidget *generate_button = GTK_WIDGET(gtk_builder_get_object(builder, "generate_button"));
    g_signal_connect(generate_button, "clicked", G_CALLBACK(generate_pdf), &app);

    display_images(&app);

    gtk_widget_show_all(app.window);
    gtk_main();

    g_list_free_full(app.images, g_free);
    g_list_free_full(app.ordered_images, g_free);

    return 0;
}
