#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

	

    int A[2];
	pipe(A);
	pid_t pid1 = fork();
	if (!pid1) {
		dup2(A[1], 1);
		close(A[0]);
		close(A[1]);
		execlp("cat","cat", "log.txt", NULL);
		exit(EXIT_FAILURE);
	}
    

	int B[2]; // pipe B
	pipe(B);
	pid_t pid2 = fork();
	if (!pid2) { // cut
		dup2(A[0], 0);
		close(A[0]);
		close(A[1]);

		dup2(B[1], 1);
		close(B[0]);
		close(B[1]);
		execlp("cut","cut", "-f4", "-d ", NULL);
		exit(EXIT_FAILURE);
	}

	close(A[0]);
	close(A[1]);
    
	int C[2];
	pipe(C);

	pid_t pid3 = fork();
	if (!pid3) { // sed
		dup2(B[0], 0);
		close(B[0]);
		close(B[1]);

		dup2(C[1], 1);
		close(C[0]);
		close(C[1]);

		execlp("cut","cut", "-f1", "-d:", NULL);
		exit(EXIT_FAILURE);
	}


	
	close(B[0]);
	close(B[1]);
    
    
    
    
    int P[2];
    pipe(P);
    
    pid_t pid0 = fork();
    if (!pid0) { // sed
        dup2(C[0], 0);
        close(C[0]);
        close(C[1]);
        
        dup2(P[1], 1);
        close(P[0]);
        close(P[1]);
        
        execlp("tr","tr", "-d", "[", NULL);
        exit(EXIT_FAILURE);
    }
    
    
    
    close(C[0]);
    close(C[1]);

    

    int E[2];
	pipe(E);

	pid_t pid5 = fork();
	if (!pid5) {
		dup2(P[0], 0);
		close(P[0]);
		close(P[1]);

		dup2(E[1], 1);
		close(E[0]);
		close(E[1]);

    
		execlp("grep","grep", "-v", "-", NULL);
		exit(EXIT_FAILURE);
	}
    close(P[0]);
    close(P[1]);
    
    int F[2];
	pipe(F);

	pid_t pid6 = fork();
	if (!pid6) { // sed
		dup2(E[0], 0);
		close(E[0]);
		close(E[1]);

		dup2(F[1], 1);
		close(F[0]);
		close(F[1]);

		execlp("cut","cut", "-f1", "-d " , NULL);
		exit(EXIT_FAILURE);
	}
    close(E[0]);
    close(E[1]);
    
    int G[2];
	pipe(G);

	pid_t pid7 = fork();
	if (!pid7) { // sed
		dup2(F[0], 0);
		close(F[0]);
		close(F[1]);

		dup2(G[1], 1);
		close(G[0]);
		close(G[1]);

		execlp("sort","sort", NULL);
		exit(EXIT_FAILURE);
	}
    close(F[0]);
    close(F[1]);
    
    
    
    
    
    int K[2];
    pipe(K);
    
    pid_t pid8 = fork();
    if (!pid8) { // sed
        dup2(G[0], 0);
        close(G[0]);
        close(G[1]);
        
        dup2(K[1], 1);
        close(K[0]);
        close(K[1]);
        
        execlp("uniq","uniq","-c", NULL);
        exit(EXIT_FAILURE);
    }
    close(G[0]);
    close(G[1]);
   
    int L[2];
    pipe(L);
    
    pid_t pid9 = fork();
    if (!pid9) { // sed
        dup2(K[0], 0);
        close(K[0]);
        close(K[1]);
        
        dup2(L[1], 1);
        close(L[0]);
        close(L[1]);
        
        execlp("sort","sort","-nr", NULL);
        exit(EXIT_FAILURE);
    }
    close(K[0]);
    close(K[1]);
    
    
    
    int S[2];
    pipe(S);
    pid_t pid10 = fork();
    if (!pid10) { // awk
        dup2(L[0], 0);
        close(L[0]);
        close(L[1]);
        
        dup2(S[1], 1);
        close(S[0]);
        close(S[1]);
        execlp("head","head", "-10", NULL);
        exit(EXIT_FAILURE);
    }
    close(L[0]);
    close(L[1]);
    
    int M[2];
    pipe(M);
    pid_t pid11 = fork();
    if (!pid11) { // awk
        dup2(S[0], 0);
        close(S[0]);
        close(S[1]);
        
        dup2(M[1], 1);
        close(M[0]);
        close(M[1]);
        execlp("awk","awk", "{print $2 , $1 }", NULL);
        exit(EXIT_FAILURE);
    }
    close(S[0]);
    close(S[1]);
    
    
    
    FILE* Cin = fdopen(M[0],"r"); // Cin is FILE* object made from C[0]
    int sum=0;
    char line [1000];
    while (fgets(line, sizeof(line), Cin)){
        printf("%s", line);
        
    }
    
    return 0;
    
   
}
