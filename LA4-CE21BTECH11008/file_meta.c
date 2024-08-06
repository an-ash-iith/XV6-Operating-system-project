#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include <kernel/file.h>

#define size_of_block 512

char roll[14]="CE21BTECH11008";

// Function to create a file with the given name and size
void file_create(char *filename, int size) {
    int fd = open(filename, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("Error creating file\n");
        exit(0);
    }

    char buffer[size_of_block];
   

    // Write the content size to all disk blocks
    for (unsigned int i = 0; i < size_of_block; i++) {

        buffer[i]=roll[i%14];

        //storing to the buffer as each charactr have size of 1 byte 
        //each block contain one 512 character if present
    }

    // Write the buffer to the file
    for (unsigned int i = 0; i < size; i += size_of_block) {
        write(fd, buffer, size_of_block);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("No sufficient argumetn given");
        exit(0);
    }

    char *file_name = argv[1];
    unsigned int size = atoi(argv[2]);

    // Create the file
    file_create(file_name, size);

    // Get file information
    struct stat st;

    //stat function get the information 

    if (stat(file_name, &st) < 0) {
        printf("Error getting file information\n");
        exit(0);
    }


// st->dev = ip->dev;
//   st->ino = ip->inum;
//   st->type = ip->type;
//   st->nlink = ip->nlink;
//   st->size = ip->size;

printf("Printing content of the inode \n ");

    printf("Node number is : %d\n", st.ino);
    //printf("Node size is : %d\n", st.size);
   //// printf("link number is : %d\n", st.nlink);
   // printf("Node type is : %d\n", st.ino);


    printf("File contents:\n");
    int fd = open(file_name, O_RDONLY);

    
    char buffer[size_of_block];

    int no_byte;
    while ((no_byte = read(fd, buffer, size_of_block)) > 0) {
        write(1, buffer, no_byte);
    }
    close(fd);

   //printing the disc block number 

    for (int i = 0; i < st.size / size_of_block; i++) {
        printf("%d ", i);
    }
    printf("\n");

    exit(0);
}





