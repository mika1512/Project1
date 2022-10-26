/// @file main .c
# include <stdio.h>
# include <math.h>
# define STB_IMAGE_IMPLEMENTATION

# include ".\headers\stb_image.h"
# define STB_IMAGE_WRITE_IMPLEMENTATION

# include "./headers\stb_image_write.h"
/*
* Delete a quarter of the image
* @param [in] image the input image
* @param [in] width the width of the image
* @param [in] height the height of the image
* @param [in] channel the channel of the image
*/
unsigned char image_background_delete ( unsigned char *img , unsigned char *img2 ,
							unsigned char *img3 , int width , int height , int channel){

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			int mika = 0;
			for ( int k = 0; k < channel ; k++){
				mika += abs(img [ i * width * channel + j * channel + k ] -  img2 [ i * width * channel + j * channel + k ]);
			}
			 if(mika < 147) {
          		for(int k = 0; k < channel ; k++) {
            		img [ i * width * channel + j * channel + k ] = img3 [ i * width * channel + j * channel + k ];
				}
			}
		}
	}
}

int main ()
{
//Declare variables
	int width , height , channel ;
	char forecast_img [] = ".\\images\\new_background.jpg";
	char background_img [] = ".\\images\\background.jpg";
	char foreground_img [] = ".\\images\\foreground.jpg";
	char result_path [] = "product_image.png";

//Read foreground image
	unsigned char * foreground = stbi_load ( foreground_img , &width , &height , &channel , 0);
	if ( foreground == NULL ){
	printf("\nError in loading the image foreground \n");
	exit(1) ;
	}
	//printf (" \nWidth = %d\n Height = %d\n Channel = %d\n", width , height , channel );

//Read background image
	unsigned char * background = stbi_load ( background_img , &width , &height , &channel , 0);
	if ( background == NULL ){
	printf("\nError in loading the image background \n");
	exit(1) ;
	}
	//printf (" \nWidth2 = %d\n Height2 = %d\n Channel2 = %d\n", width , height , channel );

//Read forecast image
	unsigned char * forecast = stbi_load ( forecast_img , &width , &height , &channel , 0);
	if ( forecast == NULL ){
	printf("\nError in loading the image forecast \n");
	exit(1) ;
	}
	//printf (" \nWidth3 = %d\n Height3 = %d\n Channel3 = %d\n", width , height , channel );

	image_background_delete (foreground , background, forecast, width , height , channel );

//Save image
	stbi_write_png ( result_path , width , height , channel , foreground , width * channel );
	printf ("Result in: %s ^^", result_path);
}