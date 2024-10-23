#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<fcntl.h>
#include <wait.h>
#include<unistd.h>
//message que struct that is used in message que code
// in the example thats inside the main function below:
// struct message{
//     long identifier;
//     int data;
// };
int main(){
    // example of  the message que code:
//     int message_que= msgget(IPC_PRIVATE, 
//     0666|IPC_CREAT|IPC_EXCL);
//     if(message_que==-1){
//         perror(
//      "\nerror occured in function msgt, the error is:");
//     }
//     printf("\n");
//     struct message msg1={1, 10};
//     if(msgsnd(message_que, 
//     &msg1, sizeof(msg1)-sizeof(long), 
//     IPC_NOWAIT)==-1){
//         perror("\nmessage send failed, error is:");
//         printf("\n");
//     }
//     if(fork()==0){
//         struct message msg2;
//         if(msgrcv(message_que, 
//     &msg2, sizeof(msg2)-sizeof(long), 
//     1,
//     IPC_NOWAIT)==-1){
//         perror("\nmessage recieve failed, error is:");
//         printf("\n");
//     }
//     printf("\n the data is %d\n",msg2.data);
       
// }
//     else{
//         wait(NULL);
//     if(msgctl(message_que, 
//             IPC_RMID, NULL)==-1){
//         perror("\n remove of message que failed, error is:");
//             }
        
//     }

    //first argument of msgget is the key of the message
//que and the second the options of the message que
    
    //IPC_PRIVATE MACRO is a constant that when 
    // passed to the first argument of msgget
    //makes the message que thats created
    //have a unique key
//IPC_PRIVATE is used when there is parent and child
// relationship between the processes that want to
//  communicate with each others.

// u can set the permissions of the message que
// and some other flags in the second option using 
// '|'(BITWISE-OR operator)
// the permissions are the same as file permissions
// except for the fact that u cant set the permissions
// for who is allowed to execute  cuz u cant execute a 
// message que
// hence u can simply write 0666 instead of  
// writing 0777 in order to give all the users
// all kinds of permissions to the message que.
//u can also use:key_t ftok( char *pathname, int proj );
//to create a key to pass to the first argument of 
// msgget. ftok function dosent ensure that ur key
//is completely unique but the risk isnt that big.
//ftok takes a pathname and a integer and
//uses them to generate a key

//lets take some time on what a message struct looks
//  like:
// struct message{
//  long indentifier_of_message;
//  void *data;
// };
//the message struct can be of any name
//the first element of the message structure
// has to be of long data type while the rest elements
//can be as many as u want and of any type u want.
//the first element is like a identifier for the message
//and can be used to recieve the message on
//the recieving side
// function for sending messages:
// int msgsnd( int msqid, const void *ptr, size_t nbytes, int flag );
// The first parameter is the message queue we want
//  to send the message to; the second is the message
//  struct;  the third is  the size of the message struct
// that we  want to
//  send,  excluding the first field of the message struct.
//  The last parameter is for what 
// happens if the queue is full:by providing zero it will
// make the msgsnd function wait until space is free.
//   But if you use IPC_NOWAIT, then an 
// attempt to add to a full  queue will just return with
// an error instead of waiting for the space to be freed.
//the reason the second argument is void is because
//a message struct can be of any name.
// function for recieving the message:
// ssize_t msgrcv( int msqid, void *ptr, size_t nbytes, long type, int flag );
// The first argument is the message queue to receive
// from;the second argument is the
//  message struct where the
// message will be copied to; the third argument is 
// the size of the message structure 
// excluding the size of the first element.
// . The fourth
// argument known as "type" is used to find the 
// message that ur  looking for:
// • type == 0 - Return the first message in
//  the queue
// • type > 0 - Return the first message in the 
// queue that has the  first element in its structure
// be equal to the type argument
// • type < 0 - Return the first message in the 
// queue whose first argument is the smallest value 
// less than or equal to the  absolute value of type

//  The last
// parameter, again, can be used to specify that you 
// don't want to wait if the message you are looking
// for does not exist.
//if the last paremeter is zero then it will wait and if
// it is IPC_NOWAIT then it wont wait


//to remove the message que the code is:
// msgctl( message_que, IPC_RMID, NULL );
//    msgctl can be used for a lot of different usecases
//  but when u are just trying to remove the message
//  que
//    then the second argument is IPC_RMID and
//    the third would be NULL while the first would be
//    the  specific message que that the wonna remove
//if u try to remove the same message que twice
//in the same process or two or more two processes
//then an error will occur and msgctl will return -1
    return 0;
}