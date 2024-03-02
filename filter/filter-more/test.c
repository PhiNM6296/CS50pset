// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a new image with a pillow outside so it's easier to calculate edge value of the matrix
    RGBTRIPLE blur[height+2][width+2];
    //make the pillow (+1 in all dimension to the original image)
    for (int i = 0; i < height+2; i++) {
        for (int j = 0; j < width+2; j++) {
            blur[i][j].rgbtRed=0;
            blur[i][j].rgbtBlue=0;
            blur[i][j].rgbtGreen=0;
        }
    }
    //copy the original image in middle of the pillow
    for (int i = 1; i < height + 1 ; i++) {
        for (int j = 1; j < width + 1; j++) {
            blur[i][j].rgbtRed = image[i-1][j-1].rgbtRed;
            blur[i][j].rgbtBlue = image[i-1][j-1].rgbtBlue;
            blur[i][j].rgbtGreen = image[i-1][j-1].rgbtGreen;
        }
    }
    //blur the image by the value from the image pillow
    for (int i = 1; i < height + 1; i++) {
        for (int j = 1; j < width + 1; j++) {
            //set all the value from the image to 0, so that we can append new value
            image[i-1][j-1].rgbtRed = 0;
            image[i-1][j-1].rgbtBlue = 0;
            image[i-1][j-1].rgbtGreen = 0;
            // pixel count number of pixel around the image, not count the pillow
            // so that we can calculate average
            int pixel = 0;
            //2 for loop above loop through the image inside the pillow, not the original image
            // then we will copy the new value from the average to the corresponding value in the original image
            // 2 for loop below loop through all the surrounding value of the image
            // if that value is from the pillow, then skip it, if not, calculate as normal
            for (int a = i - 1; a <= i + 1; a++) {
                for (int b = j - 1; b <= j + 1; b++) {
                    if ((blur[a][b].rgbtRed) == 0 && (blur[a][b].rgbtBlue) == 0 && (blur[a][b].rgbtGreen) == 0) {
                        image[i-1][j-1].rgbtRed += (blur[a][b].rgbtRed);
                        image[i-1][j-1].rgbtRed += (blur[a][b].rgbtBlue);
                        image[i-1][j-1].rgbtRed += (blur[a][b].rgbtGreen);
                        pixel++;
                    }
                }
            }
            //after append, just calculate the average (divide after append sum to minimize error)
            image[i-1][j-1].rgbtRed = round((image[i-1][j-1].rgbtRed)/pixel);
            image[i-1][j-1].rgbtBlue = round((image[i-1][j-1].rgbtBlue)/pixel);
            image[i-1][j-1].rgbtGreen = round((image[i-1][j-1].rgbtGreen)/pixel);
        }
    }
    // it should loop throug the whole pillow image, calculate the blur the save it to the original image tho
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //X filter:
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
    //make a new image with a pillow outside so it's easier to calculate edge value of the matrix
    RGBTRIPLE P[height+2][width+2];
    //make the pillow (+1 in all dimension to the original image)
    for (int i = 0; i < height+2; i++) {
        for (int j = 0; j < width+2; j++) {
            P[i][j].rgbtRed=0;
            P[i][j].rgbtBlue=0;
            P[i][j].rgbtGreen=0;
        }
    }
    //copy the original image in middle of the pillow
    for (int i = 1; i < height + 1 ; i++) {
        for (int j = 1; j < width + 1; j++) {
            P[i][j].rgbtRed = image[i-1][j-1].rgbtRed;
            P[i][j].rgbtBlue = image[i-1][j-1].rgbtBlue;
            P[i][j].rgbtGreen = image[i-1][j-1].rgbtGreen;
        }
    }
    for (int i = 1; i < height + 1; i++) {
        for (int j = 1; j < width + 1; j++) {
            //set all the value from the image to 0, so that we can append new value
            image[i-1][j-1].rgbtRed = 0;
            image[i-1][j-1].rgbtBlue = 0;
            image[i-1][j-1].rgbtGreen = 0;
            int results[3] = {0};
            for (int a = -1; a <= 1 ; a++) {
                for (int b = - 1; b <= 1; b++) {
                    results[0] += Gx[a+1][b+1]*P[i+a][j+b].rgbtRed;
                    results[1] += Gx[a+1][b+1]*P[i+a][j+b].rgbtBlue;
                    results[2] += Gx[a+1][b+1]*P[i+a][j+b].rgbtGreen;
                    }
                }
            for (int a = -1; a <= 1 ; a++) {
                for (int b = - 1; b <= 1; b++) {
                    image[i-1][j-1].rgbtRed += Gy[a+1][b+1]*P[i+a][j+b].rgbtRed;
                    image[i-1][j-1].rgbtBlue += Gy[a+1][b+1]*P[i+a][j+b].rgbtBlue;
                    image[i-1][j-1].rgbtGreen += Gy[a+1][b+1]*P[i+a][j+b].rgbtGreen;
                    }
                }
            image[i-1][j-1].rgbtRed = pow(image[i-1][j-1].rgbtRed,2) + pow(results[0],2);
            image[i-1][j-1].rgbtBlue = pow(image[i-1][j-1].rgbtBlue,2) + pow(results[1],2);
            image[i-1][j-1].rgbtGreen = pow(image[i-1][j-1].rgbtGreen,2) + pow(results[2],2);
            if (round(sqrt(image[i-1][j-1].rgbtRed)) > 255) {
                image[i-1][j-1].rgbtRed = 255;
            }
            else {
                image[i-1][j-1].rgbtRed = round(sqrt(image[i-1][j-1].rgbtRed));
            }
            if (round(sqrt(image[i-1][j-1].rgbtBlue)) > 255) {
                image[i-1][j-1].rgbtBlue = 255;
            }
            else {
                image[i-1][j-1].rgbtBlue = round(sqrt(image[i-1][j-1].rgbtBlue));
            }
            if (round(sqrt(image[i-1][j-1].rgbtGreen)) > 255) {
                image[i-1][j-1].rgbtGreen = 255;
            }
            else {
                image[i-1][j-1].rgbtGreen = round(sqrt(image[i-1][j-1].rgbtGreen));
            }
            }
        }

    return;
}

