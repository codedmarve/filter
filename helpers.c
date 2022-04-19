#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    // iterating through the rows
    for (int i = 0; i < height; i++)
    {
        // iterating through the columns
        for (int j = 0; j < width; j++)
        {

            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            // calculating the average
            average = round(((float)red + (float)green + (float)blue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue, sepred, sepgreen, sepblue;

    for (int i = 0; i < height; i++)
    {
        // iterating through the rows
        for (int j = 0; j < width; j++)
        {
            // iterating through the columns
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            // calculating sepia for red
            sepred = round(0.393 * red + 0.769 * green + 0.189 * blue);
            // ensuring sepia red is less than or equal to 255
            if (sepred > 225)
            {
                image[i][j].rgbtRed = 225;
            }
            else
            {
                image[i][j].rgbtRed = sepred;
            }

            // calculating sepia green
            sepgreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            if (sepgreen > 225)
            {
                // esuring sepia green is not above 255
                image[i][j].rgbtGreen = 225;
            }
            else
            {
                image[i][j].rgbtGreen = sepgreen;
            }

            // calculating sepia blue
            sepblue = round(0.272 * red + 0.534 * green + 0.131 * blue);
            // ensuring sepia blue is not above 255
            if (sepblue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepblue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // iterating through the rows
        for (int j = 0; j < (width / 2); j++)
        {
            // iterating through the columns
            int tmpred = image[i][j].rgbtRed;
            int tmpgreen = image[i][j].rgbtGreen;
            int tmpblue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tmpred;
            image[i][width - j - 1].rgbtGreen = tmpgreen;
            image[i][width - j - 1].rgbtBlue = tmpblue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    // iterating through the rows
    for (int i = 0; i < height; i++)
    {
        // iterating through the rows
        for (int j = 0; j < width; j++)
        {
            int total_red, total_blue, total_green;
            total_red = total_blue = total_green = 0;
            float counter = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentx = i + x;
                    int currenty = j + y;

                    if (currentx < 0 || currentx > (height - 1) || currenty < 0 || currenty > (width - 1))
                    {
                        continue;
                    }

                    total_red += image[currentx][currenty].rgbtRed;
                    total_green += image[currentx][currenty].rgbtGreen;
                    total_blue += image[currentx][currenty].rgbtBlue;

                    counter++;
                }

                tmp[i][j].rgbtRed = round(total_red / counter);
                tmp[i][j].rgbtGreen = round(total_green / counter);
                tmp[i][j].rgbtBlue = round(total_blue / counter);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        // iterating through the rows
        for (int j = 0; j < width; j++)
        {
            // iterating through the columns
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}
