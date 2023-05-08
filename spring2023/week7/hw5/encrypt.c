#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define MAX 10240
//encrypt the message and write the result to file fd
void encrypt(char *message, unsigned char key, unsigned char shift, int fd)
{
	int len = strlen(message);
	printf("len = %d\n", len);
	int msg[len];

	for(int i = 0; i<len; i++)
		msg[i] = (message[i] << shift) ^ key;
	write(fd, msg, len*sizeof(int));
	printf("%s\n", (char *)msg);
}

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		printf("Usage: %s plain-text-file encrypted-file key shift\n", argv[0]);
		return -1;
	}

    char message[MAX];
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        printf("Cannot open file %s\n", argv[1]);
        return -1;
    }
    int len = read(fd, message, MAX);
	close(fd);
	assert(len > 0);

	//note how we open the file
	fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if(fd < 0)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	int key = atoi(argv[3]);
	int shift = atoi(argv[4]);
	assert(key >= 0 && key <= 255);
	assert(shift >=0 && shift <= 24);
	encrypt(message, key, shift, fd);
	//remember to close the file
	close(fd);
	return 0;
}
