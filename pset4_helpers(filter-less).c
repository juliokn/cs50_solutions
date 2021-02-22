#include "helpers.h"
#include <math.h>           //so we can use round()
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //int is not precise enough, so only round() when storing on int, but make operations with float/double
            double avg = ((double) image[i][j].rgbtBlue + (double) image[i][j].rgbtRed + (double) image[i][j].rgbtGreen)/3; 
            image[i][j].rgbtRed = round(avg);                                                                               
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiared = (0.393 * (double) image[i][j].rgbtRed) + (0.769 * (double) image[i][j].rgbtGreen) + (0.189 * (double) image[i][j].rgbtBlue);
            if (sepiared > 255) //can't be bigger than 255, maximum value for 8bit color value, so must be capped
                sepiared = 255;
            double sepiagreen = (0.349 * (double) image[i][j].rgbtRed) + (0.686 * (double) image[i][j].rgbtGreen) + (0.168 * (double) image[i][j].rgbtBlue);
            if (sepiagreen > 255)
                sepiagreen = 255;
            double sepiablue = (0.272 * (double) image[i][j].rgbtRed) + (0.534 * (double) image[i][j].rgbtGreen) + (0.131 * (double) image[i][j].rgbtBlue);
            if (sepiablue > 255)
                sepiablue = 255;
            image[i][j].rgbtRed = round(sepiared);
            image[i][j].rgbtBlue = round(sepiablue);
            image[i][j].rgbtGreen = round(sepiagreen);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int limitwidth = 0;
    
    if ((height * width) % 2 != 0)          //if number of pixels is odd the center pixel wont swap
        limitwidth = (width - 1) / 2;       
    
    else                                //if number of pixels is even theres no center pixel
        limitwidth = (width) / 2;
    
    for (int j = 0; j < height; j++)            //jumping rows
    {
        for (int i = 0; i <= limitwidth / 2; i++) //jumping columns
        {
            RGBTRIPLE tmp = image[j][i];
            image[j][i] = image[j][width-1-i];
            image[j][width-1-i] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    double qty = 0;
    double temp_red = 0;
    double temp_green = 0;
    double temp_blue = 0;

    for (int i = 0; i < height; i++) //copying the image into a new image so we use the new__image as reference
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int ref_height = i + 1; ref_height >= (i - 1); ref_height--) 
            {
                for (int ref_width = j + 1; ref_width >= (j - 1); ref_width--)
                {
                    if ((ref_height >= 0) && (ref_height < height) && (ref_width >= 0) && (ref_width < width))
                    {
                        temp_red += (double) image[ref_height][ref_width].rgbtRed;
                        temp_green += (double) image[ref_height][ref_width].rgbtGreen;
                        temp_blue += (double) image[ref_height][ref_width].rgbtBlue;
                        qty++;
                    }
                }
            }
            int avg_red = round(temp_red / qty);
            int avg_blue = round(temp_blue / qty);
            int avg_green = round(temp_green / qty);
           
            new_image[i][j].rgbtRed = avg_red;
            new_image[i][j].rgbtBlue = avg_blue;
            new_image[i][j].rgbtGreen = avg_green;
           
            qty = 0;
            temp_red = 0;
            temp_green = 0;
            temp_blue = 0;
           
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    
    return;
}