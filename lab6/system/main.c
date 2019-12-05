/*main.c - main */
#include <xinu.h>

void receive_msg();
pid32 pid;
sid32 msgSem;

void main(void)
{
	msgSem = semcreate(0);
	pid = create(receive_msg, 1024, 21, "Process 2", 0);

	resume(pid);

	sendk(pid, "Msg 1 (valid) - this");
	sendk(pid, "Msg 2 (valid) - does");
	signal(pid);
	sendk(pid, "Msg 3 (valid) - multiple");
	sendk(pid, "Msg 4 (valid) - messages");
	sendk(pid, "Msg 5 (valid) - can now be sent");
	sendk(pid, "Msg 6 (valid) - still valid because consumed 2 earlier messages");
	sendk(pid, "Msg 7 (valid) - last valid message");
	sendk(pid, "Msg 8 (not valid)");
	sendk(pid, "Msg 9 (not valid)");
	sendk(pid, "Msg 10 (not valid)");
	sendk(pid, "Msg 11 (not valid)");
	sendk(pid, "Msg 12 (not valid)");
}

void receive_msg()
{
	wait(msgSem);
	int i = 0;
	while(1 == 1)
	{
		umsg32 str = receivek();
		kprintf("%s\n", str);

		if(i == 1) {
			sleep(5); // allow 10 messages to send
		}
		i++;
	}
}
