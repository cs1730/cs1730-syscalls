Content-type: text/html

<HTML><HEAD><TITLE>Manpage of OPEN</TITLE>
</HEAD><BODY>
<H1>OPEN</H1>
Section: Linux Programmer's Manual (2)<BR>Updated: 2008-12-03<BR><A HREF="#index">Index</A>
<A HREF="http://localhost/cgi-bin/man/man2html">Return to Main Contents</A><HR>

<A NAME="lbAB">&nbsp;</A>
<H2>NAME</H2>

open, creat - open and possibly create a file or device
<A NAME="lbAC">&nbsp;</A>
<H2>SYNOPSIS</H2>

<PRE>
<B>#include &lt;<A HREF="file:/usr/include/sys/types.h">sys/types.h</A>&gt;</B>
<B>#include &lt;<A HREF="file:/usr/include/sys/stat.h">sys/stat.h</A>&gt;</B>
<B>#include &lt;<A HREF="file:/usr/include/fcntl.h">fcntl.h</A>&gt;</B>

<B>int open(const char *</B><I>pathname</I><B>, int </B><I>flags</I><B>);</B>
<B>int open(const char *</B><I>pathname</I><B>, int </B><I>flags</I><B>, mode_t </B><I>mode</I><B>);</B>

<B>int creat(const char *</B><I>pathname</I><B>, mode_t </B><I>mode</I><B>);</B>
</PRE>

<A NAME="lbAD">&nbsp;</A>
<H2>DESCRIPTION</H2>

Given a
<I>pathname</I>

for a file,
<B>open</B>()

returns a file descriptor, a small, non-negative integer
for use in subsequent system calls
(<B><A HREF="http://localhost/cgi-bin/man/man2html?2+read">read</A></B>(2), <B><A HREF="http://localhost/cgi-bin/man/man2html?2+write">write</A></B>(2), <B><A HREF="http://localhost/cgi-bin/man/man2html?2+lseek">lseek</A></B>(2), <B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2), etc.).

The file descriptor returned by a successful call will be
the lowest-numbered file descriptor not currently open for the process.
<P>

By default, the new file descriptor is set to remain open across an
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+execve">execve</A></B>(2)

(i.e., the
<B>FD_CLOEXEC</B>

file descriptor flag described in
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

is initially disabled; the Linux-specific
<B>O_CLOEXEC</B>

flag, described below, can be used to change this default).
The file offset is set to the beginning of the file (see
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+lseek">lseek</A></B>(2)).

<P>

A call to
<B>open</B>()

creates a new
<I>open file description</I>,

an entry in the system-wide table of open files.
This entry records the file offset and the file status flags
(modifiable via the
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

<B>F_SETFL</B>

operation).
A file descriptor is a reference to one of these entries;
this reference is unaffected if
<I>pathname</I>

is subsequently removed or modified to refer to a different file.
The new open file description is initially not shared
with any other process,
but sharing may arise via
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fork">fork</A></B>(2).

<P>

The argument
<I>flags</I>

must include one of the following
<I>access modes</I>:

<B>O_RDONLY</B>, <B>O_WRONLY</B>, or <B>O_RDWR</B>.

These request opening the file read-only, write-only, or read/write,
respectively.
<P>
In addition, zero or more file creation flags and file status flags
can be
bitwise-<I>or</I>'d

in
<I>flags</I>.

The
<I>file creation flags</I>

are
<B>O_CREAT</B>, <B>O_EXCL</B>, <B>O_NOCTTY</B>, and <B>O_TRUNC</B>.

The
<I>file status flags</I>

are all of the remaining flags listed below.









The distinction between these two groups of flags is that
the file status flags can be retrieved and (in some cases)
modified using
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2).

The full list of file creation flags and file status flags is as follows:
<DL COMPACT>
<DT><B>O_APPEND</B>

<DD>
The file is opened in append mode.
Before each
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+write">write</A></B>(2),

the file offset is positioned at the end of the file,
as if with
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+lseek">lseek</A></B>(2).

<B>O_APPEND</B>

may lead to corrupted files on NFS file systems if more than one process
appends data to a file at once.



This is because NFS does not support
appending to a file, so the client kernel has to simulate it, which
can't be done without a race condition.
<DT><B>O_ASYNC</B>

<DD>
Enable signal-driven I/O:
generate a signal
(<B>SIGIO</B>

by default, but this can be changed via
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2))

when input or output becomes possible on this file descriptor.
This feature is only available for terminals, pseudo-terminals,
sockets, and (since Linux 2.6) pipes and FIFOs.
See
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

for further details.
<DT><B>O_CLOEXEC</B> (Since Linux 2.6.23)

<DD>
Enable the close-on-exec flag for the new file descriptor.
Specifying this flag permits a program to avoid additional
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

<B>F_SETFD</B>

operations to set the
<B>FD_CLOEXEC</B>

flag.
Additionally,
use of this flag is essential in some multithreaded programs
since using a separate
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

<B>F_SETFD</B>

operation to set the
<B>FD_CLOEXEC</B>

flag does not suffice to avoid race conditions
where one thread opens a file descriptor at the same
time as another thread does a
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fork">fork</A></B>(2)

plus
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+execve">execve</A></B>(2).




<DT><B>O_CREAT</B>

<DD>
If the file does not exist it will be created.
The owner (user ID) of the file is set to the effective user ID
of the process.
The group ownership (group ID) is set either to
the effective group ID of the process or to the group ID of the
parent directory (depending on file system type and mount options,
and the mode of the parent directory, see the mount options
<I>bsdgroups</I>

and
<I>sysvgroups</I>

described in
<B><A HREF="http://localhost/cgi-bin/man/man2html?8+mount">mount</A></B>(8)).



<DL COMPACT><DT><DD>
<P>

<I>mode</I>

specifies the permissions to use in case a new file is created.
This argument must be supplied when
<B>O_CREAT</B>

is specified in
<I>flags</I>;

if
<B>O_CREAT</B>

is not specified, then
<I>mode</I>

is ignored.
The effective permissions are modified by
the process's
<I>umask</I>

in the usual way: The permissions of the created file are
<I>(mode&nbsp;&amp;&nbsp;~umask)</I>.

Note that this mode only applies to future accesses of the
newly created file; the
<B>open</B>()

call that creates a read-only file may well return a read/write
file descriptor.
<P>

The following symbolic constants are provided for
<I>mode</I>:

<DL COMPACT>
<DT><B>S_IRWXU</B>

<DD>
00700 user (file owner) has read, write and execute permission
<DT><B>S_IRUSR</B>

<DD>
00400 user has read permission
<DT><B>S_IWUSR</B>

<DD>
00200 user has write permission
<DT><B>S_IXUSR</B>

<DD>
00100 user has execute permission
<DT><B>S_IRWXG</B>

<DD>
00070 group has read, write and execute permission
<DT><B>S_IRGRP</B>

<DD>
00040 group has read permission
<DT><B>S_IWGRP</B>

<DD>
00020 group has write permission
<DT><B>S_IXGRP</B>

<DD>
00010 group has execute permission
<DT><B>S_IRWXO</B>

<DD>
00007 others have read, write and execute permission
<DT><B>S_IROTH</B>

<DD>
00004 others have read permission
<DT><B>S_IWOTH</B>

<DD>
00002 others have write permission
<DT><B>S_IXOTH</B>

<DD>
00001 others have execute permission
</DL>
</DL>

<DT><B>O_DIRECT</B> (Since Linux 2.4.10)

<DD>
Try to minimize cache effects of the I/O to and from this file.
In general this will degrade performance, but it is useful in
special situations, such as when applications do their own caching.
File I/O is done directly to/from user space buffers.
The I/O is synchronous, that is, at the completion of a
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+read">read</A></B>(2)

or
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+write">write</A></B>(2),

data is guaranteed to have been transferred.
See
<B>NOTES</B>

below for further discussion.
<P>
A semantically similar (but deprecated) interface for block devices
is described in
<B><A HREF="http://localhost/cgi-bin/man/man2html?8+raw">raw</A></B>(8).

<DT><B>O_DIRECTORY</B>

<DD>
If <I>pathname</I> is not a directory, cause the open to fail.




This flag is Linux-specific, and was added in kernel version 2.1.126, to
avoid denial-of-service problems if
<B><A HREF="http://localhost/cgi-bin/man/man2html?3+opendir">opendir</A></B>(3)

is called on a
FIFO or tape device, but should not be used outside of the
implementation of
<B><A HREF="http://localhost/cgi-bin/man/man2html?3+opendir">opendir</A></B>(3).

<DT><B>O_EXCL</B>

<DD>
Ensure that this call creates the file:
if this flag is specified in conjunction with
<B>O_CREAT</B>,

and
<I>pathname</I>

already exists, then
<B>open</B>()

will fail.
The behavior of
<B>O_EXCL</B>

is undefined if
<B>O_CREAT</B>

is not specified.
<P>
When these two flags are specified, symbolic links are not followed:

if
<I>pathname</I>

is a symbolic link, then
<B>open</B>()

fails regardless of where the symbolic link points to.
<P>
<B>O_EXCL</B>

is only supported on NFS when using NFSv3 or later on kernel 2.6 or later.
In environments where NFS
<B>O_EXCL</B>

support is not provided, programs that rely on it
for performing locking tasks will contain a race condition.
Portable programs that want to perform atomic file locking using a lockfile,
and need to avoid reliance on NFS support for
<B>O_EXCL</B>,

can create a unique file on
the same file system (e.g., incorporating hostname and PID), and use
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+link">link</A></B>(2)

to make a link to the lockfile.
If
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+link">link</A></B>(2)

returns 0, the lock is successful.
Otherwise, use
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+stat">stat</A></B>(2)

on the unique file to check if its link count has increased to 2,
in which case the lock is also successful.
<DT><B>O_LARGEFILE</B>

<DD>
(LFS)
Allow files whose sizes cannot be represented in an
<I>off_t</I>

(but can be represented in an
<I>off64_t</I>)

to be opened.
The
<B>_LARGEFILE64_SOURCE</B>

macro must be defined in order to obtain this definition.
Setting the
<B>_FILE_OFFSET_BITS</B>

feature test macro to 64 (rather than using
<B>O_LARGEFILE</B>)

is the preferred method of obtaining
method of accessing large files on 32-bit systems (see
<B><A HREF="http://localhost/cgi-bin/man/man2html?7+feature_test_macros">feature_test_macros</A></B>(7)).

<DT><B>O_NOATIME</B> (Since Linux 2.6.8)

<DD>
Do not update the file last access time (st_atime in the inode)
when the file is
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+read">read</A></B>(2).

This flag is intended for use by indexing or backup programs,
where its use can significantly reduce the amount of disk activity.
This flag may not be effective on all file systems.
One example is NFS, where the server maintains the access time.


<DT><B>O_NOCTTY</B>

<DD>
If
<I>pathname</I>

refers to a terminal device --- see
<B><A HREF="http://localhost/cgi-bin/man/man2html?4+tty">tty</A></B>(4)

--- it will not become the process's controlling terminal even if the
process does not have one.
<DT><B>O_NOFOLLOW</B>

<DD>
If <I>pathname</I> is a symbolic link, then the open fails.
This is a FreeBSD extension, which was added to Linux in version 2.1.126.
Symbolic links in earlier components of the pathname will still be
followed.



<DT><B>O_NONBLOCK</B> or <B>O_NDELAY</B>

<DD>
When possible, the file is opened in non-blocking mode.
Neither the
<B>open</B>()

nor any subsequent operations on the file descriptor which is
returned will cause the calling process to wait.
For the handling of FIFOs (named pipes), see also
<B><A HREF="http://localhost/cgi-bin/man/man2html?7+fifo">fifo</A></B>(7).

For a discussion of the effect of
<B>O_NONBLOCK</B>

in conjunction with mandatory file locks and with file leases, see
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2).

<DT><B>O_SYNC</B>

<DD>
The file is opened for synchronous I/O.
Any
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+write">write</A></B>(2)s

on the resulting file descriptor will block the calling process until
the data has been physically written to the underlying hardware.
<I>But see NOTES below</I>.

<DT><B>O_TRUNC</B>

<DD>
If the file already exists and is a regular file and the open mode allows
writing (i.e., is
<B>O_RDWR</B>

or
<B>O_WRONLY</B>)

it will be truncated to length 0.
If the file is a FIFO or terminal device file, the
<B>O_TRUNC</B>

flag is ignored.
Otherwise the effect of
<B>O_TRUNC</B>

is unspecified.
</DL>
<P>

Some of these optional flags can be altered using
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

after the file has been opened.
<P>
<B>creat</B>()

is equivalent to
<B>open</B>()

with
<I>flags</I>

equal to
<B>O_CREAT|O_WRONLY|O_TRUNC</B>.

<A NAME="lbAE">&nbsp;</A>
<H2>RETURN VALUE</H2>

<B>open</B>()

and
<B>creat</B>()

return the new file descriptor, or -1 if an error occurred
(in which case,
<I>errno</I>

is set appropriately).
<A NAME="lbAF">&nbsp;</A>
<H2>ERRORS</H2>

<DL COMPACT>
<DT><B>EACCES</B>

<DD>
The requested access to the file is not allowed, or search permission
is denied for one of the directories in the path prefix of
<I>pathname</I>,

or the file did not exist yet and write access to the parent directory
is not allowed.
(See also
<B><A HREF="http://localhost/cgi-bin/man/man2html?7+path_resolution">path_resolution</A></B>(7).)

<DT><B>EEXIST</B>

<DD>
<I>pathname</I>

already exists and
<B>O_CREAT</B> and <B>O_EXCL</B>

were used.
<DT><B>EFAULT</B>

<DD>
<I>pathname</I>

points outside your accessible address space.
<DT><B>EFBIG</B>

<DD>
See
<B>EOVERFLOW</B>.

<DT><B>EINTR</B>

<DD>
While blocked waiting to complete an open of a slow device
(e.g., a FIFO; see
<B><A HREF="http://localhost/cgi-bin/man/man2html?7+fifo">fifo</A></B>(7)),

the call was interrupted by a signal handler; see
<B><A HREF="http://localhost/cgi-bin/man/man2html?7+signal">signal</A></B>(7).

<DT><B>EISDIR</B>

<DD>
<I>pathname</I>

refers to a directory and the access requested involved writing
(that is,
<B>O_WRONLY</B>

or
<B>O_RDWR</B>

is set).
<DT><B>ELOOP</B>

<DD>
Too many symbolic links were encountered in resolving
<I>pathname</I>,

or <B>O_NOFOLLOW</B> was specified but
<I>pathname</I>

was a symbolic link.
<DT><B>EMFILE</B>

<DD>
The process already has the maximum number of files open.
<DT><B>ENAMETOOLONG</B>

<DD>
<I>pathname</I>

was too long.
<DT><B>ENFILE</B>

<DD>
The system limit on the total number of open files has been reached.
<DT><B>ENODEV</B>

<DD>
<I>pathname</I>

refers to a device special file and no corresponding device exists.
(This is a Linux kernel bug; in this situation
<B>ENXIO</B>

must be returned.)
<DT><B>ENOENT</B>

<DD>
<B>O_CREAT</B>

is not set and the named file does not exist.
Or, a directory component in
<I>pathname</I>

does not exist or is a dangling symbolic link.
<DT><B>ENOMEM</B>

<DD>
Insufficient kernel memory was available.
<DT><B>ENOSPC</B>

<DD>
<I>pathname</I>

was to be created but the device containing
<I>pathname</I>

has no room for the new file.
<DT><B>ENOTDIR</B>

<DD>
A component used as a directory in
<I>pathname</I>

is not, in fact, a directory, or <B>O_DIRECTORY</B> was specified and
<I>pathname</I>

was not a directory.
<DT><B>ENXIO</B>

<DD>
<B>O_NONBLOCK</B> | <B>O_WRONLY</B>

is set, the named file is a FIFO and
no process has the file open for reading.
Or, the file is a device special file and no corresponding device exists.
<DT><B>EOVERFLOW</B>

<DD>
<I>pathname</I>

refers to a regular file that is too large to be opened.
The usual scenario here is that an application compiled
on a 32-bit platform without
<I>-D_FILE_OFFSET_BITS=64</I>

tried to open a file whose size exceeds
<I>(2&lt;&lt;31)-1</I>

bits;
see also
<B>O_LARGEFILE</B>

above.
This is the error specified by POSIX.1-2001;
in kernels before 2.6.24, Linux gave the error
<B>EFBIG</B>

for this case.



<DT><B>EPERM</B>

<DD>
The
<B>O_NOATIME</B>

flag was specified, but the effective user ID of the caller

did not match the owner of the file and the caller was not privileged
(<B>CAP_FOWNER</B>).

<DT><B>EROFS</B>

<DD>
<I>pathname</I>

refers to a file on a read-only file system and write access was
requested.
<DT><B>ETXTBSY</B>

<DD>
<I>pathname</I>

refers to an executable image which is currently being executed and
write access was requested.
<DT><B>EWOULDBLOCK</B>

<DD>
The
<B>O_NONBLOCK</B>

flag was specified, and an incompatible lease was held on the file
(see
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)).

</DL>
<A NAME="lbAG">&nbsp;</A>
<H2>CONFORMING TO</H2>

SVr4, 4.3BSD, POSIX.1-2001.
The
<B>O_DIRECTORY</B>,

<B>O_NOATIME</B>,

and
<B>O_NOFOLLOW</B>

flags are Linux-specific, and one may need to define
<B>_GNU_SOURCE</B>

to obtain their definitions.
<P>
The
<B>O_CLOEXEC</B>

flag is not specified in POSIX.1-2001,
but is specified in POSIX.1-2008.
<P>
<B>O_DIRECT</B>

is not specified in POSIX; one has to define
<B>_GNU_SOURCE</B>

to get its definition.
<A NAME="lbAH">&nbsp;</A>
<H2>NOTES</H2>

Under Linux, the
<B>O_NONBLOCK</B>

flag indicates that one wants to open
but does not necessarily have the intention to read or write.
This is typically used to open devices in order to get a file descriptor
for use with
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+ioctl">ioctl</A></B>(2).

<P>
Unlike the other values that can be specified in
<I>flags</I>,

the
<I>access mode</I>

values
<B>O_RDONLY</B>, <B>O_WRONLY</B>, and <B>O_RDWR</B>,

do not specify individual bits.
Rather, they define the low order two bits of
<I>flags</I>,

and are defined respectively as 0, 1, and 2.
In other words, the combination
<B>O_RDONLY | O_WRONLY</B>

is a logical error, and certainly does not have the same meaning as
<B>O_RDWR</B>.

Linux reserves the special, non-standard access mode 3 (binary 11) in
<I>flags</I>

to mean:
check for read and write permission on the file and return a descriptor
that can't be used for reading or writing.
This non-standard access mode is used by some Linux drivers to return a
descriptor that is only to be used for device-specific
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+ioctl">ioctl</A></B>(2)

operations.





<P>

The (undefined) effect of
<B>O_RDONLY | O_TRUNC</B>

varies among implementations.
On many systems the file is actually truncated.






<P>

There are many infelicities in the protocol underlying NFS, affecting
amongst others
<B>O_SYNC</B> and <B>O_NDELAY</B>.

<P>
POSIX provides for three different variants of synchronized I/O,
corresponding to the flags <B>O_SYNC</B>, <B>O_DSYNC</B> and
<B>O_RSYNC</B>.
Currently (2.1.130) these are all synonymous under Linux.
<P>
Note that
<B>open</B>()

can open device special files, but
<B>creat</B>()

cannot create them; use
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+mknod">mknod</A></B>(2)

instead.
<P>

On NFS file systems with UID mapping enabled,
<B>open</B>()

may
return a file descriptor but, for example,
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+read">read</A></B>(2)

requests are denied
with <B>EACCES</B>.
This is because the client performs
<B>open</B>()

by checking the
permissions, but UID mapping is performed by the server upon
read and write requests.
<P>
If the file is newly created, its
<I>st_atime</I>,

<I>st_ctime</I>,

<I>st_mtime</I>

fields
(respectively, time of last access, time of last status change, and
time of last modification; see
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+stat">stat</A></B>(2))

are set
to the current time, and so are the
<I>st_ctime</I>

and
<I>st_mtime</I>

fields of the
parent directory.
Otherwise, if the file is modified because of the
<B>O_TRUNC</B>

flag, its st_ctime and st_mtime fields are set to the current time.
<A NAME="lbAI">&nbsp;</A>
<H3>O_DIRECT</H3>

<P>

The
<B>O_DIRECT</B>

flag may impose alignment restrictions on the length and address
of userspace buffers and the file offset of I/Os.
In Linux alignment
restrictions vary by file system and kernel version and might be
absent entirely.
However there is currently no file system-independent
interface for an application to discover these restrictions for a given
file or file system.
Some file systems provide their own interfaces
for doing so, for example the
<B>XFS_IOC_DIOINFO</B>

operation in
<B><A HREF="http://localhost/cgi-bin/man/man2html?3+xfsctl">xfsctl</A></B>(3).

<P>

Under Linux 2.4, transfer sizes, and the alignment of the user buffer
and the file offset must all be multiples of the logical block size
of the file system.
Under Linux 2.6, alignment to 512-byte boundaries
suffices.
<P>

The
<B>O_DIRECT</B>

flag was introduced in SGI IRIX, where it has alignment
restrictions similar to those of Linux 2.4.
IRIX has also a
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

call to query appropriate alignments, and sizes.
FreeBSD 4.x introduced
a flag of the same name, but without alignment restrictions.
<P>

<B>O_DIRECT</B>

support was added under Linux in kernel version 2.4.10.
Older Linux kernels simply ignore this flag.
Some file systems may not implement the flag and
<B>open</B>()

will fail with
<B>EINVAL</B>

if it is used.
<P>

Applications should avoid mixing
<B>O_DIRECT</B>

and normal I/O to the same file,
and especially to overlapping byte regions in the same file.
Even when the file system correctly handles the coherency issues in
this situation, overall I/O throughput is likely to be slower than
using either mode alone.
Likewise, applications should avoid mixing
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+mmap">mmap</A></B>(2)

of files with direct I/O to the same files.
<P>

The behaviour of
<B>O_DIRECT</B>

with NFS will differ from local file systems.
Older kernels, or
kernels configured in certain ways, may not support this combination.
The NFS protocol does not support passing the flag to the server, so
<B>O_DIRECT</B>

I/O will only bypass the page cache on the client; the server may
still cache the I/O.
The client asks the server to make the I/O
synchronous to preserve the synchronous semantics of
<B>O_DIRECT</B>.

Some servers will perform poorly under these circumstances, especially
if the I/O size is small.
Some servers may also be configured to
lie to clients about the I/O having reached stable storage; this
will avoid the performance penalty at some risk to data integrity
in the event of server power failure.
The Linux NFS client places no alignment restrictions on
<B>O_DIRECT</B>

I/O.
<P>

In summary,
<B>O_DIRECT</B>

is a potentially powerful tool that should be used with caution.
It is recommended that applications treat use of
<B>O_DIRECT</B>

as a performance option which is disabled by default.
<P>

<DL COMPACT><DT><DD>
&quot;The thing that has always disturbed me about O_DIRECT is that the whole
interface is just stupid, and was probably designed by a deranged monkey
on some serious mind-controlling substances.&quot; --- Linus
</DL>

<A NAME="lbAJ">&nbsp;</A>
<H2>BUGS</H2>

Currently, it is not possible to enable signal-driven
I/O by specifying
<B>O_ASYNC</B>

when calling
<B>open</B>();

use
<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2)

to enable this flag.


<A NAME="lbAK">&nbsp;</A>
<H2>SEE ALSO</H2>

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+chmod">chmod</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+chown">chown</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+close">close</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+dup">dup</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+fcntl">fcntl</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+link">link</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+lseek">lseek</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+mknod">mknod</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+mmap">mmap</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+mount">mount</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+openat">openat</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+read">read</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+socket">socket</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+stat">stat</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+umask">umask</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+unlink">unlink</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?2+write">write</A></B>(2),

<B><A HREF="http://localhost/cgi-bin/man/man2html?3+fopen">fopen</A></B>(3),

<B><A HREF="http://localhost/cgi-bin/man/man2html?7+feature_test_macros">feature_test_macros</A></B>(7),

<B><A HREF="http://localhost/cgi-bin/man/man2html?7+fifo">fifo</A></B>(7),

<B><A HREF="http://localhost/cgi-bin/man/man2html?7+path_resolution">path_resolution</A></B>(7),

<B><A HREF="http://localhost/cgi-bin/man/man2html?7+symlink">symlink</A></B>(7)

<A NAME="lbAL">&nbsp;</A>
<H2>COLOPHON</H2>

This page is part of release 3.22 of the Linux
<I>man-pages</I>

project.
A description of the project,
and information about reporting bugs,
can be found at
<A HREF="http://www.kernel.org/doc/man-pages/.">http://www.kernel.org/doc/man-pages/.</A>
<P>

<HR>
<A NAME="index">&nbsp;</A><H2>Index</H2>
<DL>
<DT><A HREF="#lbAB">NAME</A><DD>
<DT><A HREF="#lbAC">SYNOPSIS</A><DD>
<DT><A HREF="#lbAD">DESCRIPTION</A><DD>
<DT><A HREF="#lbAE">RETURN VALUE</A><DD>
<DT><A HREF="#lbAF">ERRORS</A><DD>
<DT><A HREF="#lbAG">CONFORMING TO</A><DD>
<DT><A HREF="#lbAH">NOTES</A><DD>
<DL>
<DT><A HREF="#lbAI">O_DIRECT</A><DD>
</DL>
<DT><A HREF="#lbAJ">BUGS</A><DD>
<DT><A HREF="#lbAK">SEE ALSO</A><DD>
<DT><A HREF="#lbAL">COLOPHON</A><DD>
</DL>
<HR>
This document was created by
<A HREF="http://localhost/cgi-bin/man/man2html">man2html</A>,
using the manual pages.<BR>
Time: 01:00:53 GMT, November 04, 2015
</BODY>
</HTML>
