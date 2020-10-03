#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
 
 


char* resize(char* cp, int size){
	char* ncp = malloc(size*2);
	int i;
	for(i = 0; i < size; i++) {
		*(ncp + i) = *(cp + i);
	}
	return ncp;
}
 
char* loadMal(char* file) {
	int bSize = 512;
	char buf [bSize];
	int fd = open(file, O_RDONLY);
	int n = 0;
	int cIter = 0;
	int cMax = bSize;
	char* cp = malloc(bSize);
	do {
		n = read(fd, buf, bSize);
		int i;
		for(i = 0; i < n; i++){
			if(cIter*bSize + i >= cMax) {			
				cp = resize(cp, cMax);
				cMax *= 2;
			}
			*(cp + cIter*bSize + i) = buf[i];
		}
		cIter++;
	} while (n == bSize);
	return cp;
}


void printLastC(char* file, int ent) { 
	char* cp = loadMal(file);
	printf(1, (cp + strlen(cp) - ent));
}


void printLast(char* file, int ent) { 
	char* cp = loadMal(file);
	int n = strlen(cp);
	while(ent > 0){
		if(*(cp + n) == '\n') {
			ent--;
		}
		n--;
	}
	printf(1, (cp + n));
}


void printAfterC(char* file, int ent) { 
	char* cp = loadMal(file);
	printf(1, (cp + ent));
}


void printAfter(char* file, int ent) { 
	char* cp = loadMal(file);
	int n = 0;
	while(ent > 0){
		if(*(cp + n) == '\n') {
			ent--;
		}
		n++;
	}
	printf(1, (cp + n));
}
 
int main(int argc, char* argv[]) {
	if(argc == 2) { 
		printLast(argv[1], 10);
	} else if(strcmp(argv[1], "-n") == 0){
		if(argv[2][0] != '+') {
			printLast(argv[3], atoi(argv[2]));
		}else {
			printAfter(argv[3], atoi((argv[2]+1)));
		}
	} else {
		if(argv[2][0] != '+') {
			printLastC(argv[3], atoi(argv[2]));
		}else {
			printAfterC(argv[3], atoi((argv[2]+1)));
		}
	}
	exit();
}




