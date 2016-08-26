#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>

int main(void)
{
  struct pollfd fds[1];
  int timeout_msecs = 10000;/*10 secs*/
  int ret;

  fds[0].fd = 0;                            /*Adding fd(to be watched ) to FDLIST, here we are adding fd=0, i.e. STDIN to be monitored*/
  fds[0].events = POLLIN;                   /*Adding an event to be watched for this added fd, here we are adding POLLIN event that means this fd will be monitored if it receive any data*/
  ret = poll(fds, 1, -1);

  if (fds[0].revents && POLLIN)
  {
    /*once poll() returns we need to check  revent bit field for testing if any event occurred */
    printf("\n revents in fd[0] = 0x%x ", fds[0].revents);
  }

  if (ret > 0) {
    printf("Data is available now.\n");
  }
  else if (ret == -1)
    perror("poll()");
  else
    printf("TIME OUT…No data within 10 seconds.\n");

  close(fds[1].fd);
  return 0;
}
