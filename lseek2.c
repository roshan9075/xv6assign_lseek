#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "syscall.h"
//#include "types.h"
#include "x86.h"


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


int main(int argc, char *argv[]) {
	
	
	int file_length;
	int partfile_len;
	int re;
	int fd;
	int copy_fd;
	//int copy_re;
	int off;

	
	
	if(argc != 2) {
		exit();
	}
	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		printf(0, "%s", "file open:Failed");
		exit();
	}
	file_length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	partfile_len = file_length / 10;
	char str[partfile_len];
	copy_fd = open("copyfile", O_CREATE | O_RDWR);
	if(copy_fd == -1) {
		printf(0, "%s", "copyfile: open failed");
		exit();
	}
	lseek(copy_fd, file_length, SEEK_END);
	if(file_length > 9) {	
		for(int i = 0;i < 10; i++) {
			off = ((i * 7) + 1) % 10;  //random sequence generator linear recurrence relation		
			lseek(fd, partfile_len * off, SEEK_SET);
			lseek(copy_fd, partfile_len * off, SEEK_SET);
			re = read(fd, str, partfile_len);
			if(re == -1) {
				printf(0, "%s", "bad_read");
				exit();
			}
			write(copy_fd, &str, partfile_len); 
		}
	}
	lseek(copy_fd, partfile_len * 10, SEEK_SET);
	lseek(fd, partfile_len * 10, SEEK_SET);
	if(file_length % 10) {
		char str1[file_length % 10];
		read(fd, str1, file_length % 10);
		write(copy_fd, &str1, file_length % 10);
		//printf(0, "%s", str1);
	}
	
	close(copy_fd);
	close(fd);
	exit();
}
