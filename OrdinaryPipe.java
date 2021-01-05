import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.concurrent.TimeUnit;

public class TwoWayCommunication {
   public static void main(String[] args) throws Exception {
       //Pseudo parent process
       final PipedOutputStream outputPipe1=new PipedOutputStream();
       final PipedInputStream inputPipe1=new PipedInputStream(outputPipe1);

       //Pseudo child process
       final PipedOutputStream outputPipe2=new PipedOutputStream();
       final PipedInputStream inputPipe2=new PipedInputStream(outputPipe2);


       Thread thread1=new Thread(new Runnable() {
           @Override
           public void run() {
               try{
                   System.out.print("\nProcesi prind shkruan: HELLO");
                   outputPipe1.write("HELLO".getBytes());
                   int data=inputPipe2.read();
                   System.out.print("\nProcesi prind lexon:");
                   while(data!=-1){
                       System.out.print((char)data);
                       data=inputPipe2.read();
                   }
                   //TimeUnit.SECONDS.sleep(1);
               }catch(Exception e){
                   System.out.println(e.getMessage());
               }
           }
       });

       Thread thread2=new Thread(new Runnable() {
           @Override
           public void run() {
               try{
                   System.out.print("\nProcesi femije shkruan: hello");
                   outputPipe2.write("hello".getBytes());
                   int data=inputPipe1.read();
                   System.out.print("\nProcesi femije lexon:");
                   while(data!=-1){
                       System.out.print((char)data);
                       data=inputPipe1.read();
                   }
                   //TimeUnit.SECONDS.sleep(1);
               }catch(Exception e){
                   System.out.println(e.getMessage());
               }
           }
       });

       thread1.start();
       thread2.start();

       thread1.join();
       thread2.join();
   }
}
