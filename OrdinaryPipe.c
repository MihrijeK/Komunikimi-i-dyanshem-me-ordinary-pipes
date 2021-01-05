#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
   int pipe1[2], pipe2[2];
   int returnstatus1, returnstatus2;
   int pid;
   char pipe1writemsg[20] = "hello";
   char pipe2writemsg[20] = "HELLO";
   char readmsg[20];
   
   //krijimi i pipe 1
   returnstatus1 = pipe(pipe1);
   if (returnstatus1 == -1) {
      printf("Krijimi i pipe 1 ka deshtuar \n");
      return 1;
   }
   
   //krijimi i pipe 2
   returnstatus2 = pipe(pipe2);
   if (returnstatus2 == -1) {
      printf("Krijimi i pipe 2 ka deshtuar \n");
      return 1;
   }
   
   pid = fork();
   
   if (pid != 0) // Procesi prind 
   {
      // Mbyllja e anes se leximit te pipe1 dhe anes se shkrimit ne pipe2
      close(pipe1[0]); 
      close(pipe2[1]);
      
      printf("Mesazhi i shkruar nga procesi prind eshte: %s\n", pipe1writemsg);
      //Shkrimi i mesazhit ne pipe
      write(pipe1[1], pipe1writemsg, sizeof(pipe1writemsg));
      
      //Nga pipe tjeter lexohet mesazhi i shkruar nga femija
      read(pipe2[0], readmsg, sizeof(readmsg));
      printf("Mesazhi i lexuar nga procesi prind eshte %s\n " , readmsg);
      /* Perdorimi i funksionit reverse
printf(“Mesazhi i lexuar nga procesi prind eshte ”);
 	reverse(readmsg);
      printf("\n");
	*/
     
   } else { //Procesi femije
      //Mbyllja e anes se shkrimit te pipe1 dhe anes se leximit te pipe 2
      close(pipe1[1]);
      close(pipe2[0]); 
      
      //Leximi i mesazhit te shkruar nga prindi
      read(pipe1[0], readmsg , sizeof(readmsg));
      
      printf(“Mesazhi i lexuar nga procesi femije %s\n”,readmsg);
	/* Perdorimi i funksionit reverse
printf(“Mesazhi i lexuar nga procesi femije eshte ”);
 	reverse(readmsg);
      printf("\n");
	*/
      printf("Mesazhi i shkruar nga procesi femije %s\n", pipe2writemsg);
      
      //Shkimi i mesazhit ne pipe
      write(pipe2[1], pipe2writemsg , sizeof(pipe2writemsg));
   }
   return 0;
}

void reverse(char *data){
      int n = strlen(data); 
  
      for(int i = n - 1; i >= 0; i--) {
        printf("%c", data[i]);
    }
}
