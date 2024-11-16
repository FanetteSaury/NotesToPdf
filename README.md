# NotesToPdf
A GTK-based application that allows users to convert a folder of images into a single PDF.
## Specifications
The app automatically scales images to their maximum size while maintaining their aspect ratio. Users can either use a predefined order or manually click on images to specify the desired order before generating the PDF.

.jpg, .png, .jpeg supported
A4 pdf format

# Usage


## Dependencies

This application uses:
- **GTK**: For the user interface.
- **GDK-Pixbuf**: For image scaling and processing.
- **Cairo**: For generating PDF output.
### Install Dependencies
#### Ubuntu/Debian

```bash
sudo apt update
sudo apt install build-essential pkg-config libgtk-3-dev libcairo2-dev libgdk-pixbuf2.0-dev
```