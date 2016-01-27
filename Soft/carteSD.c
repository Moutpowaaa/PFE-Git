
#define SPI_MOSI			pin24_port1
#define SPI_MISO			pin23_port1
#define SPI_SCLK			pin20_port1
#define SPI_CS_CARTE_SD		pin21_port1

#define SD_CARD_NAME		"nameOfSD"


// Attention à bien remplacer "nameOfSD" par le nom de la carte SD
SDFileSystem sd(SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS_CARTE_SD, SD_CARD_NAME); 

char * path = strcat(SD_CARD_NAME, "/");
FILE * fp;

int SDCard_open(char * fileName)
{
	mkdir((*path), 0777);	// On créé le répertoire si besoin
	
	char * pathAndName = strcat((*path), (*fileName));
	*fp = fopen((*pathAndName), "w");	// On ouvre en ecriture par défaut
	
	if(fp == NULL) 
	{
        printf("Could not open file for write\n");
        return -1;
    }
    else
    {
    	return 0;
    }
}

void SDCard_close()
{
	fclose(fp);
}


int SDCard_write(char * stringToWrite) 
{   
    fprintf(fp, (*stringToWrite));
}

