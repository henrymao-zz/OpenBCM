 #include <stdlib.h>
 #include <stdio.h>
 #include <stdarg.h>
 #include <string.h>
 #include <errno.h>

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <sys/un.h>
 #include <syslog.h>
 #include <sys/time.h>
 #include <sys/wait.h>

 #include <errno.h>
 #include <unistd.h>
 #include <signal.h>
 #include <pthread.h>
 #include <pty.h>
 #include <arpa/inet.h>


 static inline void syslog_printf(int priority, const char *format, ...)
 {
     va_list args1, args2;
     va_start(args1, format);
     va_copy(args2, args1); // va_list cannot be used twice, copy it
     vsyslog(priority, format, args1);

     FILE *f = (priority & LOG_PRIMASK) <= LOG_WARNING ? stderr : stdout;
     fprintf(f, "[%d] ", priority);
     vfprintf(f, format, args2);
     va_end(args2);
     va_end(args1);
 }
 // Quickly replace all syslog() with syslog_printf()
 #define syslog syslog_printf

 /* Network server */
 static volatile int _dsfd = -1;
 static int _server_socket;

 static int
 _setup_domain_socket(const char *sun_path)
 {
     struct sockaddr_un addr;
     int sockfd;

     if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
         syslog(LOG_ERR, "server: can't open stream socket: %s", strerror(errno));
         exit(EXIT_FAILURE);
     }

     /* Set up server address */
     memset((void *) &addr, 0x0, sizeof(addr));
     addr.sun_family = AF_UNIX;
     // Copy 1 char less to make sure the destination is ended with \0
     strncpy(addr.sun_path, sun_path, sizeof(addr.sun_path) - 1);

     /* Remove the domain socket file first */
     unlink(sun_path);
     /* Bind our domain socket */
     if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
         syslog(LOG_ERR, "server: can't bind domain socket: %s", strerror(errno));
         exit(EXIT_FAILURE);
     }

     /* Only process one connection at a time */
     listen(sockfd, 1);

     return sockfd;
 }

 static void *
 _ds2tty(void *arg)
 {
     int fd = *((int *)arg);
     const size_t DATA_SIZE = 1024;
     unsigned char data[DATA_SIZE];
     ssize_t rc;
     struct sockaddr_in addr;
     socklen_t len;

     while (1) {
         if (_dsfd < 0)
         {
             len = sizeof(addr);
             if ((_dsfd = accept(_server_socket, (struct sockaddr *) &addr, &len)) < 0) {
                 syslog(LOG_ERR, "server: can't accept socket: %s", strerror(errno));
                 exit(EXIT_FAILURE);
             }
         }

         rc = read(_dsfd, data, DATA_SIZE);
         if (rc <= 0) {
             if (rc < 0) {
                 /* Broken pipe -- client quit */
                 syslog(LOG_ERR, "_ds2tty broken pipe");
             }
             else {
                 /* Ending connection */
             }
             close(_dsfd);
             _dsfd = -1;
         } else {
             write(fd, data, rc);
             fsync(fd);
         }
     }

     return NULL;
 }

 static void *
 _tty2ds(void *arg)
 {
     int fd = *((int *)arg);
     const size_t DATA_SIZE = 1024;
     unsigned char data[DATA_SIZE];
     ssize_t rc;

     while (1) {
         rc = read(fd, data, DATA_SIZE);
         if (rc <= 0) {
             /* Broken pipe -- app quit */
             syslog(LOG_ERR, "_tty2ds broken pipe");
             close(fd);
             exit(0);
         }
         if (_dsfd >= 0) {
             ssize_t written = write(_dsfd, data, rc);
             // Handle the client exit problem
             if (written < 0) {
                 close(_dsfd);
                 _dsfd = -1;
             }
             fsync(_dsfd);
         }
         else
         {
             /* print orphaned message to the stdout */
             printf("%.*s", (int)rc, data);
             fflush(stdout);
         }
     }
     return NULL;
 }

 static const char *const DEFAULT_SUN_PATH = "/var/run/sswsyncd/sswsyncd.socket";
 const char *sun_path = DEFAULT_SUN_PATH;

 int
 switchdev_dstty_main(int ttyfd)
 {
     int rc;
     pthread_t id;

     /* Broken pipes are not a problem */
     signal(SIGPIPE, SIG_IGN);

     /* Setup server */
     _server_socket = _setup_domain_socket(sun_path);

     /* Start proxy for input */
     if ((rc = pthread_create(&id, NULL, _ds2tty, (void *)&ttyfd)) < 0) {
         syslog(LOG_ERR, "pthread_create: %s", strerror(rc));
         exit(EXIT_FAILURE);
     }

     /* Start proxy for output */
     if ((rc = pthread_create(&id, NULL, _tty2ds, (void *)&ttyfd)) < 0) {
         syslog(LOG_ERR, "pthread_create: %s", strerror(rc));
         exit(EXIT_FAILURE);
     }

     /* Wait for our child to exit */
     int status;
     waitpid(id, &status, 0);
     syslog(LOG_NOTICE, "child %s exited status: %d", "tty2ds", status);

     if (WIFEXITED(status))
     {
         if (WEXITSTATUS(status))
         {
             return 2;
         }
         else
         {
             return 0;
         }
     }
     else
     {
         return 3;
     }
 }
