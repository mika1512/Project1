
# include <stdio.h>
# include <math.h>
# define STB_IMAGE_IMPLEMENTATION

# include ".\headers\stb_image.h"
# define STB_IMAGE_WRITE_IMPLEMENTATION

# include "./headers\stb_image_write.h"
unsigned char image_background_delete ( unsigned char *foreground, unsigned char *background, unsigned char *newbg, int width, int height, int channel){
	for (int i=0; i <height; i++){
		for (int j=0; j <width; j++){
			int a = 0;
			for ( int k=0; k <channel; k++){
				a += abs(foreground [i *width *channel +j *channel +k] - background [i *width *channel +j *channel +k]);
			}
			 if(a<155) {
          		for(int k=0; k <channel; k++) {
            		foreground[i *width *channel +j *channel +k] = newbg [i *width *channel +j *channel +k];
				}
			}
		}
	}
}

int main ()
{
	int width, height, channel ;
	char forecast_img [] = ".\\images\\new_background.jpg";
	char background_img [] = ".\\images\\background.jpg";
	char foreground_img [] = ".\\images\\foreground.jpg";
	char result_path [] = "product_image.png";

	unsigned char* foreground = stbi_load ( foreground_img, &width, &height, &channel, 0);
	if (foreground == NULL)
	{
		printf("\nError in loading the image foreground \n");
		exit(1);
	}

	unsigned char* background = stbi_load ( background_img , &width , &height , &channel , 0);
	if (background == NULL)
	{
		printf("\nError in loading the image background \n");
		exit(1);
	}

	unsigned char* forecast = stbi_load ( forecast_img , &width , &height , &channel , 0);
	if (forecast == NULL)
	{
		printf("\nError in loading the image forecast \n");
		exit(1);
	}

	image_background_delete (foreground, background, forecast, width, height, channel);
	stbi_write_png (result_path, width, height, channel, foreground, width* channel);
	printf ("Result in: %s ^^", result_path);
}
