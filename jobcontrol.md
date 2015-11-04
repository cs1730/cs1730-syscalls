# jobcontroll.cpp

This job control example is designed to emphasize the following:

 * ```SIGCONT``` will still continue a process, even with a handler set.
 * ```SIGTSTP``` will **NOT** stop a process unless its default handler is set.
 * ```SIGINT``` **CAN** change its handler disposition.

To play around with this, execute the program in the background.

```
$ ./jobcontrol &
```

Bash will give you the PID of the process. Verify that it is still running
using the ```jobs``` command:

```
$ jobs -l
```

Now, use ```kill`` to send ```SIGTSTP```. Replace ```pid``` with the process's
PID.

```
$ kill -SIGTSTP pid
```

You will notice that the signal was caught and the handler was executed.
However, if you execute the ```jobs``` command again, you'll see that the
process is still running. To actually force the process to stop, use ```kill```
to send ```SIGSTOP``` to the process.

```
$ kill -s SIGSTOP pid
```

Now, you will see that the job has stopped. If you're not sure what the
difference between ```SIGTSTP``` and ```SIGSTOP``` is, please consult reference
material.

Now that we have a stopped process, let's use kill to send it ```SIGCONT```.

```
$ kill -SIGCONT pid
```

The handler will execute, and the process will continue. You can verify this
using the jobs commands.

To terminate the process, use ```kill``` to send ```SIGTERM```.

