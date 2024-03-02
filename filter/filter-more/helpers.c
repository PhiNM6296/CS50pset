#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int temp = 0;
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0 + 0.5;
            temp = (int)avg;
            if (temp > 255)
            {
              temp = 255;
            }
            image[i][j].rgbtRed = temp;
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtGreen = temp;
        }
    }
    return;
}

// remember to pass by reference, not pass by values (use pointer)
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1=*pixel2;
    *pixel2=temp;

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //temp to swap pixel value
    RGBTRIPLE temp;
    //width is an even number -> swap all the column
    if (width % 2 ==0) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width/2; j++) {
                swap(&image[i][j],&image[i][(width - 1)- j]);
            }
        }
    }
    else {
        for (int i = 0; i < height; i ++) {
            for (int j = 0; j < (width + 1)/2; j++) {
                swap(&image[i][j],&image[i][(width - 1)- j]);
            }
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image to store blurred result
    RGBTRIPLE temp[height][width];

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Loop through the surrounding pixels (including the current pixel)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di; // Neighbor pixel row index
                    int nj = j + dj; // Neighbor pixel column index

                    // Check if the neighbor pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate average blur value and update temporary image
            temp[i][j].rgbtRed = round((float)sumRed / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }

    // Copy the blurred result back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image with zero padding
    RGBTRIPLE copy[height + 2][width + 2];

    // Initialize the copy with zeros
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            copy[i][j].rgbtRed = 0;
            copy[i][j].rgbtGreen = 0;
            copy[i][j].rgbtBlue = 0;
        }
    }

    // Copy the original image to the center of the copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i + 1][j + 1] = image[i][j];
        }
    }

    // Define the edge detection kernels
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Apply edge detection to the original image
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            int GxRed = 0, GxGreen = 0, GxBlue = 0;
            int GyRed = 0, GyGreen = 0, GyBlue = 0;

            // Convolve with the Gx and Gy kernels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    GxRed += copy[i + di][j + dj].rgbtRed * Gx[di + 1][dj + 1];
                    GxGreen += copy[i + di][j + dj].rgbtGreen * Gx[di + 1][dj + 1];
                    GxBlue += copy[i + di][j + dj].rgbtBlue * Gx[di + 1][dj + 1];

                    GyRed += copy[i + di][j + dj].rgbtRed * Gy[di + 1][dj + 1];
                    GyGreen += copy[i + di][j + dj].rgbtGreen * Gy[di + 1][dj + 1];
                    GyBlue += copy[i + di][j + dj].rgbtBlue * Gy[di + 1][dj + 1];
                }
            }

            // Compute the magnitude of the gradient
            int magnitudeRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int magnitudeGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int magnitudeBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            // Ensure the magnitude values are within the range [0, 255]
            image[i - 1][j - 1].rgbtRed = (magnitudeRed > 255) ? 255 : magnitudeRed;
            image[i - 1][j - 1].rgbtGreen = (magnitudeGreen > 255) ? 255 : magnitudeGreen;
            image[i - 1][j - 1].rgbtBlue = (magnitudeBlue > 255) ? 255 : magnitudeBlue;
        }
    }
}
